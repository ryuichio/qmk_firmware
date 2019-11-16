/* Copyright 2019 e3w2q
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
// make handwired/su120/rev1:split54:avrdude
//

//#define MAC
#ifdef MAC
#define SP_IS_MAC   true
#define SP_IME_ON   KC_LANG1
#define SP_IME_OFF  KC_LANG2
#define SP_CMD      KC_LGUI
#define SP_CTRL     KC_LCTL
#else
#define SP_IS_MAC   false
#define SP_IME_ON   KC_HENK
#define SP_IME_OFF  KC_MHEN
#define SP_CMD      KC_LCTL
#define SP_CTRL     KC_LGUI
#endif

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
};

// keymap layer number
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( /* Base */
/* R1 */    KC_ESC,   KC_GRAVE, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R3 */    KC_LCTRL, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R4 */    KC_LSHIFT,KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R5 */    KC_LCTRL, KC_LGUI,  KC_LALT,  LOWER,    XXXXXXX,  KC_SPACE, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R2 */    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* NA */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,

/* R1 */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MINUS, XXXXXXX,  KC_BSLASH,KC_EQUAL, XXXXXXX,  XXXXXXX,
/* R2 */    KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     XXXXXXX,  KC_RBRC,  KC_LBRC,  XXXXXXX,  XXXXXXX,
/* R3 */    KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  XXXXXXX,  KC_ENT,   KC_QUOT,  XXXXXXX,  XXXXXXX,
/* NA */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R5 */    KC_BSPC,  XXXXXXX,  RAISE,    KC_RALT,  KC_LEFT,  XXXXXXX,  KC_RGHT,  KC_DOWN,  XXXXXXX,  XXXXXXX,
/* R4 */    KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  XXXXXXX,  XXXXXXX,  KC_UP,    XXXXXXX,  XXXXXXX
  ),

  [_LOWER] = LAYOUT(
/* R1 */    _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R3 */    _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R4 */    _______,  _______,  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R5 */    _______,  _______,  _______,  _______,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R2 */    _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* NA */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,

/* R1 */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,
/* R2 */    KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,
/* R3 */    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,
/* NA */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R5 */    _______,  XXXXXXX,  _______,  _______,  KC_HOME,  XXXXXXX,  KC_END,   KC_PGDN,  XXXXXXX,  XXXXXXX,
/* R4 */    _______,  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  KC_PGUP,  XXXXXXX,  XXXXXXX
  ),

  [_RAISE] = LAYOUT(
/* R1 */    _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R3 */    _______,  _______,  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R4 */    _______,  _______,  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R5 */    _______,  _______,  _______,  _______,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R2 */    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* NA */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,

/* R1 */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,
/* R2 */    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   XXXXXXX,  KC_F12,   KC_F11,   XXXXXXX,  XXXXXXX,
/* R3 */    _______,  _______,  _______,  _______,  _______,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,
/* NA */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R5 */    KC_DEL,   XXXXXXX,  _______,  _______,  KC_HOME,  XXXXXXX,  KC_END,   KC_PGDN,  XXXXXXX,  XXXXXXX,
/* R4 */    _______,  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  KC_PGUP,  XXXXXXX,  XXXXXXX
  ),

  [_ADJUST] = LAYOUT(
/* R1 */    _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R3 */    _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R4 */    _______,  _______,  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R5 */    _______,  _______,  _______,  _______,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R2 */    _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* NA */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,

/* R1 */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,
/* R2 */    KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,
/* R3 */    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,
/* NA */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R5 */    _______,  XXXXXXX,  _______,  _______,  KC_HOME,  XXXXXXX,  KC_END,   KC_PGDN,  XXXXXXX,  XXXXXXX,
/* R4 */    _______,  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  KC_PGUP,  XXXXXXX,  XXXXXXX
  )
};

static bool lower_pressed = false;
static bool raise_pressed = false;
static uint16_t lower_pressed_time = 0;
static uint16_t raise_pressed_time = 0;

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

static inline void reset_layer_pressed(void) {
  lower_pressed = false;
  raise_pressed = false;
  lower_pressed_time = 0;
  raise_pressed_time = 0;
}

static inline bool is_lower_pressed(uint16_t time) {
  return lower_pressed && (TIMER_DIFF_16(time, lower_pressed_time) < TAPPING_TERM);
}

static inline bool is_raise_pressed(uint16_t time) {
  return raise_pressed && (TIMER_DIFF_16(time, raise_pressed_time) < TAPPING_TERM);
}

static inline void update_change_layer(bool pressed, uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  pressed ? layer_on(layer1) : layer_off(layer1);
  IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2) ? layer_on(layer3) : layer_off(layer3);
}

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
      update_change_layer(record->event.pressed, _LOWER, _RAISE, _ADJUST);
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
      update_change_layer(record->event.pressed, _RAISE, _LOWER, _ADJUST);
      return false;
      break;
    default:
      if (record->event.pressed) {
        reset_layer_pressed();
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
