#ifndef __AUDIO_H__
#define __AUDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

void audio_init();
void *audio_play(const char *fname, int looping, float vol, int *h);
void audio_stop(void *s);
void audio_set_volume(int h, float vol);
float audio_get_volume(int h);

#define audio_fade(m, volume_start, volume_end, time_start, time_end) \
	{ float volume_delta = volume_end - volume_start; \
	float time_delta = time_end - time_start; \
	float delta = cur_delta - time_start; \
	audio_set_volume(m, volume_start + (delta / time_delta) * volume_delta); }

#ifdef __cplusplus
}
#endif

#endif
