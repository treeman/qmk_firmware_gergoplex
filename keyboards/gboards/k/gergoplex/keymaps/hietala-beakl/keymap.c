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

#define TH_GUI KC_SPACE
#define TH_SPACE KC_SPACE
#define TH_UP OSL(UP)

#define TH_CTRL OSM(MOD_LCTL)
#define TH_SHIFT OSM(MOD_LSFT)
#define TH_ALT OSM(MOD_LALT)

enum my_keycodes {
  TO_BASE,
  // Avoid dead keys
  GRV,
  CIRC,
  TILD,
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
    KC_LEAD, SE_H,   SE_O,    SE_U, SE_Q,     SE_W, SE_C, SE_R, SE_F, SE_Z,
    SE_Y,    SE_I,   SE_E,    SE_A, SE_COLN,  SE_D, SE_S, SE_T, SE_N, SE_B,
    KC_J,    SE_DOT, SE_COMM, SE_K, SE_X,     SE_G, SE_M, SE_L, SE_P, SE_V,

    TH_GUI,  TH_SPACE, TH_UP,
    TH_CTRL, TH_SHIFT, TH_ALT
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
bool remapping_shift = false;

bool mod_down(uint16_t mod) {
    return keyboard_report->mods & MOD_BIT(mod);
}

bool remap_shift(keyrecord_t *record, uint16_t keycode) {
    if (record->event.pressed) {
        bool shift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        bool one_shot_shift = (get_oneshot_mods() & MOD_BIT(KC_LSFT)) &&
            !has_oneshot_mods_timed_out() && false;

        if (!shift && !one_shot_shift) return false;

        if (shift) {
            unregister_mods(MOD_BIT(KC_LSFT));
            tap_code16(keycode);
            register_mods(MOD_BIT(KC_LSFT));
        } else {
            clear_oneshot_mods();
            tap_code16(keycode);
        }
        remapping_shift = true;
    } else {
        if (!remapping_shift) return false;
        // If we move unregister_code and register shift here,
        // and if we do
        //
        //  shift down
        //  keycode down
        //  shift up
        //  keycode up
        //
        // we'll get stuck with shift.
        //
        // If we instead tap on pressed auto repeat breaks, but
        // we'll never find ourselves in a bad position.
        remapping_shift = false;
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
    case GRV:
      SEND_STRING("`");
      return false;
    case CIRC:
      SEND_STRING("^");
      return false;
    case TILD:
      SEND_STRING("~");
      return false;
    case SE_DOT:
      // . -> !
      if (remap_shift(record, SE_EXLM)) return false;
      return true;
    case SE_COMM:
      // , -> ?
      if (remap_shift(record, SE_QUES)) return false;
      return true;
    case SE_SLSH:
      // / -> \ (unshift + altgr)
      if (remap_shift(record, SE_BSLS)) return false;
      return true;
    case SE_COLN:
      // : -> @ (unshift + altgr)
      if (remap_shift(record, SE_AT)) return false;
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
