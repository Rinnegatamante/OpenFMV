#ifndef __FIVE_DATES_H__
#define __FIVE_DATES_H__

#ifdef FIVE_DATES
#define NUM_SEQUENCES 765
#define NUM_GAME_STRINGS 899
#define PLAYTHROUGH_SAVE_FILE "ux0:data/Late Shift/progress.sav"
#define GLOBAL_SAVE_FILE "ux0:data/Late Shift/unlocks.sav"
#define CONFIG_FILE "ux0:data/Five Dates/config.sav"
#define VIDEOS_FILE "ux0:data/Five Dates/Videos.psarc"
#define AUDIO_FOLDER "ux0:data/Five Dates/oggs"
#define SUBTITLE_NEWLINE "\n\n"

#define GAME_VER "0.0.1"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	uint8_t TODO;
} playstate;

typedef struct {
	uint8_t TODO;
} gamestate;

void fill_sequences();
void load_localization_files(int lang);

#ifdef __cplusplus
}
#endif

#endif

#endif
