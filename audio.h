#ifndef __AUDIO_H__
#define __AUDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

enum {
#ifdef HAVE_SOLOUD
	AUDIO_SOLOUD,
#endif
#ifdef HAVE_SDL2_MIXER_EXT
	AUDIO_SDL2_MIXER_EXT,
#endif
	AUDIO_BACKENDS_NUM
};

extern char *audio_backends[];

extern void (*audio_init)();
extern void (*audio_pause)();
extern void (*audio_resume)();
extern void (*audio_set_global_volume)(float vol);
extern void *(*audio_track_play)(const char *fname, int looping, float vol, int *h);
extern void *(*audio_voice_track_play)(const char *fname, int looping, float vol, int *h);
extern void (*audio_track_stop)(void *s);
extern void (*audio_track_set_volume)(int h, float vol);
extern float (*audio_track_fade)(int h, float volume_start, float volume_end, uint32_t time_start, uint32_t time_end);
extern void *(*audio_sound_load)(const char *fname);
extern void (*audio_sound_play)(void *s);

void audio_system_init();

#ifdef HAVE_SDL2_MIXER_EXT
void audio_sdl2_init();
void audio_sdl2_pause();
void audio_sdl2_resume();
void audio_sdl2_set_global_volume(float vol);
void *audio_sdl2_track_play(const char *fname, int looping, float vol, int *h);
void *audio_sdl2_voice_track_play(const char *fname, int looping, float vol, int *h);
void audio_sdl2_track_stop(void *s);
void audio_sdl2_track_set_volume(int h, float vol);
float audio_sdl2_track_fade(int h, float volume_start, float volume_end, uint32_t time_start, uint32_t time_end);
void *audio_sdl2_sound_load(const char *fname);
void audio_sdl2_sound_play(void *s);
#endif

#ifdef HAVE_SOLOUD
void audio_soloud_init();
void audio_soloud_pause();
void audio_soloud_resume();
void audio_soloud_set_global_volume(float vol);
void *audio_soloud_track_play(const char *fname, int looping, float vol, int *h);
void *audio_soloud_voice_track_play(const char *fname, int looping, float vol, int *h);
void audio_soloud_track_stop(void *s);
void audio_soloud_track_set_volume(int h, float vol);
float audio_soloud_track_fade(int h, float volume_start, float volume_end, uint32_t time_start, uint32_t time_end);
void *audio_soloud_sound_load(const char *fname);
void audio_soloud_sound_play(void *s);
#endif

#ifdef __cplusplus
}
#endif

#endif
