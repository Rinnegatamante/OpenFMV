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

#define SUBTITLE_NEWLINE "\n\n"

#define GAME_VER "0.9.0"

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
	uint8_t radioplay_started;
	uint8_t may_kiss;
	uint8_t thumb_pain;
	uint8_t knife_long;
	uint8_t spit_in_the_face;
	uint8_t matt_alone_playing;
	uint8_t may_stabbed;
	uint8_t get_away_long_playing;
	uint8_t passed_by_seg326;
	uint8_t police_everywhere_playing;
	uint8_t cross_exam;
	uint8_t turned_away;
	uint8_t left_may_crying;
	uint8_t from_ep7_to_ep11;
	uint8_t from_ep9_to_ep11;
	uint8_t finish_ep7_target;
	uint8_t passed_by_seg765;
	uint8_t know_trojan;
	uint8_t mentioned_trojan;
	uint8_t got_keycard;
	uint8_t aware_of_chest;
	uint8_t payback_time;
	uint8_t called_parr;
	uint8_t torture_seb;
	uint8_t passed_by_seg975;
	uint8_t passed_by_seg739;
} gamestate;

extern gamestate game_vars;

void fill_sequences();
void load_localization_files(int lang);

#ifdef __cplusplus
}
#endif

#endif

#endif
