#include <malloc.h>
#include <stdio.h>
#include "audio.h"
#include "engine.h"
#include "games.h"

void (*audio_init)();
void (*audio_pause)();
void (*audio_resume)();
void (*audio_set_global_volume)(float vol);
void *(*audio_track_play)(const char *fname, int looping, float vol, int *h);
void *(*audio_voice_track_play)(const char *fname, int looping, float vol, int *h);
void (*audio_track_stop)(void *s);
void (*audio_track_set_volume)(int h, float vol);
float (*audio_track_fade)(int h, float volume_start, float volume_end, uint32_t time_start, uint32_t time_end);
void *(*audio_sound_load)(const char *fname);
void (*audio_sound_play)(void *s);

char *audio_backends[] = {
#ifdef HAVE_SOLOUD
	"SoLoud",
#endif
#ifdef HAVE_SDL2_MIXER_EXT
	"SDL2 Mixer X",
#endif
};

void audio_system_init() {
	switch (config.audio_backend) {
#ifdef HAVE_SOLOUD
	case AUDIO_SOLOUD:
		debug_log("Using SoLoud audio backend\n");
		audio_init = audio_soloud_init;
		audio_pause = audio_soloud_pause;
		audio_resume = audio_soloud_resume;
		audio_set_global_volume = audio_soloud_set_global_volume;
		audio_track_play = audio_soloud_track_play;
		audio_voice_track_play = audio_soloud_voice_track_play;
		audio_track_stop = audio_soloud_track_stop;
		audio_track_set_volume = audio_soloud_track_set_volume;
		audio_track_fade = audio_soloud_track_fade;
		audio_sound_load = audio_soloud_sound_load;
		audio_sound_play = audio_soloud_sound_play;
		break;
#endif
#ifdef HAVE_SDL2_MIXER_EXT
	case AUDIO_SDL2_MIXER_EXT:
		debug_log("Using SDL2 Mixer X audio backend\n");
		audio_init = audio_sdl2_init;
		audio_pause = audio_sdl2_pause;
		audio_resume = audio_sdl2_resume;
		audio_set_global_volume = audio_sdl2_set_global_volume;
		audio_track_play = audio_sdl2_track_play;
		audio_voice_track_play = audio_sdl2_voice_track_play;
		audio_track_stop = audio_sdl2_track_stop;
		audio_track_set_volume = audio_sdl2_track_set_volume;
		audio_track_fade = audio_sdl2_track_fade;
		audio_sound_load = audio_sdl2_sound_load;
		audio_sound_play = audio_sdl2_sound_play;
		break;
#endif
	default:
		debug_log("Invalid audio backend\n");
		break;
	}
}