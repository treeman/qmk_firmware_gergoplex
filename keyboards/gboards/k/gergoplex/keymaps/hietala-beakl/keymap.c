#include QMK_KEYBOARD_H

/*
 * TODO
 * 1. Shortcut layer mod taps
 * 2. Overlayed mod one-shots
 * 3. Sometimes pressing / and : in rapid succession makes shift/altgr to get stuck
 *    (possibly other SE symbols too).
 *
 * Experiences with home row mods:
 *   https://www.reddit.com/r/ErgoMechKeyboards/comments/ibsi0k/your_experiences_with_modlayer_tap/
 */

#include <stdio.h>
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#define BASE 0
#undef UP
#define UP 1
#define FUN 2
#define MOVE 3
#define SHRT 4
#define GAME 5

#define ______ KC_TRNS
#define xxxxxx KC_NO

#define MY_GUI KC_SPACE
#define MY_SPACE KC_SPACE
#define MY_UP OSL(UP)

#define MY_CTRL OSM(MOD_LCTL)
#define MY_SHIFT OSM(MOD_LSFT)
#define MY_ALT OSM(MOD_LALT)

enum my_keycodes {
  TO_BASE,
  // Avoid dead keys
  MY_GRV,
  MY_CIRC,
  MY_TILD,
};

#include "g/keymap_combo.h"

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
    KC_LEAD, SE_H,   SE_O,    SE_U, SE_X,     SE_Q, SE_C, SE_R, SE_F, SE_Z,
    SE_Y,    SE_I,   SE_E,    SE_A, SE_COLN,  SE_D, SE_S, SE_T, SE_N, SE_B,
    KC_J,    SE_DOT, SE_COMM, SE_K, SE_W,     SE_G, SE_M, SE_L, SE_P, SE_V,

    MY_GUI,  MY_SPACE, MY_UP,
    MY_CTRL, MY_SHIFT, MY_ALT
    ),
/* Keymap 1: Up layer
 */
[UP] = LAYOUT_gergoplex(
    ______, ______, ______, _______,______,    xxxxxx, SE_7, SE_8, SE_9, TO_BASE,
    ______, SE_ODIA,SE_ADIA,SE_ARNG,______,    xxxxxx, SE_1, SE_2, SE_3, xxxxxx,
    SE_TILD,SE_GRV, SE_CIRC,SE_ACUT,SE_DIAE,   xxxxxx, SE_4, SE_5, SE_6, xxxxxx,

    KC_LGUI, KC_LSFT,    ______,
    ______,  LSFT(SE_0), ______
    ),
/* Keymap 2: Function layer
 */
[FUN] = LAYOUT_gergoplex(
    ______,______,______,______,______,    KC_F12, KC_F7, KC_F8, KC_F9, TO_BASE,
    ______,______,______,______,______,    KC_F11, KC_F1, KC_F2, KC_F3, xxxxxx,
    ______,______,______,______,______,    KC_F10, KC_F4, KC_F5, KC_F6, xxxxxx,

    ______, ______, ______, // Left
    ______, ______, ______  // Right
    ),
/* Keymap 3: Movement/mouse layer
 */
[MOVE] = LAYOUT_gergoplex(
    KC_LEAD,KC_PGDN,KC_UP,  KC_PGUP, KC_HOME,   ______,______,______,______,TO_BASE,
    KC_ESC, KC_LEFT,KC_DOWN,KC_RIGHT,KC_END,    ______,______,______,______,______,
    KC_BTN4,KC_BTN1,xxxxxx, KC_BTN5, xxxxxx,    ______,______,______,______,______,

    ______, ______, OSL(SHRT), // Left
    ______, ______, ______     // Right
    ),
/* Keymap 4: Shortcut layer
 */
[SHRT] = LAYOUT_gergoplex(
    KC_LEAD,SE_Q,SE_W,SE_E,SE_R,    ______,______,______,______,TO_BASE,
    xxxxxx ,SE_A,SE_S,SE_D,SE_F,    ______,______,______,______,______,
    xxxxxx ,SE_Z,SE_X,SE_C,SE_V,    ______,______,______,______,______,

    ______, ______, ______,   // Left
    ______, ______, ______    // Right
    )
};

bool swap_caps_escape = false;
bool remapping_shift[4];

bool mod_down(uint16_t mod) {
    return keyboard_report->mods & MOD_BIT(mod);
}

bool mod_one_shot(uint16_t mod) {
    return (get_oneshot_mods() & MOD_BIT(mod)) && !has_oneshot_mods_timed_out();
}

bool remap_shift(keyrecord_t *record, uint16_t keycode, uint16_t i) {
    if (record->event.pressed) {
        bool shift = mod_down(KC_LSFT);
        bool one_shot_shift = mod_one_shot(KC_LSFT);

        if (!shift && !one_shot_shift) return false;

        register_code(keycode);

        remapping_shift[i] = true;
    } else {
        if (!remapping_shift[i]) return false;

        unregister_code(keycode);

        remapping_shift[i] = false;
    }
    return true;
}

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
    case TO_BASE:
      layer_clear();
      clear_oneshot_mods();
      return false;
    case MY_GRV:
      SEND_STRING("`");
      return false;
    case MY_CIRC:
      SEND_STRING("^");
      return false;
    case MY_TILD:
      SEND_STRING("~");
      return false;
    case SE_DOT:
      // . -> !
      if (remap_shift(record, SE_1, 0)) return false;
      return true;
    case SE_COMM:
      // , -> ?
      if (remap_shift(record, SE_PLUS, 1)) return false;
      return true;
    case MY_SPACE:
      // space -> /
      if (remap_shift(record, SE_7, 2)) return false;
      return true;
    case SE_COLN:
      // : -> %
      if (remap_shift(record, SE_5, 3)) return false;
      return true;
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

    SEQ_TWO_KEYS(SE_C, SE_C) {
      if (swap_caps_escape) {
        tap_code(KC_ESC);
      } else {
        tap_code(KC_CAPS);
      }
    }

    SEQ_ONE_KEY(KC_ESC) {
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
