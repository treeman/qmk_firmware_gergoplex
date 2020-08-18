#include QMK_KEYBOARD_H

/*
 * TODO
 * 1. Dead characters don't work properly
 * 2. Modifier support on shortcut layer
 * 3. TAPPING_FORCE_HOLD per key?
 * 4. Move some altgr keys?
 * 5. Highlight altgre keys?
 *
 *
 * Another attempt:
 *
 *
 * Experiences with home row mods:
 *   https://www.reddit.com/r/ErgoMechKeyboards/comments/ibsi0k/your_experiences_with_modlayer_tap/
 */

#include <stdio.h>
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#define _______ KC_TRNS
#define xxxxx KC_NO

#define HOME_Y LGUI_T(SE_Y)
#define HOME_I LALT_T(SE_I)
#define HOME_E LSFT_T(SE_E)
#define HOME_A LCTL_T(SE_A)

// Right shift adds a return for some reason :<
#define HOME_S RCTL_T(SE_S)
#define HOME_T LSFT_T(SE_T)
#define HOME_N RALT_T(SE_N)
#define HOME_B RGUI_T(SE_B)

#define TH_SPACE KC_SPACE
#define TH_ENTER KC_ENT

enum my_keycodes {
  MOVE_ON = SAFE_RANGE,
  MOVE_OFF,
  // Avoid dead keys
  GRV,
  CIRC,
  TILD,
};

#define BASE 0 // default layer
#define SYM 1 // symbol layer
#define NUM 2 // number layer
#define FUN 3 // function layer
#define MOVE 4 // movement/mouse layer
#define SHRT 5 // shortcut layer

#include "g/keymap_combo.h"

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
    SE_Q,  SE_H,   SE_O,   SE_U,  SE_X,       SE_G, SE_C,  SE_R,  SE_F,  SE_Z,
    HOME_Y,HOME_I, HOME_E, HOME_A,SE_DOT,     SE_D, HOME_S,HOME_T,HOME_N,HOME_B,
    SE_J,  SE_COLN,SE_SLSH,SE_K,  SE_COMM,    SE_W, SE_M,  SE_L,  SE_P,  SE_V,

    OSL(SHRT), TH_SPACE,  OSL(NUM),  // Left
    OSL(SYM),  TH_ENTER,  KC_LEAD    // Right
    ),
/* Keymap 1: Symbols layer
 */
[SYM] = LAYOUT_gergoplex(
    xxxxx, SE_AT,   SE_PLUS, SE_PIPE, xxxxx,    _______,_______,_______,_______,_______,
    xxxxx, TILD,    SE_EXLM, SE_QUES, GRV,      SE_TILD,SE_GRV, SE_CIRC,SE_ACUT,SE_DIAE,
    xxxxx, SE_AMPR, CIRC,    SE_BSLS, xxxxx,    _______,_______,_______,_______,_______,

    _______, _______, _______, // Left
    _______, _______, _______  // Right
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
    _______, _______,_______,_______,_______,    xxxxx, SE_7, SE_8, SE_9, xxxxx,
    _______, _______,_______,_______,_______,    xxxxx, SE_0, SE_1, SE_2, SE_3,
    OSL(FUN),_______,_______,_______,_______,    xxxxx, SE_4, SE_5, SE_6, xxxxx,

    _______, _______,         _______, // Left
    _______, RGUI_T(KC_PENT), _______  // Right
    ),
/* Keymap 3: Function layer
 */
[FUN] = LAYOUT_gergoplex(
    _______,_______,_______,_______,_______,    KC_F12, KC_F7,  KC_F8, KC_F9, xxxxx,
    _______,_______,_______,_______,_______,    KC_F11, KC_F10, KC_F1, KC_F2, KC_F3,
    _______,_______,_______,_______,_______,    xxxxx,  KC_F4,  KC_F5, KC_F6, xxxxx,

    _______, _______, _______, // Left
    _______, _______, _______  // Right
    ),
/* Keymap 4: Movement/mouse layer
 */
[MOVE] = LAYOUT_gergoplex(
    KC_END, KC_PGDN,KC_UP,  KC_PGUP, KC_HOME,    _______,_______,_______,_______,_______,
    KC_BTN4,KC_LEFT,KC_DOWN,KC_RIGHT,KC_BTN5,    _______,_______,_______,_______,_______,
    xxxxx,  KC_BTN1,_______,KC_BTN2, xxxxx,      _______,_______,_______,_______,_______,

    OSL(SHRT), KC_SPACE, KC_ENTER, // Left
    _______,   _______,  _______   // Right
    ),
/* Keymap 5: Shortcut layer
 */
[SHRT] = LAYOUT_gergoplex(
    SE_Q,SE_W,SE_E,SE_R,SE_T,    _______,_______,_______,_______,_______,
    SE_A,SE_S,SE_D,SE_F,SE_G,    _______,_______,_______,_______,_______,
    SE_Z,SE_X,SE_C,SE_V,SE_B,    _______,_______,_______,_______,_______,

    _______, _______, _______,   // Left
    _______, _______, _______    // Right
    )
};

bool swap_caps_escape = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_ESC:
      if (swap_caps_escape) {
        if (record->event.pressed) {
            register_code(KC_CAPS);
        } else {
            unregister_code(KC_CAPS);
        }
        return false;
      }
      return true;
    case KC_CAPS:
      if (swap_caps_escape) {
        if (record->event.pressed) {
            register_code(KC_ESC);
        } else {
            unregister_code(KC_ESC);
        }
        return false;
      }
      return true;
    case MOVE_ON:
      layer_on(MOVE);
      return false;
    case MOVE_OFF:
      layer_off(MOVE);
      return false;
    case GRV:
      SEND_STRING("`");
      return false;
    case CIRC:
      SEND_STRING("^");
      return false;
    case TILD:
      SEND_STRING("~");
      return false;
    default:
      return true;
  }
}

char wpm_str[10];

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(TH_ENTER) {
      tap_code(KC_LGUI);
    }
    SEQ_TWO_KEYS(SE_C, SE_C) {
      if (swap_caps_escape) {
        tap_code(KC_ESC);
      } else {
        tap_code(KC_CAPS);
      }
    }
    SEQ_TWO_KEYS(SE_S, SE_C) {
      swap_caps_escape = !swap_caps_escape;
    }
    SEQ_TWO_KEYS(SE_P, SE_V) {
      SEND_STRING("v0.1");
    }
    SEQ_THREE_KEYS(SE_W, SE_P, SE_M) {
      sprintf(wpm_str, "WPM: %03d", get_current_wpm());
      send_string(wpm_str);
    }
  }
}

// FIXME this wasn't good enough :(
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    if (combo->keys[0] == TH_ENTER) {
        return 100;
    }

    return COMBO_TERM;
}
