#ifndef __ENGINE_H__
#define __ENGINE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "games.h"
#include "unzip.h"

#define ENGINE_VER "1.0.0"

#define NUM_AUDIO_SAMPLES 32

#define Color4(x) ImVec4(x[0], x[1], x[2], x[3])
#define set_theme_color(x, a, b, c, d) \
	x[0] = a; x[1] = b; x[2] = c; x[3] = d;

enum {
	LANG_JA,
	LANG_EN,
	LANG_FR,
	LANG_ES,
	LANG_DE,
	LANG_IT,
	LANG_NL,
	LANG_PT,
	LANG_RU,
	LANG_KO,
	LANG_CH_S,
	LANG_CH_T,
	LANG_FI,
	LANG_SW,
	LANG_DA,
	LANG_NW,
	LANG_PL,
	LANG_PT_BR,
	LANG_EN_UK,
	LANG_TR,
	LANG_UK,
	LANG_HE,
	LANG_HU,
	LANG_AR
};

typedef struct {
	void *src;
	float volume;
	int handle;
	uint8_t active;
} audio_sample;

typedef struct {
	int subtitles;
	float master_volume;
	float music_volume;
	int language;
} engine;

typedef struct subtitle {
	char text[128];
	uint32_t start;
	uint32_t end;
	uint32_t is_italic;
	struct subtitle *next;
} subtitle;

typedef struct subs_window {
	float x;
	float y;
	float w;
	float h;
} subs_window;

enum {
	EVENT_ONESHOT,
	EVENT_DURATION
};

enum {
	BAR_DEFAULT,
	BAR_CENTER_FILL,
	BAR_CIRCULAR
};

enum {
	CHOICES_CENTER_POS,
	CHOICES_FIXED_POS
};

struct sequence;
typedef struct {
	uint32_t start;
	uint32_t end;
	uint8_t type;
	struct sequence *(*s)();
} timed_event;

typedef struct sequence {
#ifdef DEBUG
	char name[32];
#endif
	char hash[64];
	struct sequence *links[8];
	struct sequence *(*d)();
	struct sequence *(*l)();
	struct sequence *(*r)();
	struct sequence *(*e)();
	char *(*ltext)();
	char *(*rtext)();
	char *(*etext)();
	uint32_t jump_time;
	uint32_t start;
	uint32_t end;
	timed_event events[64];
	subtitle subs[128];
	int sub_lang;
	int num_subs;
	int num_events;
} sequence;

typedef struct {
	float btn_bg[4];
	float btn_hover_bg[4];
	float bar_bg[4];
	float bar[4];
	float text[4];
	float btn_text[4];
	float shadow_text[4];
	float btn_hover_text[4];
	float popup_bg[4];
	uint8_t bar_type;
	uint8_t choices_type;
	float choice1[2]; // x, y
	float choice2[2]; // x, y
	float choice3[2]; // x, y
	float choice_bar[4]; // x, y, len/radius, thickness
} theme;

enum {
	BTNS_DONE,
	BTNS_CALC_SIZE
};

enum {
	GAME_ACTIVE,
	GAME_EXITING,
	GAME_RESUMING
};

#define LOOP_SEQUENCE ((sequence *(*)())0xDEADBEEF)

extern theme colors;
extern sequence sequences[NUM_SEQUENCES];
extern char game_strings[NUM_GAME_STRINGS][128];
extern audio_sample bgm[NUM_AUDIO_SAMPLES];
extern sequence *cur_seq;
extern subtitle *cur_sub;
extern int fake_pass;
extern int chosen_path;
extern int trigger_save;
extern int btns_state;
extern int cur_event;
extern int game_state;
extern uint32_t cur_delta;
extern unzFile sub_handle;
extern engine config;
extern subs_window subs_win;

extern void *snd_click;
extern void *snd_hover;
extern void *snd_pause;
extern void *snd_unpause;

void load_animated_bg(const char *fname, int needs_hash);
uint32_t load_image(const char *fname);
void free_image(uint32_t image);
void fill_sequence(char *name, sequence *s, sequence *(*d)(), char *(*ltext)(), char *(*rtext)(), char *(*etext)(), sequence *(*l)(), sequence *(*r)(), sequence *(*e)(), uint32_t start, uint32_t end, uint32_t jump);
void start_sequence(sequence *s);
void start_first_sequence(sequence *s);
void install_timed_event(sequence *t, uint32_t start, uint32_t end, uint8_t type, sequence *(*s)());
void load_subtitles(sequence *s);
void reload_subtitles(sequence *s);
void start_subs_loader();
void set_subs_window(float x, float y, float w, float h);

void spooky_hash128(const void *buf, int len, char *out);

void menu_setup();
void game_main_menu();
void game_pause_menu(int *state);
void game_setup();
void game_prepare();

audio_sample *audio_sample_start(const char *fname, int looping, float vol);
audio_sample *audio_voice_sample_start(const char *fname, int looping, float vol);
void audio_sample_stop(audio_sample *s);
void audio_sample_stop_all();
void audio_sample_reset_volume_all();

#ifdef DEBUG
#define debug_log printf
#else
#define debug_log
#endif

#define audio_sample_fade(s, vs, vd, ts, td) \
	if (s) { \
		float new_vol = audio_track_fade(s->handle, vs, vd, ts, td); \
		s->volume = new_vol; \
	}
		
#define audio_sample_set_volume(s, v) \
	if (s) { \
		audio_track_set_volume(s->handle, v); \
		s->volume = v; \
	}

#define audio_sample_stop_and_free(s) \
	audio_sample_stop(s); s = NULL; \

#ifdef __cplusplus
}
#endif

#endif