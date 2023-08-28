#ifdef HAVE_ALMIXER
#include <malloc.h>
#include <stdio.h>
#include <ALmixer.h>
#include "engine.h"
#include "games.h"

extern "C" {
	
void audio_almixer_init() {
	ALmixer_Init(44100, 0, 0);
}

void audio_almixer_pause() {
	ALmixer_SuspendPlayingState();
}

void audio_almixer_resume() {
	ALmixer_ResumePlayingState();
}

void *audio_almixer_track_play(const char *fname, int looping, float vol, int *handle) {
	char path[256];
	sprintf(path, "%s/%s.wav.ogg", AUDIO_FOLDER, fname);
	ALmixer_Data *res = ALmixer_LoadStream(fname, ALMIXER_DEFAULT_BUFFERSIZE, ALMIXER_DEFAULT_QUEUE_BUFFERS, ALMIXER_DEFAULT_STARTUP_BUFFERS, ALMIXER_DEFAULT_BUFFERS_TO_QUEUE_PER_UPDATE_PASS, AL_FALSE);
	*handle = ALmixer_PlayChannel(-1, res, 0);
	ALmixer_SetVolumeChannel(*handle, vol * config.music_volume);
	return res;
}

void *audio_almixer_voice_track_play(const char *fname, int looping, float vol, int *handle) {
	char path[256];
	sprintf(path, "%s/%s.wav.ogg", AUDIO_FOLDER, fname);
	ALmixer_Data *res = ALmixer_LoadStream(fname, ALMIXER_DEFAULT_BUFFERSIZE, ALMIXER_DEFAULT_QUEUE_BUFFERS, ALMIXER_DEFAULT_STARTUP_BUFFERS, ALMIXER_DEFAULT_BUFFERS_TO_QUEUE_PER_UPDATE_PASS, AL_FALSE);
	*handle = ALmixer_PlayChannel(-1, res, 0);
	ALmixer_SetVolumeChannel(*handle, vol);
	return res;
}

void audio_almixer_track_stop(void *s, int handle) {
	ALmixer_HaltChannel(handle);
	ALmixer_FreeData((ALmixer_Data *)s);
}

void audio_almixer_track_set_volume(int h, float vol) {
	ALmixer_SetVolumeChannel(h, vol * config.music_volume);
}

float audio_almixer_track_fade(int h, float volume_start, float volume_end, uint32_t time_start, uint32_t time_end) {
	float volume_delta = volume_end - volume_start;
	float time_delta = time_end - time_start;
	float delta = cur_delta - time_start;
	float new_volume = volume_start + (delta / time_delta) * volume_delta;
	ALmixer_SetVolumeChannel(h, new_volume * config.music_volume);
	return new_volume;
}

void *audio_almixer_sound_load(const char *fname) {
	return ALmixer_LoadAll(fname, AL_FALSE);
}

void audio_almixer_sound_play(void *s) {
	ALmixer_PlayChannel(-1, (ALmixer_Data *)s, 0);
}

void audio_almixer_set_global_volume(float vol) {
	ALmixer_SetMasterVolume(vol);
}

}
#endif
