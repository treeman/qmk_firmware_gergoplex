#include "oled_utils.h"

void render_keymap_version(void) {
    oled_write_P(PSTR("      "), false);
    oled_write_P(PSTR(KEYMAP_VERSION), false);
    oled_write_ln("", false);
}

void render_left_rotary_state(void) {
    //oled_write_P(PSTR("L-Enc: "), false);
    //render_encoder(encoder_left_mode);
}

void render_wpm(void) {
    //get_current_wpm(void);
}

void render_layers(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Num\n"), false);
            break;
        case _FUN:
            oled_write_P(PSTR("Fun\n"), false);
            break;
        case _MISC:
            oled_write_P(PSTR("Misc\n"), false);
            break;
        case _MOVE:
            oled_write_P(PSTR("Move\n"), false);
            break;
        default:
            oled_write_P(PSTR("???\n"), false);
    }
}

void render_mods(void) {
    uint8_t modifiers = get_mods() | get_oneshot_mods();

    oled_write_P((modifiers & MOD_MASK_SHIFT) ? PSTR("S ") : PSTR("  "), false);
    oled_write_P((modifiers & MOD_MASK_GUI) ? PSTR("G ") : PSTR("  "), false);
    oled_write_P((modifiers & MOD_MASK_CTRL) ? PSTR("C ") : PSTR("  "), false);
    oled_write_P((modifiers & MOD_MASK_ALT) ? PSTR("A ") : PSTR("  "), false);
    oled_write_ln("", false);
}

void render_caps(void) {
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    // TODO Render swapped ESC/CAPS status
    oled_write_ln("", false);
}

void render_master_status(void) {
    render_keymap_version();
    render_left_rotary_state();
    render_wpm();
}

void render_slave_status(void) {
    render_layers();
    render_mods();
    render_caps();
}
