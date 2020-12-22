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
#define WIN 3
#define MOVE 4
#define SHRT 5
#define GAME 6

#define ______ KC_TRNS
#define xxxxxx KC_NO

#define MY_GUI KC_SPACE
#define MY_SPACE KC_SPACE
#define MY_UP TD(T_UP)

#define MY_CTRL OSM(MOD_LCTL)
#define MY_SHIFT OSM(MOD_LSFT)
#define MY_ALT OSM(MOD_LALT)

enum {
  TO_BASE,
  // Avoid dead keys
  MY_GRV,
  MY_CIRC,
  MY_TILD,
};

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};

enum {
    T_WIN,
    T_UP,
    T_SHIFT,
    T_ALT,
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

void win_finished(qk_tap_dance_state_t *state, void *user_data);
void win_reset(qk_tap_dance_state_t *state, void *user_data);

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


/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}

// Create an instance of 'tap' for the 'win' tap dance.
static tap wintap_state = {
    .is_press_action = true,
    .state = 0
};

void win_finished(qk_tap_dance_state_t *state, void *user_data) {
    wintap_state.state = cur_dance(state);
    switch (wintap_state.state) {
        case SINGLE_TAP: set_oneshot_layer(WIN, ONESHOT_START); break;
        case SINGLE_HOLD: layer_on(WIN); break;
        /* case DOUBLE_TAP: register_code(KC_ESC); break; */
        /* case DOUBLE_HOLD: register_code(KC_LALT); break; */
        /* // Last case is for fast typing. Assuming your key is `f`: */
        /* // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`. */
        /* // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms. */
        /* case DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X); */
    }
}

void win_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (wintap_state.state) {
        case SINGLE_TAP: clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED); break;
        case SINGLE_HOLD: layer_off(WIN); break;
        /* case DOUBLE_TAP: unregister_code(KC_ESC); break; */
        /* case DOUBLE_HOLD: unregister_code(KC_LALT); */
        /* case DOUBLE_SINGLE_TAP: unregister_code(KC_X); */
    }
    wintap_state.state = 0;
}

// Create an instance of 'tap' for the 'up' tap dance.
static tap uptap_state = {
    .is_press_action = true,
    .state = 0
};

void up_finished(qk_tap_dance_state_t *state, void *user_data) {
    uptap_state.state = cur_dance(state);
    switch (uptap_state.state) {
        case SINGLE_TAP: set_oneshot_layer(UP, ONESHOT_START); break;
        case SINGLE_HOLD: layer_on(UP); break;
        case DOUBLE_TAP: set_oneshot_layer(FUN, ONESHOT_START); break;
        case DOUBLE_HOLD: layer_on(FUN); break;
    }
}

void up_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (uptap_state.state) {
        case SINGLE_TAP: clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED); break;
        case SINGLE_HOLD: layer_off(UP); break;
        case DOUBLE_TAP: clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED); break;
        case DOUBLE_HOLD: layer_off(FUN); break;
    }
    uptap_state.state = 0;
}

// Create an instance of 'tap' for the 'shift' tap dance.
static tap shifttap_state = {
    .is_press_action = true,
    .state = 0
};

// FIXME how to combine oneshot mods?
void up_finished(qk_tap_dance_state_t *state, void *user_data) {
    shifttap_state.state = cur_dance(state);
    switch (shifttap_state.state) {
        case SINGLE_TAP: set_oneshot_mods(MOD_LSFT); break;
        case SINGLE_HOLD: register_mods(MOD_BIT(KC_LSFT)); break;
        case DOUBLE_TAP: set_oneshot_layer(FUN, ONESHOT_START); break;
        case DOUBLE_HOLD: layer_on(FUN); break;
    }
}

void up_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (shifttap_state.state) {
        case SINGLE_TAP: clear_oneshot_mods(); break;
        case SINGLE_HOLD: unregister_mods(MOD_BIT(KC_LSFT)); break;
        case DOUBLE_TAP: clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED); break;
        case DOUBLE_HOLD: layer_off(FUN); break;
    }
    shifttap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [T_WIN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, win_finished, win_reset)
    [T_UP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, up_finished, up_reset)
    [T_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_finished, shift_reset)
};

/* register_mods(MOD_BIT(KC_LALT)); */
/* unregister_mods(MOD_BIT(KC_LALT)); */

