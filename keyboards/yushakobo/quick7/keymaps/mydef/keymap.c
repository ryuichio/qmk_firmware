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
    _Arrow,  // arrows
    _Audio,  // audio
    _Led,    // leds
    _System, // system
};

#define XXXXXXX  KC_NO

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    YUSHAURL = SAFE_RANGE,
    KC_MCMUTE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_Arrow] = LAYOUT(
        XXXXXXX,   XXXXXXX,   TO(_Audio),
        KC_PGUP,   KC_UP,     KC_PGDN,
        KC_LEFT,   KC_DOWN,   KC_RGHT
    ),
    [_Audio] = LAYOUT(
        XXXXXXX,   XXXXXXX,   TO(_Led),
        KC_MUTE,   KC_VOLU,   KC_MPRV,
        KC_MCMUTE, KC_VOLD,   KC_MNXT
    ),
    [_Led] = LAYOUT(
        XXXXXXX,   XXXXXXX,   TO(_System),
        RGB_TOG,   RGB_SAI,   RGB_VAI,
        RGB_MOD,   RGB_SAD,   RGB_VAD
    ),
    [_System] = LAYOUT(
        XXXXXXX,   XXXXXXX,   TO(_Arrow),
        RESET,     XXXXXXX,   XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX
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
        case KC_MCMUTE:
            if (record->event.pressed) {
                register_code(KC_LSHIFT);
                register_code(KC_LGUI);
                register_code(KC_0);
                unregister_code(KC_0);
                unregister_code(KC_LGUI);
                unregister_code(KC_LSHIFT);
            }
            return false;
            break;
    }
    return true;
}

static inline void _send_key(uint16_t keycode) {
    register_code(keycode);
    unregister_code(keycode);
}

void _enc_tap(bool iscw, uint16_t oncw, uint16_t onucw) {
    if (iscw) {
        tap_code(oncw);
    } else {
        tap_code(onucw);
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _Arrow:
            break;
        case _Audio:
            _enc_tap(clockwise, KC_VOLU, KC_VOLD);
            break;
        case _Led:
            if (clockwise) {
                rgblight_decrease_hue_noeeprom();
            } else {
                rgblight_increase_hue_noeeprom();
            }
            break;
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Mode: "), false);

    switch (get_highest_layer(layer_state)) {
        case _Arrow:
            oled_write_ln_P(PSTR("Arrow keys"), false);
            oled_write_ln_P(PSTR("          ----/----"), false);
            oled_write_ln_P(PSTR("PGUP  UP  PGDN"), false);
            oled_write_ln_P(PSTR("LEFT DOWN RIGT"), false);
            break;
        case _Audio:
            oled_write_ln_P(PSTR("Audio"), false);
            oled_write_ln_P(PSTR("          VOL+/VOL-"), false);
            oled_write_ln_P(PSTR("MUTE VOL+ NEXT"), false);
            oled_write_ln_P(PSTR("MIC  VOL- PREV"), false);
            break;
        case _Led:
            oled_write_ln_P(PSTR("LED Control"), false);
            oled_write_ln_P(PSTR("          HUE+/HUE-"), false);
            oled_write_ln_P(PSTR("TOGL SAT+ BRI+"), false);
            oled_write_ln_P(PSTR("MODE SAT- BRI-"), false);
            break;
        case _System:
            oled_write_ln_P(PSTR("System"), false);
            oled_write_ln_P(PSTR("          ----/----"), false);
            oled_write_ln_P(PSTR("RST  ---- ----"), false);
            oled_write_ln_P(PSTR("---- ---- ----"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
            oled_write_ln_P(PSTR("          ----/----"), false);
            oled_write_ln_P(PSTR("---- ---- ----"), false);
            oled_write_ln_P(PSTR("---- ---- ----"), false);
    }
}
