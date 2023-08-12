#include <malloc.h>
#include <stdio.h>
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"
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
	int h = soloud.play(*w, vol);
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
	soloud.setVolume(h, vol);
}

float audio_track_get_volume(int h) {
	return soloud.getVolume(h);
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

}
