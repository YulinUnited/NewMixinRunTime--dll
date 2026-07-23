#pragma once
/*Windows操作系统按键映射，按键映射，可选*/

//win按键映射，不代表其他硬件映射
typedef enum {
    KEY_NONE = 0,
    KEY_BACKSPACE = 0x08,
    KEY_TAB = 0x09,
    KEY_RETURN = 0x0D,
    KEY_SHIFT = 0x10,
    KEY_CONTROL = 0x11,
    KEY_MENU = 0x12,  // Alt键
    KEY_CAPSLOCK = 0x14,
    KEY_ESCAPE = 0x1B,

    // 空格和标点
    KEY_SPACE = 0x20,
    KEY_APOSTROPHE = 0xDE,  // '
    KEY_COMMA = 0xBC,       // ,
    KEY_MINUS = 0xBD,       // -
    KEY_PERIOD = 0xBE,      // .
    KEY_SLASH = 0xBF,       // /

    // 数字键
    KEY_0 = 0x30,
    KEY_1 = 0x31,
    KEY_2 = 0x32,
    KEY_3 = 0x33,
    KEY_4 = 0x34,
    KEY_5 = 0x35,
    KEY_6 = 0x36,
    KEY_7 = 0x37,
    KEY_8 = 0x38,
    KEY_9 = 0x39,

    // 字母键
    KEY_A = 0x41,
    KEY_B = 0x42,
    KEY_C = 0x43,
    KEY_D = 0x44,
    KEY_E = 0x45,
    KEY_F = 0x46,
    KEY_G = 0x47,
    KEY_H = 0x48,
    KEY_I = 0x49,
    KEY_J = 0x4A,
    KEY_K = 0x4B,
    KEY_L = 0x4C,
    KEY_M = 0x4D,
    KEY_N = 0x4E,
    KEY_O = 0x4F,
    KEY_P = 0x50,
    KEY_Q = 0x51,
    KEY_R = 0x52,
    KEY_S = 0x53,
    KEY_T = 0x54,
    KEY_U = 0x55,
    KEY_V = 0x56,
    KEY_W = 0x57,
    KEY_X = 0x58,
    KEY_Y = 0x59,
    KEY_Z = 0x5A,

    // 方向键
    KEY_LEFT = 0x25,
    KEY_UP = 0x26,
    KEY_RIGHT = 0x27,
    KEY_DOWN = 0x28,

    // 功能键
    KEY_F1 = 0x70,
    KEY_F2 = 0x71,
    KEY_F3 = 0x72,
    KEY_F4 = 0x73,
    KEY_F5 = 0x74,
    KEY_F6 = 0x75,
    KEY_F7 = 0x76,
    KEY_F8 = 0x77,
    KEY_F9 = 0x78,
    KEY_F10 = 0x79,
    KEY_F11 = 0x7A,
    KEY_F12 = 0x7B,

    // 鼠标键
    MOUSE_LEFT = 0x01,
    MOUSE_RIGHT = 0x02,
    MOUSE_MIDDLE = 0x04,
    MOUSE_X1 = 0x05,
    MOUSE_X2 = 0x06,

    // 系统键
    KEY_LWIN = 0x5B,
    KEY_RWIN = 0x5C,

    // 小键盘
    KEY_NUMPAD0 = 0x60,
    KEY_NUMPAD1 = 0x61,
    KEY_NUMPAD2 = 0x62,
    KEY_NUMPAD3 = 0x63,
    KEY_NUMPAD4 = 0x64,
    KEY_NUMPAD5 = 0x65,
    KEY_NUMPAD6 = 0x66,
    KEY_NUMPAD7 = 0x67,
    KEY_NUMPAD8 = 0x68,
    KEY_NUMPAD9 = 0x69,
    KEY_MULTIPLY = 0x6A,
    KEY_ADD = 0x6B,
    KEY_SUBTRACT = 0x6D,
    KEY_DECIMAL = 0x6E,
    KEY_DIVIDE = 0x6F,
}KeyCode;

typedef enum {
    BUTTON_LEFT = MOUSE_LEFT,
    BUTTON_RIGHT = MOUSE_RIGHT,
    BUTTON_MIDDLE = MOUSE_MIDDLE,
    BUTTON_X1 = MOUSE_X1,
    BUTTON_X2 = MOUSE_X2,
} MouseButton;