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

//
// make choco60:mydef:avrdude
//

#include QMK_KEYBOARD_H
#include "keymap_jp.h"

enum layer_names {
    _BASE,
    _LOWER,
    _FN,
};

#define KC_FN MO(_FN)
#define KC_LOWER MO(_LOWER)
#define SP_BSLS KC_INT3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, /* */ KC_7, KC_8, KC_9, KC_0, KC_MINUS, JP_EQL,  JP_GRV, KC_BSPACE,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, /* */ KC_Y, KC_U, KC_I, KC_O, KC_P, JP_LBRC,  JP_RBRC, SP_BSLS,
    KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, /* */ KC_H, KC_J, KC_K, KC_L, JP_SCLN, KC_QUOTE, KC_ENTER,
    KC_LOWER, KC_Z, KC_X, KC_C, KC_V, KC_B, /* */ KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, KC_FN,
    KC_LALT,  KC_LGUI, KC_SPACE, /* */ KC_FN, KC_BSPACE, KC_LANG2, KC_LANG1
  ),
  [_LOWER] = LAYOUT(
    KC_ESC,  JP_EXLM, JP_AT,   JP_HASH, JP_DLR,  JP_PERC, /* */ JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, JP_UNDS, JP_PLUS, JP_TILD, KC_DELETE,
    LSFT(KC_TAB),   LSFT(KC_Q), LSFT(KC_W), LSFT(KC_E), LSFT(KC_R), LSFT(KC_T), /* */ LSFT(KC_Y), LSFT(KC_U), LSFT(KC_I), LSFT(KC_O), LSFT(KC_P),  JP_LCBR, JP_RCBR, JP_PIPE,
    LSFT(KC_LCTRL), LSFT(KC_A), LSFT(KC_S), LSFT(KC_D), LSFT(KC_F), LSFT(KC_G), /* */ LSFT(KC_H), LSFT(KC_J), LSFT(KC_K), LSFT(KC_L), JP_COLN, JP_DQT,  LSFT(KC_ENTER),
    LSFT(KC_LOWER), LSFT(KC_Z), LSFT(KC_X), LSFT(KC_C), LSFT(KC_V), LSFT(KC_B), /* */ LSFT(KC_N), LSFT(KC_M), LSFT(KC_COMMA), LSFT(KC_DOT), LSFT(KC_SLASH), KC_RSHIFT, KC_FN,
    LSFT(KC_LALT),  LSFT(KC_LGUI), LSFT(KC_SPACE),                              /* */ KC_FN,      KC_DELETE, _______, _______
  ),
  [_FN] = LAYOUT(
    RESET, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,           /* */ KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INSERT, KC_DELETE,
    _______, _______, _______, _______, _______, _______, /* */ _______, KC_PGUP, KC_UP,   KC_PGDOWN, _______, _______, KC_RBRACKET, KC_BSPACE,
    _______, _______, _______, _______, _______, _______, /* */ KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,  KC_END,  _______, KC_ENTER,
    _______, _______, _______, _______, _______, _______, /* */ _______, _______, _______, _______,  _______,  KC_RSHIFT, KC_FN,
    _______, _______, _______,                            /* */ KC_FN,   KC_DELETE, _______, _______
  )
};
