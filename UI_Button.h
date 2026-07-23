#pragma once
/*UI°´Å¥£¬¿ÉÑ¡*/
#include "Include.h"

typedef enum {
    UI_BUTTON_NORMAL,
    UI_BUTTON_HOVERED,
    UI_BUTTON_PRESSED,
    UI_BUTTON_DISABLED
} UIButtonState;

typedef struct UIButton UIButton;

typedef void (*UIButtonClickCallback)(UIButton*);

struct UIButton {
    int x, y, width, height;
    const char* text;

    UIButtonState state;
    UIButtonClickCallback onClick;
    int enabled;
};

MixinRunTime_API void ui_button_init(UIButton* btn, int x, int y, int w, int h, const char* text);
MixinRunTime_API void ui_button_draw(const UIButton* btn);
MixinRunTime_API void ui_button_handle_mouse(UIButton* btn, int mx, int my, int down);
