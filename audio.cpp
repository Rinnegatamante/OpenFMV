#include <malloc.h>
#include <stdio.h>
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"
#include "engine.h"
#include "games.h"

SoLoud::Soloud soloud;

extern "C" {
	
void audio_init() {
	soloud.init(SoLoud::Soloud::CLIP_ROUNDOFF);
}

void audio_pause() {
	soloud.setPauseAll(1);
}

void audio_resume() {
	soloud.setPauseAll(0);
}

void *audio_track_play(const char *fname, int looping, float vol, int *handle) {
	char path[256];
	sprintf(path, "%s/%s.wav.ogg", AUDIO_FOLDER, fname);
	auto *w = new SoLoud::WavStream;
	w->load(path);
	w->setVolume(vol);
	w->setLooping(looping ? true : false);
	int h = soloud.play(*w, vol * config.music_volume);
	if (h)
		*handle = h;
	return w;
}

void audio_track_stop(void *s) {
	auto *w = (SoLoud::WavStream *)s;
	w->stop();
	delete w;
}

void audio_track_set_volume(int h, float vol) {
	soloud.setVolume(h, vol * config.music_volume);
}

float audio_track_fade(int h, float volume_start, float volume_end, uint32_t time_start, uint32_t time_end) {
	float volume_delta = volume_end - volume_start;
	float time_delta = time_end - time_start;
	float delta = cur_delta - time_start;
	float new_volume = volume_start + (delta / time_delta) * volume_delta;
	soloud.setVolume(h, new_volume * config.music_volume);
	return new_volume;
}

float audio_track_get_volume(int h) {
	return soloud.getVolume(h) / config.music_volume;
}

void *audio_sound_load(const char *fname) {
	auto *w = new SoLoud::Wav;
	w->load(fname);
	return w;
}

void audio_sound_play(void *s) {
	auto *w = (SoLoud::Wav *)s;
	soloud.play(*w);
}

void audio_set_global_volume(float vol) {
	soloud.setGlobalVolume(vol);
}

}
