/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

#define BASE 0 // default layer
#define SYM 1 // symbol layer
#define NUM 2 // number layer
#define FUN 3 // function layer

/* Combomap
 *
 * ,-----------------------------.       ,--------------------------------.
 * |      |    ESC    |     |     |      |     |    ESC    |    BSLH      |
 * |-----+-----+-----+-----+------|      |--------------------------------|
 * |      |   BSPC   ENT    |     |      |    LES   COLN  GRT    |        |
 * |-----+-----+-----+--RMB+-LMB--+      |--------------------------------|
 * |      |   MINS    |     |     |      |    QUO   UNDR   |     |        |
 * `------+-----+-----+------+----'      `--------------------------------'
 *  .-------------------------.           .-----------------.
 *  |        |       |        |           |        |    |   |
 *  '-------------------------'           '-----------------'
 */

#define Y_MOD LGUI_T(KC_Y)
#define I_MOD LCTL_T(KC_I)
#define E_MOD LALT_T(KC_E)
#define A_MOD LSFT_T(KC_A)

#define S_MOD RSFT_T(KC_S)
#define T_MOD RALT_T(KC_T)
#define N_MOD RCTL_T(KC_N)
#define B_MOD RGUI_T(KC_B)

// Blank template at the bottom
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-----------------------------.       ,--------------------------------.
 * |      |     |     |     |     |      |     |     |     |     |        |
 * |-----+-----+-----+-----+------|      |--------------------------------|
 * |      |     |     |     |     |      |     |     |     |     |        |
 * |-----+-----+-----+-----+------+      |--------------------------------|
 * |      |     |     |     |     |      |     |     |     |     |        |
 * `------+-----+-----+------+----'        `--------------------------------'
 *  .-------------------------.           .-----------------.
 *  |        |       |        |           |        |    |   |
 *  '-------------------------'           '-----------------'
 */
[BASE] = LAYOUT_gergoplex(
    KC_Q,  KC_H,   KC_O,   KC_U,  KC_X,       KC_G, KC_C,  KC_R,  KC_F,  KC_Z,
    Y_MOD, I_MOD,  E_MOD,  A_MOD, KC_DOT,     KC_D, S_MOD, T_MOD, N_MOD, B_MOD,
    KC_J,  KC_COLN,KC_SLSH,KC_K,  KC_COMM,    KC_W, KC_M,  KC_L,  KC_P,  KC_V,

    KC_PERC,  KC_SPC,    OSL(NUM),  // Left
    OSL(SYM), KC_RETURN, KC_EQL     // Right
    ),
/* Keymap 2: Number layer
 *
 * ,-----------------------------.       ,--------------------------------.
 * |      |     |     |     |     |      |     |     |     |     |        |
 * |-----+-----+-----+-----+------|      |--------------------------------|
 * |      |     |     |     |     |      |     |     |     |     |        |
 * |-----+-----+-----+-----+------+      |--------------------------------|
 * |      |     |     |     |     |      |     |     |     |     |        |
 * `------+-----+-----+------+----'        `--------------------------------'
 *  .-------------------------.           .-----------------.
 *  |        |       |        |           |        |    |   |
 *  '-------------------------'           '-----------------'
 */
[NUM] = LAYOUT_gergoplex(
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,    KC_NO, KC_7, KC_8, KC_9, KC_NO,
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,    KC_NO, KC_0, KC_1, KC_2, KC_3,
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,    KC_NO, KC_4, KC_5, KC_6, KC_NO,

    KC_TRNS, KC_TRNS, KC_TRNS, // Left
    KC_TRNS, KC_PENT, KC_TRNS  // Right
    )
};
