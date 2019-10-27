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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  SEND_00 = SAFE_RANGE,
  SEND_000
};

// keymap layer number
enum keymap_layer {
  KL_BASE,
  KL_LOWER,
  KL_RAISE,
};
#define MO_LOWER    MO(KL_LOWER)
#define MO_RAISE    MO(KL_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [KL_BASE] = LAYOUT( /* Base */
/* R1 */    KC_ESC,   KC_GRAVE, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R3 */    KC_LCTRL, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R4 */    KC_LSHIFT,KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R5 */    KC_LCTRL, KC_LGUI,  KC_LALT,  MO_LOWER, XXXXXXX,  KC_SPACE, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R2 */    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* NA */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,

/* R1 */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MINUS, XXXXXXX,  KC_BSLASH,KC_EQUAL, XXXXXXX,  XXXXXXX,
/* R2 */    KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     XXXXXXX,  KC_RBRC,  KC_LBRC,  XXXXXXX,  XXXXXXX,
/* R3 */    KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  XXXXXXX,  KC_ENT,   KC_QUOT,  XXXXXXX,  XXXXXXX,
/* NA */    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* R5 */    KC_BSPC,  XXXXXXX,  MO_RAISE, KC_RALT,  KC_LEFT,  XXXXXXX,  KC_RGHT,  KC_DOWN,  XXXXXXX,  XXXXXXX,
/* R4 */    KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  XXXXXXX,  XXXXXXX,  KC_UP,    XXXXXXX,  XXXXXXX
  ),

  [KL_LOWER] = LAYOUT(
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

  [KL_RAISE] = LAYOUT(
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
/* R5 */    KC_DEL,   XXXXXXX,  _______,  _______,  _______,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,
/* R4 */    _______,  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SEND_00:
      if (record->event.pressed) {
        // when keycode SEND_00 is pressed
        SEND_STRING("00");
      } else {
        // when keycode SEND_00 is released
      }
      break;
    case SEND_000:
      if (record->event.pressed) {
        // when keycode SEND_000 is pressed
        //SEND_STRING("000" SS_TAP(X_ENTER));
        SEND_STRING("000");
      } else {
        // when keycode SEND_000 is released
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
