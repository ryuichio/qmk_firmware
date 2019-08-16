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

enum layer_names {
    _BASE,
    _FN,
};

#define KC_FN MO(_FN)

//#define MAC
#ifdef MAC
#define SP_IME_ON   KC_LANG1
#define SP_IME_OFF  KC_LANG2
#define SP_CTRL     KC_LGUI
#define SP_GUI      KC_LCTRL
#else
#define SP_IME_ON   KC_HENK
#define SP_IME_OFF  KC_MHEN
#define SP_CTRL     KC_LCTRL
#define SP_GUI      KC_LGUI
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    /**/ KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS,    KC_EQUAL,    KC_GRAVE,  KC_BSPC,
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    /**/ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRACKET, KC_RBRACKET, KC_BSLASH,
    KC_LCTRL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    /**/ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOTE,    KC_ENTER,
    KC_LSHIFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    /**/ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSHIFT,   KC_FN,
               KC_LGUI, KC_LALT, KC_SPACE,                  /**/ KC_FN,   KC_BSPC, SP_IME_OFF, SP_IME_ON
  ),
  [_FN] = LAYOUT(
    RESET,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   /**/ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,  KC_INSERT, KC_DEL,
    _______,   KC_PSCR, KC_SLCK, KC_PAUS, _______, _______, /**/ _______, KC_PGUP, KC_UP,   KC_PGDN, _______, _______,   _______, _______,
    _______,   _______, _______, _______, _______, _______, /**/ KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______,   KC_ENTER,
    _______,   _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______, KC_RSHIFT, KC_FN,
               _______, _______, _______,                   /**/ _______, KC_DEL,  _______, _______
  )
};
