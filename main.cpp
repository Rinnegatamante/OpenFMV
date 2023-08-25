#include <string>
#include <stdio.h>
#include <ctype.h>
#include <vitasdk.h>
#include <vitaGL.h>
#include <imgui_vita.h>
#include <imgui_internal.h>
#include "audio.h"
#include "draw.h"
#include "engine.h"
#include "games.h"
#include "fios.h"
#include "player.h"
#include "unzip.h"
#include "trophies.h"

static uint32_t shadow_u32 = 0;

void ImGui_CircleBar(float radius, float thickness, float progress, ImVec4 color) {
	int num_segments = 20;
	ImGuiWindow *window = ImGui::GetCurrentWindow();
	ImVec2 pos = window->DC.CursorPos;
	const ImRect bb{pos, ImVec2(pos.x + radius * 2, pos.y + radius * 2)};
	ImGui::ItemSize(bb);
	if (!ImGui::ItemAdd(bb, 0))
		return;
	window->DrawList->PathClear();
	const float a_max = progress * 6.5f;
	ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius);
	window->DrawList->PathArcTo(centre, radius - 0.5f, 4.71f, 4.71f + a_max, num_segments - 1);
	window->DrawList->PathStroke(ImGui::GetColorU32(color), false, thickness);
}

int _newlib_heap_size_user = 256 * 1024 * 1024;

void ImGui_TextCentered(char *text) {
    auto wS = ImGui::GetWindowSize();
    auto tS = ImGui::CalcTextSize(text);
	
	char *newline = strstr(text, "\n");
	if (newline) {
		newline[0] = 0;
		auto lX = ImGui::CalcTextSize(text);
		ImGui::SetCursorPos(ImVec2((wS.x - lX.x) * 0.5f, (wS.y - tS.y) * 0.5f));
		ImGui::Text(text);
		auto lX2 = ImGui::CalcTextSize(&newline[1]);
		ImGui::SetCursorPos(ImVec2((wS.x - lX2.x) * 0.5f, (wS.y - tS.y) * 0.5f + lX.y));
		ImGui::Text(&newline[1]);
		newline[0] = '\n';
	} else {
		ImGui::SetCursorPos(ImVec2((wS.x - tS.x) * 0.5f, (wS.y - tS.y) * 0.5f));
		ImGui::Text(text);
	}
}

void reload_theme() {
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_ButtonHovered] = Color4(colors.btn_hover_bg);
	style.Colors[ImGuiCol_Button] = Color4(colors.btn_bg);
	style.Colors[ImGuiCol_FrameBg] = Color4(colors.bar_bg);
	style.Colors[ImGuiCol_PlotHistogram] = Color4(colors.bar);
	style.Colors[ImGuiCol_Text] = Color4(colors.text);
	style.Colors[ImGuiCol_WindowBg] = Color4(colors.popup_bg);
	shadow_u32 = (uint32_t)(colors.shadow_text[0] * 255.0f) | (uint32_t)(colors.shadow_text[1] * 255.0f) << 8 | (uint32_t)(colors.shadow_text[2] * 255.0f) << 16 | (uint32_t)(colors.shadow_text[3] * 255.0f) << 24;
}

void warning(const char *msg) {
	SceMsgDialogUserMessageParam msg_param;
	sceClibMemset(&msg_param, 0, sizeof(SceMsgDialogUserMessageParam));
	msg_param.buttonType = SCE_MSG_DIALOG_BUTTON_TYPE_OK;
	msg_param.msg = (const SceChar8*)msg;
	SceMsgDialogParam param;
	sceMsgDialogParamInit(&param);
	param.mode = SCE_MSG_DIALOG_MODE_USER_MSG;
	param.userMsgParam = &msg_param;
	sceMsgDialogInit(&param);
	while (sceMsgDialogGetStatus() != SCE_COMMON_DIALOG_STATUS_FINISHED) {
		vglSwapBuffers(GL_TRUE);
	}
	sceMsgDialogTerm();
}

int main(int argc, char *argv[]) {
	// Mounting PSARC archive for videos
	fios_init();
	
	// Mounting subtitles file and strings file based on system language
	SceAppUtilInitParam appUtilParam;
	SceAppUtilBootParam appUtilBootParam;
	memset(&appUtilParam, 0, sizeof(SceAppUtilInitParam));
	memset(&appUtilBootParam, 0, sizeof(SceAppUtilBootParam));
	sceAppUtilInit(&appUtilParam, &appUtilBootParam);
	FILE *f = fopen(CONFIG_FILE, "rb");
	if (f) {
		fread(&config, 1, sizeof(engine), f);
		fclose(f);
	} else {
		config.subtitles = 1;
		config.master_volume = 1.0f;
		config.music_volume = 1.0f;
		sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_LANG, &config.language);
	}
	audio_set_global_volume(config.master_volume);
	load_localization_files(config.language);
	
	// Initing vitaGL and video player
	scePowerSetArmClockFrequency(444);
	scePowerSetBusClockFrequency(222);
	vglInitWithCustomThreshold(0, 960, 544, 16 * 1024 * 1024, 32 * 1024 * 1024, 0, 26 * 1024 * 1024, SCE_GXM_MULTISAMPLE_NONE);
	sceSysmoduleLoadModule(SCE_SYSMODULE_AVPLAYER);

#ifdef HAVE_TROPHIES
	// Initing trophy system
	SceIoStat st;
	int r = trophies_init();
	if (r < 0 && sceIoGetstat(TROPHIES_FILE, &st) < 0) {
		FILE *f = fopen(TROPHIES_FILE, "w");
		fclose(f);
		warning("This game features unlockable trophies but NoTrpDrm is not installed. If you want to be able to unlock trophies, please install it.");
	}
#endif

	// Initing audio player and menu audio sounds
	audio_init();
	snd_hover = audio_sound_load("app0:data/menu_move.ogg");
	snd_click = audio_sound_load("app0:data/menu_click.ogg");
	snd_pause = audio_sound_load("app0:data/menu_pause.ogg");
	snd_unpause = audio_sound_load("app0:data/menu_unpause.ogg");
	
	// Initializing dear ImGui
	static const ImWchar compact_ranges[] = { // All languages except chinese
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0100, 0x024F, // Latin Extended
		0x0370, 0x03FF, // Greek
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x0590, 0x05FF, // Hebrew
		0x0900, 0x09FF, // Punctuation
		0x2000, 0x206F, // General Punctuation
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0,
	};
	ImGui::CreateContext();
	ImFont *fnt_normal = ImGui::GetIO().Fonts->AddFontFromFileTTF("app0:data/normal.ttf", 24.0f, NULL, compact_ranges);
	ImFont *fnt_italic = ImGui::GetIO().Fonts->AddFontFromFileTTF("app0:data/italic.ttf", 24.0f, NULL, compact_ranges);
	ImGui_ImplVitaGL_Init_Extended();
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 0.0f;
	style.WindowRounding = 1.0f;
	style.FrameRounding = 5.0f;
	style.ItemSpacing.y = 16.0f;
	style.ItemSpacing.x = 32.0f;
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	ImGui::GetIO().MouseDrawCursor = false;
	ImGui::GetCurrentContext()->NavDisableMouseHover = false;
	ImGui_ImplVitaGL_TouchUsage(false);
	ImGui_ImplVitaGL_GamepadUsage(true);
	ImGui_ImplVitaGL_MouseStickUsage(false);
	sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_STOP);
	bool btn1_hovered = false;
	bool btn2_hovered = false;
	bool btn3_hovered = false;
	int pause_menu_triggered = 0;
	
	// Starting subtitles loader worker thread
	start_subs_loader();
	
	// Populating sequences tree
	fill_sequences();
	
	// Loading menu engine theme
main_menu:
	menu_setup();
	reload_theme();
	
	// Main Menu
	game_main_menu();
	
	// Loading in-game engine theme and setting up game for boot
	game_setup();
	reload_theme();
	game_prepare();
	
	// Main Loop
	game_state = GAME_ACTIVE;
	ImVec2 btn1_size = ImVec2(0, 0);
	ImVec2 btn2_size = ImVec2(0, 0);
	ImVec2 btn3_size = ImVec2(0, 0);
	for (;;) {
		// Input handling
		static uint32_t oldpad = 0;
		SceCtrlData pad;
		sceCtrlPeekBufferPositive(0, &pad, 1);
		if ((pad.buttons & SCE_CTRL_START) && !(oldpad & SCE_CTRL_START)) {
			if (player_state == PLAYER_ACTIVE) {
				video_pause();
				audio_pause();
				pause_menu_triggered = 1;
			} else {
				video_resume();
				audio_resume();
			}
		}
#ifdef DEBUG
		#define FAST_SKIP_MS 5000
		if ((pad.buttons & SCE_CTRL_LTRIGGER) && !(oldpad & SCE_CTRL_LTRIGGER)) {
			video_jump_to_time(cur_delta > FAST_SKIP_MS ? (cur_delta - FAST_SKIP_MS) : 0);
		} else if ((pad.buttons & SCE_CTRL_RTRIGGER) && !(oldpad & SCE_CTRL_RTRIGGER)) {
			video_jump_to_time(cur_delta + FAST_SKIP_MS);
		}
#endif
		
		// Draw current video frame
		if (draw_video_frame()) {
			ImGui::GetIO().NavVisible = true;
			ImGui::GetIO().NavActive = true;
			ImGui::GetCurrentContext()->NavDisableHighlight = false;
			ImGui_ImplVitaGL_NewFrame();
subtitle_draw:
			cur_delta = video_get_current_time();
			if (shadow_u32) {
				ImGui::PushFontShadow(shadow_u32);
			}
			if (config.subtitles && cur_sub) {
				if (cur_delta > cur_sub->start) {
					// Go to next subtitle
					if (cur_delta > cur_sub->end) {
						cur_sub = cur_sub->next;
						goto subtitle_draw;
					}
					
					// Draw current subtitle
					ImGui::SetNextWindowBgAlpha(0.0f);
					ImGui::SetNextWindowPos(ImVec2(subs_win.x, subs_win.y), ImGuiSetCond_Always);
					ImGui::SetNextWindowSize(ImVec2(subs_win.w, subs_win.h), ImGuiSetCond_Always);
					ImGui::Begin("##sub", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);
					ImGui::PushFont(cur_sub->is_italic ? fnt_italic : fnt_normal);
					ImGui_TextCentered(cur_sub->text);
					ImGui::PopFont();
					ImGui::End();
				}
			}
			ImGui::PopFontShadow();
			
			// Draw choices
			if (cur_seq->l) {
				char *ltext = cur_seq->ltext();
				if (!ltext) {
					goto skip_choices;
				}
				
				// Precalculate once buttons sizes for properly centering them
				if (btns_state == BTNS_CALC_SIZE && colors.choices_type == CHOICES_CENTER_POS) {
					ImGui::Begin("##fake", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);
					ImGui::SetCursorPosX(-10000.0f);
					ImGui::Button(ltext, ImVec2(ImGui::CalcTextSize(ltext).x + 20.0f, 1.0f));
					btn1_size = ImGui::GetItemRectSize();
					ImGui::SetCursorPosX(-10000.0f);
					ImGui::Button(cur_seq->rtext(), ImVec2(ImGui::CalcTextSize(cur_seq->rtext()).x + 20.0f, 1.0f));
					btn2_size = ImGui::GetItemRectSize();
					btn3_size = ImVec2(0, 0);
					if (cur_seq->e) {
						char *etext = cur_seq->etext();
						if (etext) {
							ImGui::SetCursorPosX(-10000.0f);
							ImGui::Button(etext, ImVec2(ImGui::CalcTextSize(etext).x + 20.0f, 1.0f));
							btn3_size = ImGui::GetItemRectSize();
							btn3_size.x += + style.ItemSpacing.x;
						}
					}
					ImGui::End();
					btns_state = BTNS_DONE;
					ImGui::GetCurrentContext()->NavId = 0;
				}
			
				if (cur_delta > cur_seq->start && cur_delta < cur_seq->end && !chosen_path) {		
					ImGui::SetNextWindowFocus();				
					ImGui::SetNextWindowBgAlpha(0.0f);
					ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
					ImGui::SetNextWindowSize(ImVec2(960, 544), ImGuiSetCond_Always);
					ImGui::Begin("##choice", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
					ImGui::PushFont(fnt_normal);
					
					// Draw buttons
					if (colors.choices_type == CHOICES_CENTER_POS) {
						ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - (btn1_size.x + btn2_size.x + btn3_size.x + style.ItemSpacing.x)) * 0.5f, colors.choice1[1]));
					} else {
						ImGui::SetCursorPos(ImVec2(colors.choice1[0], colors.choice1[1]));
					}
					ImGui::PushStyleColor(ImGuiCol_Text, btn1_hovered ? Color4(colors.btn_hover_text) : Color4(colors.btn_text));
					ImGui::PushStyleColor(ImGuiCol_Button, btn1_hovered ? Color4(colors.btn_hover_bg) : Color4(colors.btn_bg));
					if (ImGui::Button(ltext, ImVec2(ImGui::CalcTextSize(ltext).x + 20.0f, 40.0f))) {
						chosen_path = 1;
					}
					if (ImGui::IsItemFocused()) {
						btn1_hovered = true;
					} else {
						btn1_hovered = false;
					}
					if (!ImGui::IsAnyItemFocused()) {
						ImGui::SetKeyboardFocusHere();
						ImGui::GetCurrentContext()->NavWindow = ImGui::GetCurrentContext()->CurrentWindow;
						ImGui::GetCurrentContext()->NavId = ImGui::GetCurrentContext()->CurrentWindow->DC.LastItemId;
					}
					ImGui::PopStyleColor(2);
					if (colors.choices_type == CHOICES_CENTER_POS) {
						ImGui::SameLine();
					} else {
						ImGui::SetCursorPos(ImVec2(colors.choice2[0], colors.choice2[1]));
					}
					ImGui::PushStyleColor(ImGuiCol_Text, btn2_hovered ? Color4(colors.btn_hover_text) : Color4(colors.btn_text));
					if (ImGui::Button(cur_seq->rtext(), ImVec2(ImGui::CalcTextSize(cur_seq->rtext()).x + 20.0f, 40.0f))) {
						chosen_path = 2;
					}
					if (ImGui::IsItemFocused()) {
						btn2_hovered = true;
					} else {
						btn2_hovered = false;
					}
					ImGui::PopStyleColor();
					if (cur_seq->e) {
						char *etext = cur_seq->etext();
						if (etext) {
							if (colors.choices_type == CHOICES_CENTER_POS) {
								ImGui::SameLine();
							} else {
								ImGui::SetCursorPos(ImVec2(colors.choice3[0], colors.choice3[1]));
							}
							ImGui::PushStyleColor(ImGuiCol_Text, btn3_hovered ? Color4(colors.btn_hover_text) : Color4(colors.btn_text));
							if (ImGui::Button(etext, ImVec2(ImGui::CalcTextSize(etext).x + 20.0f, 40.0f))) {
								chosen_path = 3;
							}
							if (ImGui::IsItemFocused()) {
								btn3_hovered = true;
							} else {
								btn3_hovered = false;
							}
							ImGui::PopStyleColor();
						}
					}
					ImGui::PopFont();
					ImGui::GetCurrentContext()->NavDisableHighlight = false;
					
					// Draw remaining time bar
					if (cur_seq->d != LOOP_SEQUENCE) {
						float progress = (float)(cur_delta - cur_seq->start) / (float)(cur_seq->end - cur_seq->start);
						float half_width;
						switch (colors.bar_type) {
						case BAR_DEFAULT:
							ImGui::SetCursorPos(ImVec2(colors.choice_bar[0], colors.choice_bar[1]));
							ImGui::ProgressBar(progress, ImVec2(colors.choice_bar[2], colors.choice_bar[3]), "");
							break;
						case BAR_CENTER_FILL:
							half_width = colors.choice_bar[2] / 2.0f;
							ImGui::SetCursorPos(ImVec2(colors.choice_bar[0] + (half_width - 1.0f), colors.choice_bar[1]));
							ImGui::ProgressBar(progress, ImVec2(half_width, colors.choice_bar[3]), "##p1");
							ImGui::SameLine();
							ImGui::SetCursorPosX(colors.choice_bar[0]);
							ImGui::PushStyleColor(ImGuiCol_FrameBg, Color4(colors.bar));
							ImGui::PushStyleColor(ImGuiCol_PlotHistogram, Color4(colors.bar_bg));
							ImGui::ProgressBar(1.0f - progress, ImVec2(half_width, colors.choice_bar[3]), "##p2");
							ImGui::PopStyleColor(2);
							break;
						case BAR_CIRCULAR:
							ImGui::SetCursorPos(ImVec2(colors.choice_bar[0], colors.choice_bar[1]));
							ImGui_CircleBar(colors.choice_bar[2], colors.choice_bar[3], 1.0f, Color4(colors.bar_bg));
							ImGui::SetCursorPos(ImVec2(colors.choice_bar[0], colors.choice_bar[1]));
							ImGui_CircleBar(colors.choice_bar[2], colors.choice_bar[3], progress, Color4(colors.bar));
							break;
						default:
							debug_log("Fatal Error: Invalid bar type\n");
							break;
						}
					}
					ImGui::End();
				}
			}
skip_choices:			
			// Draw pause menu
			if (player_state == PLAYER_PAUSED) {
				menu_setup();
				reload_theme();
				game_pause_menu(&pause_menu_triggered);
				game_setup();
				reload_theme();
			}

			// Update display
			glViewport(0, 0, static_cast<int>(ImGui::GetIO().DisplaySize.x), static_cast<int>(ImGui::GetIO().DisplaySize.y));
			ImGui::Render();
			ImGui_ImplVitaGL_RenderDrawData(ImGui::GetDrawData());
			vglSwapBuffers(GL_FALSE);
			sceKernelPowerTick((SceKernelPowerTickType)0);
			
			// Handle game state changes
			switch (game_state) {
			case GAME_EXITING:
				audio_sample_stop_all();
				video_resume();
				video_close();
				goto main_menu;
			case GAME_RESUMING:
				video_resume();
				audio_resume();
				game_state = GAME_ACTIVE;
				break;
			default:
				break;
			}
			
handle_event:
			// Handle timed events
			if (cur_event < cur_seq->num_events) {
				if (cur_delta >= cur_seq->events[cur_event].start) {
					if (cur_seq->events[cur_event].type == EVENT_ONESHOT) {
						sequence *t = cur_seq->events[cur_event].s();
						if (t)
							start_sequence(t);
						cur_event++;
						goto handle_event;
					} else {
						if (cur_delta <= cur_seq->events[cur_event].end) {
							sequence *t = cur_seq->events[cur_event].s();
							if (t)
								start_sequence(t);
						} else {
							cur_event++;
							goto handle_event;
						}
					}
				}
			}
			
			// Starting chosen sequence
			if (chosen_path && (cur_delta > cur_seq->jump_time)) {
				switch (chosen_path) {
				case 1:
					start_sequence(cur_seq->l());
					break;
				case 2:
					start_sequence(cur_seq->r());
					break;
				case 3:
					start_sequence(cur_seq->e());
					break;
				default:
					debug_log("Fatal Error: Invalid chosen path.\n");
					break;
				}
			}
		}
		
		// Auto-select default choice if player gives no input
		if (player_state == PLAYER_INACTIVE) {
			if (cur_seq->d) {
				start_sequence(cur_seq->d());
			} else { // If no default choice is set, we return to main menu
				audio_sample_stop_all();
				goto main_menu;
			}
		}
		
		oldpad = pad.buttons;
	}
}