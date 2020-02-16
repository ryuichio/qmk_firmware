/* Copyright 2019 Franklin Harding
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
// make slamd:default:avrdude
//

// Defines the keycodes used by our macros in process_record_user
enum slamd_layouts {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
};

enum tapdances{
  TD_SCCL = 0,
  TD_SLBS,
  TD_MIEQ,
};

#define KC_SCCL  TD(TD_SCCL)
#define KC_SLBS  TD(TD_SLBS)
#define KC_MIEQ  TD(TD_MIEQ)

//#define _MAC
#ifdef _MAC
#define SP_CTRL  KC_LGUI
#define SP_WIN   KC_LCTL
#else
#define SP_CTRL  KC_LCTL
#define SP_WIN   KC_LGUI
#endif

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SCCL] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
  [TD_SLBS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
  [TD_MIEQ] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | No   | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MIEQ,
    SP_CTRL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCCL, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
    KC_TAB,  KC_LCTL, KC_LALT, SP_WIN,  LOWER,   KC_SPC,  KC_BSPC, RAISE,   KC_RALT, KC_LBRC, KC_RBRC, KC_NO
),
  /* Lower */
[_LOWER] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_ENT,
    _______, _______, _______, _______, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______
),
/* Raise */
[_RAISE] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_PGUP, KC_UP,   KC_PGDN, _______, _______,
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,  _______,
    _______, KC_F11,  KC_F12,  _______, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______
),
/* Adjust */
[_ADJUST] = LAYOUT(
    RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

static inline void _send_key(uint16_t keycode) {
    register_code(keycode);
    unregister_code(keycode);
}

static inline void _change_ime(bool enable) {
    if (enable) {
#ifdef _MAC
        _send_key(KC_LANG1);
#else
        _send_key(KC_HENK);
#endif
    } else {
#ifdef _MAC
        _send_key(KC_LANG2);
#else
        _send_key(KC_MHEN);
#endif
    }
}

static bool lower_pressed = false;
static bool raise_pressed = false;
static uint16_t lower_pressed_time = 0;
static uint16_t raise_pressed_time = 0;

static inline void update_change_layer(bool pressed, uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  pressed ? layer_on(layer1) : layer_off(layer1);
  IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2) ? layer_on(layer3) : layer_off(layer3);
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

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {
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
