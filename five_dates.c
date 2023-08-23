// Five Dates gamecode reimplementation
#include <stdio.h>
#include <ctype.h>
#include <vitasdk.h>
#include <vitaGL.h>
#include "audio.h"
#include "draw.h"
#include "engine.h"
#include "five_dates.h"

#ifdef FIVE_DATES
char game_strings[NUM_GAME_STRINGS][128];

void fill_events() {
}

void fill_sequences() {
	// Creating sequences links
	// PROLOGUE
	fill_sequence("scene_goto_App", &sequences[0], NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // ad2c6a4b-85f4-4ba3-bb06-65be14e974e0
	
	fill_events();
}

int current_lang = -1;
int available_lang[] = {
	LANG_EN, // 0
	LANG_FR, // 1
	LANG_ES, // 2
	LANG_DE, // 3
	LANG_PT_BR, // 4
	LANG_RU, // 5
	LANG_TR, // 6
	// LANG_CH_S, // 7
	// LANG_KO, // 8
};

void load_localization_files(int lang) {
	if (sub_handle != NULL) {
		unzClose(sub_handle);
	}
	
	config.language = lang;
	FILE *f;
	switch (lang) {
	/*case LANG_KO:
		debug_log("Language: Korean\n");
		current_lang = 14;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/ko.zip");
		f = fopen("app0:data/lang/ko.str", "r");
		break;*/
	case LANG_TR:
		debug_log("Language: Turkish\n");
		current_lang = 6;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/tr.zip");
		f = fopen("app0:data/lang/tr.str", "r");
		break;
	case LANG_FR:
		debug_log("Language: French\n");
		current_lang = 1;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/fr.zip");
		f = fopen("app0:data/lang/fr.str", "r");
		break;
	case LANG_DE:
		debug_log("Language: German\n");
		current_lang = 3;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/de.zip");
		f = fopen("app0:data/lang/de.str", "r");
		break;
	case LANG_ES:
		debug_log("Language: Spanish\n");
		current_lang = 2;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/es.zip");
		f = fopen("app0:data/lang/es.str", "r");
		break;
	/*case LANG_CH_S:
		debug_log("Language: Simplified Chinese\n");
		current_lang = 12;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/zhs.zip");
		f = fopen("app0:data/lang/zhs.str", "r");
		break;*/
	case LANG_PT_BR:
	case LANG_PT:
		debug_log("Language: Portuguese\n");
		current_lang = 4;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/ptbr.zip");
		f = fopen("app0:data/lang/ptbr.str", "r");
		break;
	case LANG_RU:
		debug_log("Language: Russian\n");
		current_lang = 5;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/ru.zip");
		f = fopen("app0:data/lang/ru.str", "r");
		break;
	default:
		debug_log("Language: English\n");
		current_lang = 0;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/en.zip");
		f = fopen("app0:data/lang/en.str", "r");
		break;
	}
	
	// Loading game strings on memory
	int i = 0;
	while (fgets(game_strings[i], 128, f)) {
		if (game_strings[i][strlen(game_strings[i]) - 1] == '\n')
			game_strings[i][strlen(game_strings[i]) - 1] = 0;
		i++;
	}
	fclose(f);
}

void menu_setup() {
	// TODO: Reusing Late Shift one for now
	// Setting up engine theme for menu 
	set_theme_color(colors.btn_hover_bg, 0.0f, 0.0f, 0.0f, 0.0f);
	set_theme_color(colors.btn_bg, 0.0f, 0.0f, 0.0f, 0.0f);
	set_theme_color(colors.bar_bg, 0.62745f, 0.62745f, 0.62745f, 1.0f);
	set_theme_color(colors.bar, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.text, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.btn_text, 0.18431f, 0.18431f, 0.18431f, 1.0f);
	set_theme_color(colors.btn_hover_text, 1.0f, 1.0f, 1.0f, 1.0f);
}

void game_pause_menu(int *first_call) {
	// TODO
}

void game_main_menu() {
	// TODO
	
	// Starting new game
	debug_log("Booting first sequence\n");
	// trigger_save = 1;
	sequence *out = &sequences[0];
	memset(&game_vars, 0, sizeof(gamestate));

	start_first_sequence(out);
}

void game_setup() {
	// TODO: Reusing Late Shift one for now
	// Setting up engine theme for game
	set_theme_color(colors.btn_hover_bg, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.btn_bg, 0.0f, 0.0f, 0.0f, 0.3f);
	set_theme_color(colors.bar_bg, 0.62745f, 0.62745f, 0.62745f, 1.0f);
	set_theme_color(colors.bar, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.text, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.btn_text, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.btn_hover_text, 0.0f, 0.0f, 0.0f, 1.0f);
}

void game_prepare() {
}

#endif

