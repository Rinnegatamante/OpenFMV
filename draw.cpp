#include <vitasdk.h>
#include <vitaGL.h>
#include <imgui_vita.h>
#include <imgui_internal.h>
#include <malloc.h>
#include <stdio.h>
#include "audio.h"
#include "draw.h"
#include "engine.h"
#include "fios.h"
#include "player.h"

#define MENU_INPUT_DELAY (300000) // Input delay in microseconds between two key presses

extern ImFont *fnt_italic;
extern ImFont *fnt_normal;

float *draw_attributes = NULL;
void draw_image(uint32_t image, float x, float y, float w, float h) {
	float x2 = x + w;
	float y2 = y + h;
	if (!draw_attributes)
		draw_attributes = (float*)malloc(sizeof(float) * 22);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, image);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	draw_attributes[0] = x;
	draw_attributes[1] = y;
	draw_attributes[2] = 0.0f;
	draw_attributes[3] = x2;
	draw_attributes[4] = y;
	draw_attributes[5] = 0.0f;
	draw_attributes[6] = x;
	draw_attributes[7] = y2;
	draw_attributes[8] = 0.0f;
	draw_attributes[9] = x2;
	draw_attributes[10] = y2;
	draw_attributes[11] = 0.0f;
	vglVertexPointerMapped(3, draw_attributes);
	
	draw_attributes[12] = 0.0f;
	draw_attributes[13] = 0.0f;
	draw_attributes[14] = 1.0f;
	draw_attributes[15] = 0.0f;
	draw_attributes[16] = 0.0f;
	draw_attributes[17] = 1.0f;
	draw_attributes[18] = 1.0f;
	draw_attributes[19] = 1.0f;
	vglTexCoordPointerMapped(&draw_attributes[12]);
	
	uint16_t *indices = (uint16_t*)&draw_attributes[20];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;
	vglIndexPointerMapped(indices);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0, 960, 544, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	vglDrawObjects(GL_TRIANGLE_STRIP, 4, GL_TRUE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDisableClientState(GL_COLOR_ARRAY);
}

int draw_video_frame() {
	if (!draw_attributes)
		draw_attributes = (float*)malloc(sizeof(float) * 22);

	int vid_w, vid_h;
	GLuint vid_frame = video_get_frame(&vid_w, &vid_h);
	if (vid_frame == 0xDEADBEEF)
		return 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, vid_frame);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	draw_attributes[0] = 0.0f;
	draw_attributes[1] = 0.0f;
	draw_attributes[2] = 0.0f;
	draw_attributes[3] = 960.0f;
	draw_attributes[4] = 0.0f;
	draw_attributes[5] = 0.0f;
	draw_attributes[6] = 0.0f;
	draw_attributes[7] = 544.0f;
	draw_attributes[8] = 0.0f;
	draw_attributes[9] = 960.0f;
	draw_attributes[10] = 544.0f;
	draw_attributes[11] = 0.0f;
	vglVertexPointerMapped(3, draw_attributes);
	
	draw_attributes[12] = 0.0f;
	draw_attributes[13] = 0.0f;
	draw_attributes[14] = 1.0f;
	draw_attributes[15] = 0.0f;
	draw_attributes[16] = 0.0f;
	draw_attributes[17] = 1.0f;
	draw_attributes[18] = 1.0f;
	draw_attributes[19] = 1.0f;
	vglTexCoordPointerMapped(&draw_attributes[12]);
	
	uint16_t *bg_indices = (uint16_t*)&draw_attributes[20];
	bg_indices[0] = 0;
	bg_indices[1] = 1;
	bg_indices[2] = 2;
	bg_indices[3] = 3;
	vglIndexPointerMapped(bg_indices);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0, 960, 544, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	vglDrawObjects(GL_TRIANGLE_STRIP, 4, GL_TRUE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDisableClientState(GL_COLOR_ARRAY);
	return 1;
}

void draw_text(float x, float y, const char *label, float *clr, float scale) {
	fnt_normal->Scale = scale;
	ImGui::PushFont(fnt_normal);
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::TextColored(Color4(clr), label);
	fnt_normal->Scale = 1.0f;
	ImGui::PopFont();
}

void draw_italic_text(float x, float y, const char *label, float *clr, float scale) {
	fnt_italic->Scale = scale;
	ImGui::PushFont(fnt_italic);
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::TextColored(Color4(clr), label);
	fnt_italic->Scale = 1.0f;
	ImGui::PopFont();
}

void draw_centered_text(float y, const char *label, float scale) {
	fnt_normal->Scale = scale;
	ImGui::PushFont(fnt_normal);
	ImGui::SetCursorPosY(y);
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth   = ImGui::CalcTextSize(label).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(label);
	fnt_normal->Scale = 1.0f;
	ImGui::PopFont();
}

void draw_centered_italic_text(float y, const char *label, float scale) {
	fnt_italic->Scale = scale;
	ImGui::PushFont(fnt_italic);
	ImGui::SetCursorPosY(y);
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth   = ImGui::CalcTextSize(label).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(label);
	fnt_italic->Scale = 1.0f;
	ImGui::PopFont();
}

int draw_button(float x, float y, const char *label, int *state) {
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::PushStyleColor(ImGuiCol_Text, *state ? Color4(colors.btn_hover_text) : Color4(colors.btn_text));
	ImGui::PushStyleColor(ImGuiCol_Button, *state ? Color4(colors.btn_hover_bg) : Color4(colors.btn_bg));
	int r = ImGui::Button(label, ImVec2(ImGui::CalcTextSize(label).x + 20.0f, 0.0f));
	if (ImGui::IsItemFocused()) {
		*state = 1;
	} else {
		*state = 0;
	}
	ImGui::PopStyleColor(2);
	if (r) {
		audio_sound_play(snd_click);
	}
	return r;
}

int draw_selector(float x, float y, const char *label, int *state, int *select, int max) {
	static uint32_t last_change_tick = 0;
	int res = 0;
	SceCtrlData pad;
	sceCtrlPeekBufferPositive(0, &pad, 1);
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::PushStyleColor(ImGuiCol_Text, *state ? Color4(colors.btn_hover_text) : Color4(colors.btn_text));
	ImGui::PushStyleColor(ImGuiCol_Button, *state ? Color4(colors.btn_hover_bg) : Color4(colors.btn_bg));
	ImGui::Button(label, ImVec2(ImGui::CalcTextSize(label).x + 20.0f, 0.0f));
	if (ImGui::IsItemFocused()) {
		*state = 1;
		if (pad.buttons & SCE_CTRL_LEFT) {
			uint32_t tick = sceKernelGetProcessTimeLow();
			if (tick - last_change_tick > MENU_INPUT_DELAY) {
				*select = *select - 1;
				if (*select < 0)
					*select = max - 1;
				res = 1;
				last_change_tick = tick;
				audio_sound_play(snd_hover);
			}
		} else if (pad.buttons & SCE_CTRL_RIGHT) {
			uint32_t tick = sceKernelGetProcessTimeLow();
			if (tick - last_change_tick > MENU_INPUT_DELAY) {
				*select = (*select + 1) % max;
				res = 1;
				last_change_tick = tick;
				audio_sound_play(snd_hover);
			}
		}
	} else {
		*state = 0; 
	}
	ImGui::PopStyleColor(2);
	return res;
}

int draw_fast_selector(float x, float y, const char *label, int *state, int *select, int max) {
	int res = 0;
	SceCtrlData pad;
	sceCtrlPeekBufferPositive(0, &pad, 1);
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::PushStyleColor(ImGuiCol_Text, *state ? Color4(colors.btn_hover_text) : Color4(colors.btn_text));
	ImGui::PushStyleColor(ImGuiCol_Button, *state ? Color4(colors.btn_hover_bg) : Color4(colors.btn_bg));
	ImGui::Button(label, ImVec2(ImGui::CalcTextSize(label).x + 20.0f, 0.0f));
	if (ImGui::IsItemFocused()) {
		*state = 1;
		if (pad.buttons & SCE_CTRL_LEFT) {
			*select = *select - 1;
			if (*select < 0) {
				*select = 0;
			} else {
				res = 1;
				audio_sound_play(snd_hover);
			}
		} else if (pad.buttons & SCE_CTRL_RIGHT) {
			*select = *select + 1;
			if (*select > max) {
				*select = max;
			} else {
				res = 1;
				audio_sound_play(snd_hover);
			}
		}
	} else {
		*state = 0; 
	}
	ImGui::PopStyleColor(2);
	return res;
}

void draw_progressbar(float x, float y, float w, float h, float val, char *label) {
	if (colors.bar_type == BAR_DEFAULT) {
		ImGui::SetCursorPos(ImVec2(x, y));
		ImGui::ProgressBar(val, ImVec2(w, h), label);
	} else {
		ImGui::SetCursorPos(ImVec2(x - 1.0f + x * 0.5, y));
		ImGui::ProgressBar(val, ImVec2(w / 2, h), label);
		ImGui::SetCursorPos(ImVec2(x + 1.0f + x * 0.5, y));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, Color4(colors.bar));
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, Color4(colors.bar_bg));
		ImGui::ProgressBar(1.0f - val, ImVec2(w, h), label);
		ImGui::PopStyleColor(2);
	}
}

int draw_main_button(float x, float y, const char *label, int *state) {
	int r = draw_button(x, y, label, state);
	if (!ImGui::IsAnyItemFocused()) {
		ImGui::SetKeyboardFocusHere();
		ImGui::GetCurrentContext()->NavWindow = ImGui::GetCurrentContext()->CurrentWindow;
		ImGui::GetCurrentContext()->NavId = ImGui::GetCurrentContext()->CurrentWindow->DC.LastItemId;
	}
	return r;
}

float calc_centered_button_pos(const char *label) {
	ImGui::SetNextWindowBgAlpha(0.0f);
	ImGui::Begin("##calc", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav);
	ImGui::SetCursorPosX(-10000.0f);
	ImGui::Button(label, ImVec2(ImGui::CalcTextSize(label).x + 20.0f, 0.0f));
	float w = ImGui::GetItemRectSize().x;
	ImGui::End();
	return (960.0f - w) * 0.5f;
}

void init_menu(float alpha, float x, float y, float w, float h, const char *id) {
	ImGui::SetNextWindowBgAlpha(alpha);
	ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiSetCond_Always);
	ImGui::Begin(id, nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
}

void end_menu() {
	ImGui::End();
}

void init_ui_frame() {
	ImGui::GetIO().NavVisible = true;
	ImGui::GetIO().NavActive = true;
	ImGui::GetCurrentContext()->NavDisableHighlight = false;
	ImGui_ImplVitaGL_NewFrame();
}

void end_ui_frame() {
	static ImGuiID old_id = 0;
	ImGuiID cur_id = ImGui::GetCurrentContext()->NavId;
	if (cur_id != old_id && cur_id != 0 && old_id != 0) {
		audio_sound_play(snd_hover);
	}
	old_id = cur_id;
	
	glViewport(0, 0, static_cast<int>(ImGui::GetIO().DisplaySize.x), static_cast<int>(ImGui::GetIO().DisplaySize.y));
	ImGui::Render();
	ImGui_ImplVitaGL_RenderDrawData(ImGui::GetDrawData());
}
