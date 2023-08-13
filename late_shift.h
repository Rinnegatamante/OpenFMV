#ifndef __LATE_SHIFT_H__
#define __LATE_SHIFT_H__

#ifdef LATE_SHIFT
#define NUM_SEQUENCES 508
#define NUM_GAME_STRINGS 443
#define NUM_AUDIO_SOURCES 215
#define SAVE_FILE "ux0:data/Late Shift/progress.sav"
#define CONFIG_FILE "ux0:data/Late Shift/config.sav"
#define VIDEOS_FILE "ux0:data/Late Shift/Videos.psarc"
#define AUDIO_FOLDER "ux0:data/Late Shift/oggs"

#define GAME_VER "0.6.0"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	uint8_t has_pepper_spray;
	uint8_t know_about_party;
	uint8_t key_given;
	uint8_t cctv_seg;
	uint8_t with_lee;
	uint8_t elo_thinks;
	uint8_t coming_from_seg223;
	uint8_t may_likes_matt;
	uint8_t respect_earned;
	uint8_t sabotage;
	uint8_t intervened;
	uint8_t sold_for;
	uint8_t gone_upstairs;
	uint8_t passed_by_seg341;
	uint8_t lockdown;
	uint8_t security_alert;
	uint8_t blank_book;
	uint8_t gone_to_woe;
	uint8_t has_cookie;
	uint8_t report_to_police;
	uint8_t matt_escape;
} gamestate;

extern gamestate game_vars;

void fill_sequences();
void load_localization_files(int lang);

#ifdef __cplusplus
}
#endif

#endif

#endif
