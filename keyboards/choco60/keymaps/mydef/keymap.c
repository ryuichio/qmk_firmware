/* Copyright 2019 Naoto Takai
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

//
// make choco60:mydef:avrdude
//
#define TAPPING_TERM 180

enum layer_names {
    _BASE,
    _FN,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
};

#define KC_FN MO(_FN)

#define MAC
#ifdef MAC
#define SP_IME_ON   KC_LANG1
#define SP_IME_OFF  KC_LANG2
#define SP_CTRL     KC_LGUI
#define SP_LGUI     KC_LCTRL
#define SP_RGUI     KC_RCTRL
#else
#define SP_IME_ON   KC_HENK
#define SP_IME_OFF  KC_MHEN
#define SP_CTRL     KC_LCTRL
#define SP_LGUI     KC_LGUI
#define SP_RGUI     KC_RGUI
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    /**/ KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS,    KC_EQUAL,    KC_GRAVE,  KC_BSPC,
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    /**/ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRACKET, KC_RBRACKET, KC_BSLASH,
    SP_CTRL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    /**/ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOTE,    KC_ENTER,
    KC_LSHIFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    /**/ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSHIFT,   KC_FN,
               KC_LALT, LOWER,   KC_SPACE,                  /**/ KC_BSPC, KC_FN,   RAISE,   SP_LGUI
  ),
  [_FN] = LAYOUT(
    RESET,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   /**/ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,  KC_INSERT, KC_DEL,
    _______,   KC_PSCR, KC_SLCK, KC_PAUS, _______, _______, /**/ _______, KC_PGUP, KC_UP,   KC_PGDN, _______, _______,   _______, _______,
    _______,   _______, _______, _______, _______, _______, /**/ KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______,   KC_ENTER,
    _______,   _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______, KC_RSHIFT, KC_FN,
               _______, SP_LGUI, _______,                   /**/ KC_DEL,  _______, _______, _______
  )
};

static bool lower_pressed = false;
static bool raise_pressed = false;
static uint16_t lower_pressed_time = 0;
static uint16_t raise_pressed_time = 0;

static inline void _send_key(uint16_t keycode) {
    register_code(keycode);
    unregister_code(keycode);
}

static inline void _change_ime(bool enable) {
    if (enable) {
        _send_key(SP_IME_ON);
    } else {
        _send_key(SP_IME_OFF);
    }
}

static inline bool is_lower_pressed(uint16_t time) {
  return lower_pressed && (TIMER_DIFF_16(time, lower_pressed_time) < TAPPING_TERM);
}

static inline bool is_raise_pressed(uint16_t time) {
  return raise_pressed && (TIMER_DIFF_16(time, raise_pressed_time) < TAPPING_TERM);
}

static inline void set_lower_pressed(uint16_t time) {
  lower_pressed = true;
  raise_pressed = false;
  lower_pressed_time = time;
}

static inline void set_raise_pressed(uint16_t time) {
  raise_pressed = true;
  lower_pressed = false;
  raise_pressed_time = time;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        set_lower_pressed(record->event.time);
      } else {
        if (is_lower_pressed(record->event.time)) {
            _change_ime(false);
        }
        lower_pressed = false;
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        set_raise_pressed(record->event.time);
      } else {
        if (is_raise_pressed(record->event.time)) {
            _change_ime(true);
        }
        raise_pressed = false;
      }
      return false;
      break;
  }
  return true;
}
