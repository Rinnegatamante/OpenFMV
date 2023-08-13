#ifndef _PLAYER_H
#define _PLAYER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <vitaGL.h>

enum {
	PLAYER_INACTIVE,
	PLAYER_ACTIVE,
	PLAYER_PAUSED,
};

extern int player_state;

void video_open(const char *path, int looping);
GLuint video_get_frame(int *width, int *height);
uint32_t video_get_current_time();
void video_close();
void video_pause();
void video_resume();
void video_set_volume(float vol);

#ifdef __cplusplus
}
#endif

#endif