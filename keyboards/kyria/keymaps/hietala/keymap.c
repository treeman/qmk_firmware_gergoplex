/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "keycodes.h"

#include "sendstring_swedish.h"

#ifdef ENCODER_ENABLE
#    include "encoder_utils.h"
#endif

#ifdef OLED_DRIVER_ENABLE
#    include "oled_utils.h"
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Modified Beakl-15
 */
    [_BASE] = LAYOUT(
      _______, MY_ESC, SE_COLN, SE_H,    SE_U,    SE_DQUO,                                     SE_X, SE_C,   SE_R,    SE_F, MY_ENT, _______,
      _______, MY_Y,   MY_I,    MY_O,    MY_A,    SE_W,                                        SE_D, MY_S,   MY_T,    MY_N, MY_B,   _______,
      _______, SE_J,   SE_DOT,  SE_COMM, SE_K,    SE_SLSH, MY_USFT, MY_RALT, MY_FUN,  KC_LGUI, SE_G, SE_M,   SE_L,    SE_P, SE_V,   _______,
                                _______, SE_PERC, MY_SPC,  MY_LSFT, KC_LEAD, KC_LEAD, MY_NUM,  MY_E, SE_EQL, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef ENCODER_ENABLE
        case ENC_MODE_L:
            if (record->event.pressed) {
                cycle_left_encoder_mode(false);
            }
            break;
        case ENC_MODE_R:
            if (record->event.pressed) {
                cycle_right_encoder_mode(false);
            }
            break;
#endif
    }
    return true;
}

/*
// FIXME this should be defined here?
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void oled_task_user(void) { render_status(); }
#endif
*/

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        update_left_encoder(clockwise);
#    ifdef OLED_DRIVER_ENABLE
        oled_on();
#    endif
    } else if (index == 1) {
        update_right_encoder(clockwise);
#    ifdef OLED_DRIVER_ENABLE
        oled_on();
#    endif
    }
}
#endif
