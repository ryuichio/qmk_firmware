/* Copyright 2020 yushakobo
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

// make yushakobo/quick7:mydef:avrdude

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FUNC1
};

#define XXXXXXX  KC_NO

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    YUSHAURL = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        XXXXXXX,   XXXXXXX,   RGB_MOD,
        MO(_FUNC1),KC_UP,     KC_TAB,
        KC_LEFT,   KC_DOWN,   KC_RGHT
    ),
    [_FUNC1] = LAYOUT(
        XXXXXXX,   XXXXXXX,   RGB_TOG,
        _______,   KC_VOLU,   KC_END,
        KC_MPRV,   KC_VOLD,   KC_MNXT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case YUSHAURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://yushakobo.jp/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    // if (clockwise) {
    //     tap_code(KC_VOLU);
    // } else {
    //     tap_code(KC_VOLD);
    // }
    if (clockwise) {
        rgblight_decrease_hue_noeeprom();
    } else {
        rgblight_increase_hue_noeeprom();
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case _FUNC1:
            oled_write_ln_P(PSTR("Func1"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}
