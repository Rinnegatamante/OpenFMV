#ifndef __AUDIO_H__
#define __AUDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

void audio_init();
void audio_pause();
void audio_resume();
void audio_set_global_volume(float vol);

void *audio_track_play(const char *fname, int looping, float vol, int *h);
void *audio_voice_track_play(const char *fname, int looping, float vol, int *h);
void audio_track_stop(void *s);
void audio_track_set_volume(int h, float vol);
float audio_track_get_volume(int h);
float audio_track_fade(int h, float volume_start, float volume_end, uint32_t time_start, uint32_t time_end);

void *audio_sound_load(const char *fname);
void audio_sound_play(void *s);

#ifdef __cplusplus
}
#endif

#endif
