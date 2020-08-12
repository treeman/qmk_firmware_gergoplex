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

#define Y_MOD MT(MOD_LGUI, KC_Y)
#define I_MOD MT(MOD_LCTL, KC_I)
#define E_MOD MT(MOD_LALT, KC_E)
#define A_MOD MT(MOD_LSFT, KC_A)

#define S_MOD MT(MOD_RSFT, KC_S)
#define T_MOD MT(MOD_RALT, KC_T)
#define N_MOD MT(MOD_RCTL, KC_N)
#define B_MOD MT(MOD_RGUI, KC_B)

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

    KC_PERC, KC_SPC,    KC_NO,  // Left
    KC_NO,   KC_RETURN, KC_EQL  // Right
    )
};
