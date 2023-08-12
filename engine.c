#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "late_shift.h"
#include "player.h"
#include "unzip.h"

#define MEM_BUFFER_SIZE (2 * 1024 * 1024)
//#define DBG_SAVE // Enable saving at each sequence change for debugging

static char generic_mem_buffer[MEM_BUFFER_SIZE];
static char generic_buf[512];
unzFile sub_handle = NULL;
engine config;

int btns_state;
uint32_t cur_delta;
int trigger_save = 0;
int chosen_path = 0;
int cur_event = 0;
gamestate game_vars;
subtitle subs[128];
sequence sequences[NUM_SEQUENCES];

sequence *cur_seq;
subtitle *cur_sub;
theme colors;
void *snd_click;
void *snd_hover;

void fill_sequence(sequence *s, char *(*ltext)(), char *(*rtext)(), char *(*etext)(), sequence *(*l)(), sequence *(*r)(), sequence *(*e)(), uint32_t start, uint32_t end, uint32_t jump) {
	s->l = l;
	s->r = r;
	s->e = e;
	s->ltext = ltext;
	s->rtext = rtext;
	s->etext = etext;
	s->start = start;
	s->end = end;
	s->jump_time = jump;
}

void start_sequence(sequence *s) {
#ifdef DBG_SAVE
	trigger_save = 1;
#endif

#if 1
	printf("Launching %s\n", s->hash);
#endif

	// Updating progress save
	if (trigger_save) {
		FILE *f = fopen("ux0:data/Late Shift/progress.sav", "w");
		fwrite(s->hash, 1, 32, f);
		fwrite(&game_vars, 1, sizeof(gamestate), f);
		fclose(f);
		trigger_save = 0;
	}
	
	// Loading subtitles
	unz_file_info file_info;
	sprintf(generic_buf, "%s.srt", s->hash);
	int sub_idx = 0;
	if (unzLocateFile(sub_handle, generic_buf, NULL) == UNZ_OK) {
		unzGetCurrentFileInfo(sub_handle, &file_info, generic_buf, 512, NULL, 0, NULL, 0);
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
			subs[sub_idx].start = times_start[3] + times_start[2] * 1000 + times_start[1] * 1000 * 60 /*+ times_start[3] * 1000 * 60 * 60*/;
			subs[sub_idx].end = times_end[3] + times_end[2] * 1000 + times_end[1] * 1000 * 60 /*+ times_start[3] * 1000 * 60 * 60*/;
			char *start = &l[17];
			if (*start == '*') {
				subs[sub_idx].is_italic = 1;
				start += 2;
			} else {
				subs[sub_idx].is_italic = 0;
			}
			char *end = strstr(start, "\n");
			strncpy(subs[sub_idx].text, start, end - start);
			subs[sub_idx].text[end - start] = 0;
			subs[sub_idx].next = NULL;
			if (sub_idx > 0)
				subs[sub_idx - 1].next = &subs[sub_idx];
			l = strstr(l + 18, "-->");
			sub_idx++;
		}
	}
	if (sub_idx > 0)
		cur_sub = &subs[0];
	else
		cur_sub = NULL;
	
	// Loading video file
	sprintf(generic_buf, "/Converted/%s.mp4", s->hash);
	video_open(generic_buf, 0);
	cur_seq = s;
	cur_event = 0;
	chosen_path = 0;
	btns_state = BTNS_CALC_SIZE;
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

void resolve_hash(const char *src, char *dst) {
	spooky_hash128(src, strlen(src), dst);
}
