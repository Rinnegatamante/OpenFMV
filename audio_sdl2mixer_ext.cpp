#ifdef HAVE_SDL2_MIXER_EXT
#include <malloc.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer_ext.h>
#include "engine.h"
#include "games.h"

extern "C" {
	
void audio_sdl2_init() {
	SDL_Init(SDL_INIT_AUDIO);
	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024);
	Mix_AllocateChannels(52);
}

void audio_sdl2_pause() {
	Mix_PauseMusicStreamAll();
}

void audio_sdl2_resume() {
	Mix_ResumeMusicStreamAll();
}

void *audio_sdl2_track_play(const char *fname, int looping, float vol, int *handle) {
	char path[256];
	sprintf(path, "%s/%s.wav.ogg", AUDIO_FOLDER, fname);
	Mix_Music *res = Mix_LoadMUS(path);
	Mix_VolumeMusicStream(res, (int)(vol * config.music_volume * 128.0f));
	Mix_PlayMusicStream(res, looping ? -1 : 1);
	*handle = (int)res;
	return res;
}

void *audio_sdl2_voice_track_play(const char *fname, int looping, float vol, int *handle) {
	char path[256];
	sprintf(path, "%s/%s.wav.ogg", AUDIO_FOLDER, fname);
	Mix_Music *res = Mix_LoadMUS(path);
	Mix_VolumeMusicStream(res, (int)(vol * 128.0f));
	Mix_PlayMusicStream(res, looping ? -1 : 1);
	*handle = (int)res;
	return res;
}

void audio_sdl2_track_stop(void *s) {
	Mix_HaltMusicStream((Mix_Music *)s);
	Mix_FreeMusic((Mix_Music *)s);
}

void audio_sdl2_track_set_volume(int h, float vol) {
	Mix_VolumeMusicStream((Mix_Music *)h, (int)(vol * config.music_volume * 128.0f));
}

float audio_sdl2_track_fade(int h, float volume_start, float volume_end, uint32_t time_start, uint32_t time_end) {
	float volume_delta = volume_end - volume_start;
	float time_delta = time_end - time_start;
	float delta = cur_delta - time_start;
	float new_volume = volume_start + (delta / time_delta) * volume_delta;
	Mix_VolumeMusicStream((Mix_Music *)h, (int)(new_volume * config.music_volume * 128.0f));
	return new_volume;
}

void *audio_sdl2_sound_load(const char *fname) {
	return Mix_LoadWAV(fname);
}

void audio_sdl2_sound_play(void *s) {
	Mix_VolumeChunk((Mix_Chunk *)s, (int)(config.master_volume * 128.0f));
	Mix_PlayChannel(-1, (Mix_Chunk *)s, 0);
}

void audio_sdl2_set_global_volume(float vol) {
	Mix_VolumeMusicGeneral((int)(vol * 128.0f));
}

}
#endif
