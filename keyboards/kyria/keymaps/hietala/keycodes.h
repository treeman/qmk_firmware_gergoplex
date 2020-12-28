#pragma once

#include "keymap_swedish.h"
#include "quantum.h"

enum layers {
    _BASE = 0,
    _NUM,
    _FUN,
    _MISC,
    _MOVE
};

enum custom_keycodes {
    L_ENCM = SAFE_RANGE,
    R_ENCM
};

#define xxxxxxx KC_NO

#define MY_Y SE_Y
#define MY_I LALT_T(SE_I)
#define MY_O LSFT_T(SE_O)
#define MY_A LCTL_T(SE_A)
#define MY_DOT RALT_T(SE_DOT)
#define MY_K LGUI_T(SE_K)

#define MY_S RCTL_T(SE_S)
#define MY_T RSFT_T(SE_T)
#define MY_N LALT_T(SE_N)
#define MY_B SE_B
#define MY_M RGUI_T(SE_M)
#define MY_P RALT_T(SE_P)

#define MY_ESC KC_ESC
#define MY_ENT KC_ENTER

#define MY_LSFT OSM(MOD_LSFT)
#define MY_RSFT OSM(MOD_RSFT)
#define MY_LCTL OSM(MOD_LCTL)
#define MY_RCTL OSM(MOD_RCTL)

#define MY_NUM OSL(_NUM)
#define MY_FUN OSL(_FUN)

#define MY_SPC KC_SPACE
#define MY_E SE_E

