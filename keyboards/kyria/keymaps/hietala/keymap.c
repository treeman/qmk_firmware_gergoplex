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
      xxxxxxx, MY_ESC,  SE_COLN, SE_O,    SE_U,    SE_DQUO,                                     SE_X,    SE_C,    SE_R,    SE_F,    MY_ENT,  xxxxxxx,
      xxxxxxx, SE_Y,    MY_H,    MY_E,    MY_A,    SE_W,                                        SE_D,    MY_S,    MY_T,    MY_N,    SE_V,    xxxxxxx,
      xxxxxxx, SE_J,    MY_DOT,  SE_COMM, MY_K,    SE_SLSH, MY_LCTL, xxxxxxx, MY_FUN,  MY_RCTL, SE_G,    MY_M,    SE_L,    MY_P,    SE_B,    xxxxxxx,
                                 L_ENCM,  SE_PERC, MY_SPC,  MY_LSFT, KC_LEAD, KC_LEAD, MY_RSFT, MY_I,    MY_NUM,  R_ENCM
    ),
    [_NUM] = LAYOUT(
      xxxxxxx, _______, SE_6,    SE_5,    SE_4,    xxxxxxx,                                     _______, _______, _______, _______, KC_PENT, xxxxxxx,
      xxxxxxx, SE_3,    SE_2,    SE_1,    SE_0,    xxxxxxx,                                     _______, _______, _______, _______, _______, xxxxxxx,
      xxxxxxx, xxxxxxx, SE_9,    SE_8,    SE_7,    xxxxxxx, _______, _______, _______, _______, _______, _______, _______, _______, _______, xxxxxxx,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_FUN] = LAYOUT(
      xxxxxxx, _______, KC_F6,   KC_F5,   KC_F4,   KC_F12,                                      _______, _______, _______, _______, _______, xxxxxxx,
      xxxxxxx, KC_F3,   KC_F2,   KC_F1,   xxxxxxx, KC_F11,                                      _______, _______, _______, _______, _______, xxxxxxx,
      xxxxxxx, xxxxxxx, KC_F9,   KC_F8,   KC_F7,   KC_F10,  _______, _______, _______, _______, _______, _______, _______, _______, _______, xxxxxxx,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef ENCODER_ENABLE
        case L_ENCM:
            if (record->event.pressed) {
                cycle_left_encoder_mode(false);
            }
            break;
        case R_ENCM:
            if (record->event.pressed) {
                cycle_right_encoder_mode(false);
            }
            break;
#endif
    }
    return true;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_master_status();
    } else {
        render_slave_status();
    }
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        action_left_encoder(clockwise);
#    ifdef OLED_DRIVER_ENABLE
        oled_on();
#    endif
    } else if (index == 1) {
        action_right_encoder(clockwise);
#    ifdef OLED_DRIVER_ENABLE
        oled_on();
#    endif
    }
}
#endif
