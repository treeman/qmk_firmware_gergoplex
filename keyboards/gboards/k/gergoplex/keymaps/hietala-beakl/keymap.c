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
#define MOV 4 // movement/mouse layer
#define QWERTY 5 // qwerty layer

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

#define I_MOD LCTL_T(KC_I)
#define E_MOD LALT_T(KC_E)
#define A_MOD LSFT_T(KC_A)

#define S_MOD RSFT_T(KC_S)
#define T_MOD RALT_T(KC_T)
#define N_MOD RCTL_T(KC_N)

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
    KC_Y,  I_MOD,  E_MOD,  A_MOD, KC_DOT,     KC_D, S_MOD, T_MOD, N_MOD, KC_B,
    KC_J,  KC_COLN,KC_SLSH,KC_K,  KC_COMM,    KC_W, KC_M,  KC_L,  KC_P,  KC_V,

    TT(MOV),  LGUI_T(KC_SPACE),  OSL(NUM),  // Left
    OSL(SYM), KC_ENT,            KC_LEAD    // Right
    ),
/* Keymap 1: Symbols layer
 */
[SYM] = LAYOUT_gergoplex(
    KC_NO, KC_AT,   KC_PLUS, KC_PIPE, KC_NO,    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
    KC_NO, KC_TILD, KC_EXLM, KC_QUES, KC_GRV,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
    KC_NO, KC_AMPR, KC_CIRC, KC_BSLS, KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

    KC_TRNS, KC_TRNS, KC_TRNS, // Left
    KC_TRNS, KC_TRNS, KC_TRNS  // Right
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
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,    KC_NO, KC_7, KC_8, KC_9, KC_NO,
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,    KC_NO, KC_0, KC_1, KC_2, KC_3,
    OSL(FUN),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,    KC_NO, KC_4, KC_5, KC_6, KC_NO,

    KC_TRNS, KC_TRNS,         KC_TRNS, // Left
    KC_TRNS, RGUI_T(KC_PENT), KC_TRNS  // Right
    ),
/* Keymap 3: Function layer
 */
[FUN] = LAYOUT_gergoplex(
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,    KC_F12, KC_F7,  KC_F8, KC_F9, KC_NO,
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,    KC_F11, KC_F10, KC_F1, KC_F2, KC_F3,
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,    KC_NO,  KC_F4,  KC_F5, KC_F6, KC_NO,

    KC_TRNS, KC_TRNS, KC_TRNS, // Left
    KC_TRNS, KC_TRNS, KC_TRNS  // Right
    ),
/* Keymap 4: Movement/mouse layer
 */
[FUN] = LAYOUT_gergoplex(
    KC_END, KC_PGDN,KC_UP,  KC_PGUP, KC_HOME,    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
    KC_WBAK,KC_LEFT,KC_DOWN,KC_RIGHT,KC_WFWD,    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
    KC_TRNS,KC_BTN1,KC_TRNS,KC_BTN2, KC_TRNS,    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

    TG(MOV), KC_SPACE, KC_ENTER, // Left
    KC_TRNS, KC_TRNS,  KC_TRNS   // Right
    ),
/* Keymap 5: qwerty layer
 */
[QWERTY] = LAYOUT_gergoplex(
    KC_Q,KC_W,KC_E,KC_R,KC_T,    KC_Y,KC_U,KC_I,   KC_O,  KC_P,
    KC_A,KC_S,KC_D,KC_F,KC_G,    KC_H,KC_J,KC_K,   KC_L,  KC_M,
    KC_Z,KC_X,KC_C,KC_V,KC_B,    KC_N,KC_M,KC_COMM,KC_DOT,KC_MINUS,

    KC_TRNS, KC_TRNS, KC_TRNS,   // Left
    KC_TRNS, KC_TRNS, KC_TRNS    // Right
    )
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    /*
    SEQ_ONE_KEY(KC_F) {
      // Anything you can do in a macro.
      SEND_STRING("QMK is awesome.");
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com\n");
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
    */
    SEQ_ONE_KEY(KC_ENTER) {
      register_code(KC_LGUI);
      unregister_code(KC_LGUI);
    }
    SEQ_ONE_KEY(KC_A) {
      SEND_STRING("å");
    }
    SEQ_ONE_KEY(KC_E) {
      SEND_STRING("ä");
    }
    SEQ_ONE_KEY(KC_I) {
      SEND_STRING("ö");
    }
    /*
    SEQ_TWO_KEYS(KC_DOT, KC_E) {
  //    SEND_STRING("é");
      send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
    }
    SEQ_TWO_KEYS(KC_COMM, KC_E) {
      SEND_STRING("è");
    }
    SEQ_TWO_KEYS(KC_DOT, KC_A) {
      SEND_STRING("á");
    }
    SEQ_TWO_KEYS(KC_COMM, KC_A) {
      SEND_STRING("à");
    }
    */
    /*
    SEQ_TWO_KEYS(KC_S, KC_U) {
     // toggle unicode support
     // is this even possible...?
    }
    */
    /*
    SEQ_TWO_KEYS(KC_S, KC_L) {
     // toggle unicode support
     // is this even possible...?
    }
    */
    SEQ_TWO_KEYS(KC_P, KC_V) {
      SEND_STRING("BEAKL-HIETALA 0.1");
    }
  }
}

