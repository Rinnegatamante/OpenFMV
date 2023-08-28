#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <vitasdk.h>
#include <vitaGL.h>
#include "audio.h"
#include "engine.h"
#include "games.h"
#include "player.h"
#include "unzip.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MEM_BUFFER_SIZE (2 * 1024 * 1024)

static char generic_mem_buffer[MEM_BUFFER_SIZE];
static char generic_buf[512], subtitle_buf[512];
unzFile sub_handle = NULL;
engine config;

int btns_state;
uint32_t cur_delta;
int trigger_save = 0;
int chosen_path = 0;
int cur_event = 0;
int fake_pass = 0;
int game_state;
playstate game_vars = {0};
gamestate global_vars = {0};
sequence sequences[NUM_SEQUENCES];
audio_sample bgm[NUM_AUDIO_SAMPLES];
subs_window subs_win;

sequence *cur_seq;
choice *cur_choice;
subtitle *cur_sub;
theme colors;
void *snd_click, *snd_hover, *snd_pause, *snd_unpause;

void load_subtitles(sequence *s) {
#ifdef DEBUG
	debug_log("Loading subtitles for %s sequence\n", s->name);
#endif
	unz_file_info file_info;
	sprintf(subtitle_buf, "%s.srt", s->hash);
	s->num_subs = 0;
	if (unzLocateFile(sub_handle, subtitle_buf, NULL) == UNZ_OK) {
		unzGetCurrentFileInfo(sub_handle, &file_info, subtitle_buf, 512, NULL, 0, NULL, 0);
		unzOpenCurrentFile(sub_handle);
		uint32_t executed_bytes = 0;
		while (executed_bytes < file_info.uncompressed_size) {
			uint32_t read_size = (file_info.uncompressed_size - executed_bytes) > MEM_BUFFER_SIZE ? MEM_BUFFER_SIZE : (file_info.uncompressed_size - executed_bytes);
			unzReadCurrentFile(sub_handle, generic_mem_buffer, read_size);
			executed_bytes += read_size;
		}
		generic_mem_buffer[file_info.uncompressed_size] = 0;
		unzCloseCurrentFile(sub_handle);	
		char *l = strstr(generic_mem_buffer, "-->");
		
		while (l) {
			int times_start[4];
			int times_end[4];
			sscanf(l - 13, "%2d:%2d:%2d,%3d --> %2d:%2d:%2d,%3d", &times_start[0], &times_start[1], &times_start[2], &times_start[3], &times_end[0], &times_end[1], &times_end[2], &times_end[3]);
			s->subs[s->num_subs].start = times_start[3] + times_start[2] * 1000 + times_start[1] * 1000 * 60 /*+ times_start[3] * 1000 * 60 * 60*/;
			s->subs[s->num_subs].end = times_end[3] + times_end[2] * 1000 + times_end[1] * 1000 * 60 /*+ times_start[3] * 1000 * 60 * 60*/;
			char *start = &l[17];
			if (*start == '*') {
				s->subs[s->num_subs].is_italic = 1;
				start += 2;
			} else {
				s->subs[s->num_subs].is_italic = 0;
			}
			char *end = strstr(start, SUBTITLE_NEWLINE);
			if (!end) {
				end = &generic_mem_buffer[strlen(generic_mem_buffer) - 2];
			}
			strncpy(s->subs[s->num_subs].text, start, end - start);
			s->subs[s->num_subs].text[end - start] = 0;
			s->subs[s->num_subs].next = NULL;
			if (s->num_subs > 0)
				s->subs[s->num_subs - 1].next = &s->subs[s->num_subs];
			l = strstr(l + 18, "-->");
			s->num_subs++;
		}
	}
	
	s->sub_lang = config.language;
}

#define SUBS_LOADER_QUEUE_SIZE 8
volatile sequence *to_load[SUBS_LOADER_QUEUE_SIZE] = {NULL};
SceUID subs_request_mutex, subs_delivered_mutex;
int subs_loader(SceSize args, void *argp) {
	for (;;) {
		sceKernelWaitSema(subs_request_mutex, 1, NULL);
		for (int i = 0; i < SUBS_LOADER_QUEUE_SIZE; i++) {
			if (!to_load[i]) {
				break;
			}
			load_subtitles((sequence *)to_load[i]);
		}
		sceKernelSignalSema(subs_delivered_mutex, 1);
	}
	
	return 0;
}

void fill_sequence(char *name, sequence *s, sequence *(*d)(), char *(*ltext)(), char *(*rtext)(), char *(*etext)(), sequence *(*l)(), sequence *(*r)(), sequence *(*e)(), uint32_t start, uint32_t end, uint32_t jump) {
	s->d = d;
	s->main_choice.l = l;
	s->main_choice.r = r;
	s->main_choice.e = e;
	s->main_choice.ltext = ltext;
	s->main_choice.rtext = rtext;
	s->main_choice.etext = etext;
	s->main_choice.start = start;
	s->main_choice.end = end;
	s->main_choice.jump_time = jump;
	s->sub_lang = -1;
#ifdef DEBUG
	strcpy(s->name, name);
#endif
	spooky_hash128(name, strlen(name), s->hash);
	
	sceClibMemset(&s->aux_choice, 0, sizeof(choice));
}

void add_extra_choice(sequence *s, char *(*ltext)(), char *(*rtext)(), char *(*etext)(), sequence *(*l)(), sequence *(*r)(), sequence *(*e)(), uint32_t start, uint32_t end, uint32_t jump) {
	s->aux_choice.l = l;
	s->aux_choice.r = r;
	s->aux_choice.e = e;
	s->aux_choice.ltext = ltext;
	s->aux_choice.rtext = rtext;
	s->aux_choice.etext = etext;
	s->aux_choice.start = start;
	s->aux_choice.end = end;
	s->aux_choice.jump_time = jump;
}

#define enqueue_link(x) \
	if (x) { \
		link = x(); \
		if (link && link->sub_lang != config.language) \
			to_load[i++] = link; \
	}

void reload_subtitles(sequence *s) {
	// Loading current sequence subtitles directly
	load_subtitles(s);
	if (s->num_subs > 0) {
		cur_sub = &s->subs[0];
	} else {
		cur_sub = NULL;
	}
	
	// Dumping current gamestate
	playstate dump;
	memcpy(&dump, &game_vars, sizeof(game_state));
	int real_trigger_save = trigger_save;
	
	// Faking possible choices to get a list of reachable sequences
	int i = 0;
	fake_pass = 1;
	sequence *link;
	if (s->d != LOOP_SEQUENCE)
		enqueue_link(s->d);
	enqueue_link(s->main_choice.l);
	enqueue_link(s->main_choice.r);
	enqueue_link(s->main_choice.e);
	enqueue_link(s->aux_choice.l);
	enqueue_link(s->aux_choice.r);
	enqueue_link(s->aux_choice.e);
	to_load[i] = NULL;
	fake_pass = 0;
	
	// Restoring original gamestate
	trigger_save = real_trigger_save;
	memcpy(&game_vars, &dump, sizeof(game_state));
	
	// Loading reachable sequences subtitles in parallel
	sceKernelWaitSema(subs_delivered_mutex, 1, NULL);
	sceKernelSignalSema(subs_request_mutex, 1);
}

void start_sequence(sequence *s) {
#ifdef DBG_SAVE
	trigger_save = 1;
#endif
#ifdef DEBUG
	debug_log("Launching %s sequence\n", s->name);
#endif
	// Dumping current gamestate
	gamestate dump;
	memcpy(&dump, &game_vars, sizeof(game_state));
	
	// Faking possible choices to get a list of reachable sequences
	int i = 0;
	fake_pass = 1;
	sequence *link;
	if (s->d != LOOP_SEQUENCE)
		enqueue_link(s->d);
	enqueue_link(s->main_choice.l);
	enqueue_link(s->main_choice.r);
	enqueue_link(s->main_choice.e);
	enqueue_link(s->aux_choice.l);
	enqueue_link(s->aux_choice.r);
	enqueue_link(s->aux_choice.e);
	to_load[i] = NULL;
	fake_pass = 0;
	
	// Restoring original gamestate
	memcpy(&game_vars, &dump, sizeof(game_state));
	
	// Updating progress save
	if (trigger_save) {
		debug_log("Saving...\n");
		FILE *f = fopen(PLAYTHROUGH_SAVE_FILE, "w");
		fwrite(s->hash, 1, 32, f);
		fwrite(&game_vars, 1, sizeof(playstate), f);
		fclose(f);
		f = fopen(GLOBAL_SAVE_FILE, "w");
		fwrite(&global_vars, 1, sizeof(gamestate), f);
		fclose(f);
		trigger_save = 0;
	}
	
	// Loading reachable sequences subtitles in parallel
	sceKernelWaitSema(subs_delivered_mutex, 1, NULL);
	sceKernelSignalSema(subs_request_mutex, 1);
	if (s->num_subs > 0)
		cur_sub = &s->subs[0];
	else
		cur_sub = NULL;
	
	// Loading video file
	sprintf(generic_buf, "/Converted/%s.mp4", s->hash);
	video_open(generic_buf, s->d == LOOP_SEQUENCE ? 1 : 0);
	cur_seq = s;
	cur_choice = &s->main_choice;
	cur_event = 0;
	cur_delta = 0;
	chosen_path = 0;
	btns_state = BTNS_CALC_SIZE;
}

void start_first_sequence(sequence *s) {
	// Directly loading first sequence subtitles
	if (s->sub_lang != config.language) {
		load_subtitles(s);
	}
	
	start_sequence(s);
}

void install_timed_event(sequence *t, uint32_t start, uint32_t end, uint8_t type, sequence *(*s)()) {
	t->events[t->num_events].start = start;
	t->events[t->num_events].end = end;
	t->events[t->num_events].s = s;
	t->events[t->num_events].type = type;
	t->num_events++;
}

void load_animated_bg(const char *fname, int needs_hash) {
	char tmp[128];
	if (needs_hash) {
		char hash[64];
		spooky_hash128(fname, strlen(fname), hash);
		sprintf(tmp, "/Converted/%s.mp4", hash);
		fname = tmp;
	}
	video_open(fname, 1);
}

void load_video(const char *fname, int needs_hash) {
	char tmp[128];
	if (needs_hash) {
		char hash[64];
		spooky_hash128(fname, strlen(fname), hash);
		sprintf(tmp, "/Converted/%s.mp4", hash);
		fname = tmp;
	}
	video_open(fname, 0);
}

uint32_t load_image(const char *fname) {
	uint32_t w, h, res;
	uint8_t *data = stbi_load(fname, &w, &h, NULL, 4);
	glGenTextures(1, &res);
	glBindTexture(GL_TEXTURE_2D, res);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	return res;
}

void free_image(uint32_t image) {
	glDeleteTextures(1, &image);
}

volatile audio_sample *audio_to_load;
SceUID audio_request_mutex, audio_delivered_mutex;
int audio_loader(SceSize args, void *argp) {
	for (;;) {
		sceKernelWaitSema(audio_request_mutex, 1, NULL);
		if (audio_to_load->is_voice) {
			audio_to_load->src = audio_voice_track_play((const char *)audio_to_load->fname, audio_to_load->looping, audio_to_load->volume, (int *)&audio_to_load->handle);
		} else {
			audio_to_load->src = audio_track_play((const char *)audio_to_load->fname, audio_to_load->looping, audio_to_load->volume, (int *)&audio_to_load->handle);
		}
		sceKernelSignalSema(audio_delivered_mutex, 1);
	}
	
	return 0;
}

audio_sample *audio_sample_start(const char *fname, int looping, float vol) {
	audio_sample *r = NULL;
	for (int i = 0; i < NUM_AUDIO_SAMPLES; i++) {
		if (!bgm[i].active) {
			r = &bgm[i];
#ifdef DEBUG
			printf("Playing %s on slot %d\n", fname, i);
#endif
			break;
		}
	}
#ifndef SYNC_AUDIO_LOAD
	sceKernelWaitSema(audio_delivered_mutex, 1, NULL);
	strcpy(r->fname, fname);
	r->src = NULL;
	r->handle = 0;
	r->volume = vol;
	r->looping = looping;
	r->is_voice = 0;
	audio_to_load = r;
	sceKernelSignalSema(audio_request_mutex, 1);
#else
	r->src = audio_track_play(fname, looping, vol, &r->handle);
	r->volume = vol;
#endif
	r->active = 1;
	return r;
}

audio_sample *audio_voice_sample_start(const char *fname, int looping, float vol) {
	audio_sample *r = NULL;
	for (int i = 0; i < NUM_AUDIO_SAMPLES; i++) {
		if (!bgm[i].active) {
			r = &bgm[i];
#ifdef DEBUG
			printf("Playing %s on slot %d\n", fname, i);
#endif
			break;
		}
	}
#ifndef SYNC_AUDIO_LOAD
	sceKernelWaitSema(audio_delivered_mutex, 1, NULL);
	strcpy(r->fname, fname);
	r->src = NULL;
	r->handle = 0;
	r->volume = vol;
	r->looping = looping;
	r->is_voice = 1;
	audio_to_load = r;
	sceKernelSignalSema(audio_request_mutex, 1);
#else
	r->src = audio_voice_track_play(fname, looping, vol, &r->handle);
	r->volume = vol;
#endif
	r->active = 1;
	return r;
}

void audio_sample_stop(audio_sample *s) {
	if (s) {
		audio_track_stop(s->src, s->handle);
		s->active = 0;
	}
}

void audio_sample_stop_all() {
	for (int i = 0; i < NUM_AUDIO_SAMPLES; i++) {
		if (bgm[i].active) {
			audio_sample_stop(&bgm[i]);
		}
	}
}

void audio_sample_reset_volume_all() {
	for (int i = 0; i < NUM_AUDIO_SAMPLES; i++) {
		if (bgm[i].active) {
			audio_sample *s = &bgm[i];
			audio_sample_set_volume(s, bgm[i].volume);
		}
	}
}

void start_async_loaders() {
	subs_request_mutex = sceKernelCreateSema("subs request", 0, 0, 1, NULL);
	subs_delivered_mutex = sceKernelCreateSema("subs delivery", 0, 1, 1, NULL);
	SceUID subs_loader_thd = sceKernelCreateThread("subs loader", &subs_loader, 0x10000100, 0x10000, 0, 0, NULL);
	sceKernelStartThread(subs_loader_thd, 0, NULL);
#ifndef SYNC_AUDIO_LOAD
	audio_request_mutex = sceKernelCreateSema("audio request", 0, 0, 1, NULL);
	audio_delivered_mutex = sceKernelCreateSema("audio delivery", 0, 1, 1, NULL);
	SceUID audio_loader_thd = sceKernelCreateThread("audio loader", &audio_loader, 0x10000100, 0x10000, 0, 0, NULL);
	sceKernelStartThread(audio_loader_thd, 0, NULL);
#endif
}

void set_subs_window(float x, float y, float w, float h) {
	subs_win.x = x;
	subs_win.y = y;
	subs_win.w = w;
	subs_win.h = h;
}
