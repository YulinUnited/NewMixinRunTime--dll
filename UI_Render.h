#pragma once
/*UI‰÷»æ£¨ø…—°*/
#include "Include.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct { unsigned char r, g, b, a; } Color;

extern const Color Color_White;
extern const Color Color_LightBlue;
extern const Color Color_DarkGray;
extern const Color Color_Gray;
extern const Color Color_Black;

extern uint32_t* framebuffer;
extern int screen_width;
extern int screen_height;

typedef void (*DrawTextCenteredFunc)(const char* text, int x, int y, int w, int h, Color color);
MixinRunTime_API void draw_rect(int x, int y, int w, int h, Color color);
MixinRunTime_API void draw_text_centered(const char* text, int x, int y, int w, int h, Color color);

MixinRunTime_API void ui_register_draw_text(DrawTextCenteredFunc Ffunc);

#ifdef __cplusplus
}
#endif