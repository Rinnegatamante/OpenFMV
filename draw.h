#ifndef __DRAW_H__
#define __DRAW_H__

#ifdef __cplusplus
extern "C" {
#endif

int draw_video_frame();
int draw_button(float x, float y, const char *label, int *state);
int draw_main_button(float x, float y, const char *label, int *state);
void draw_text(float x, float y, const char *label, float *clr);
void draw_centered_text(float y, const char *label);
int draw_selector(float x, float y, const char *label, int *state, int *select, int max);
int draw_fast_selector(float x, float y, const char *label, int *state, int *select, int max);
void draw_progressbar(float x, float y, float w, float h, float val, char *label);
void draw_image(uint32_t image, float x, float y, float w, float h);

float calc_centered_button_pos(const char *label);

void init_menu(float alpha, float x, float y, float w, float h, const char *id);
void end_menu();
void init_ui_frame();
void end_ui_frame();

#ifdef __cplusplus
}
#endif

#endif
