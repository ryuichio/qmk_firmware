//
// My Mac and Windows key map
// make ergodash/mini:mymac:avrdude
//
#include QMK_KEYBOARD_H
#include "keymap_jp.h"

// Uncomment for Macs
//#define _MY_MAC

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

#ifdef _MY_MAC
#define _IME_ON     KC_LANG1
#define _IME_OFF    KC_LANG2
#define _LEFT_PINKY KC_LGUI  // Command
#define _LEFT_RING  KC_LALT  // Option
#define _LEFT_MID   KC_LCTL  // Control
#else
#define _IME_ON  KC_HENK
#define _IME_OFF KC_MHEN
#define _LEFT_PINKY KC_LCTL  // Ctrl
#define _LEFT_RING  KC_LGUI  // Win
#define _LEFT_MID   KC_LALT  // Alt
#endif

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  Esc |   Q  |   W  |   E  |   R  |   T  |  -=  |                    |  ^~  |   Y  |   U  |   I  |   O  |   P  |  @`  |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Cmd  |   A  |   S  |   D  |   F  |   G  |  [{  |                    |  ]}  |   H  |   J  |   K  |   L  |  ;+  |  :*  |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |      | Home |      |  End |      |   N  |   M  |  ,<  |  .>  |  Up  |  /?  |
   * |-------------+------+------+------+------+      +------+------+------+      +------+------+------+------+-------------|
   * | Cmd  |  Alt | Ctrl |   _  |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise||||||||  \|  | Left | Down | Right|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    KC_ESC,      KC_Q,       KC_W,      KC_E,    KC_R,    KC_T,    JP_MINS,                        JP_CIRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT  , \
    _LEFT_PINKY, KC_A,       KC_S,      KC_D,    KC_F,    KC_G,    JP_LBRC,                        JP_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN, \
    KC_LSFT,     KC_Z,       KC_X,      KC_C,    KC_V,    KC_B,             KC_HOME,       KC_END ,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP  , KC_SLSH, \
    _LEFT_PINKY, _LEFT_RING, _LEFT_MID, JP_UNDS,          LOWER,   KC_SPC , KC_DEL,        KC_BSPC,KC_ENT , RAISE,            JP_YEN,  KC_LEFT, KC_DOWN, KC_RGHT  \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | Tab  |   !  |   "  |   #  |   $  |   %  |   _  |                    |   +  |   &  |   '  |   (  |   )  |      |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |   ~  |   1  |   2  |   3  |   4  |   5  |   {  |                    |   }  |   6  |   7  |   8  |   9  |   0  |  -   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   6  |   7  |   8  |   9  |   0  |      | Home |      |  End |      |   N  |   M  |   <  |   >  | PgUp | Shift|
   * |-------------+------+------+------+------+      +------+------+------+      +------+------+------+------+-------------|
   * | Cmd  |  Alt | Ctrl |   _  |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise||||||||  \|  | Home |PgDown|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    KC_GRV,      JP_EXLM,    JP_DQT,    JP_HASH, JP_DLR,  JP_PERC, JP_UNDS,                        JP_PLUS, JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, _______, JP_MINS, \
    KC_TILD,     KC_1,       KC_2,      KC_3,    KC_4,    KC_5,    JP_LBRC,                        JP_RBRC, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_MINS, \
    KC_LSFT,     KC_6,       KC_7,      KC_8,    KC_9,    KC_0,             KC_HOME,       KC_END,          KC_N,    KC_M,    KC_LT,   KC_GT,   KC_PGUP, KC_QUES, \
    _LEFT_PINKY, _LEFT_RING, _LEFT_MID, JP_UNDS,          LOWER,   KC_SPC , KC_DEL,        KC_BSPC,KC_ENT , RAISE,            JP_YEN,  KC_HOME, KC_PGDN, KC_END   \
  ),

  /* Raise
  * ,----------------------------------------------------------------------------------------------------------------------.
  * |   `  |   !  |   "  |   #  |   $  |   %  |   _  |                    |   +  |   &  |   '  |   (  |   )  |      |  |   |
  * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
  * |   ~  |   F1 |   F2 |   F3 |   F4 |   F5 |   {  |                    |   }  |   F6 |   F7 |   F8 |   F9 |  F10 |  "   |
  * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
  * | Shift|  F11 |  F12 |      |      |      |      | Home |      |  End |      |   N  |   M  |   <  |   >  | PgUp | Shift|
  * |-------------+------+------+------+------+      +------+------+------+      +------+------+------+------+-------------|
  * | Cmd  |  Alt | Ctrl |   _  |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise||||||||  \|  | Home |PgDown|  End |
  * ,----------------------------------------------------------------------------------------------------------------------.
  */
  [_RAISE] = LAYOUT(
    KC_TAB,      JP_EXLM,    JP_DQT,    JP_HASH, JP_DLR,  JP_PERC, JP_UNDS,                        JP_PLUS, JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, _______, JP_MINS, \
    KC_TILD,     KC_F1,      KC_F2,     KC_F3,   KC_F4,   KC_F5,   JP_LBRC,                        JP_RBRC, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DQT , \
    KC_LSFT,     KC_F11,     KC_F12,    _______, _______, _______,          KC_HOME,       KC_END,          KC_N,    KC_M,    KC_LT,   KC_GT,   KC_PGUP, KC_RSFT, \
    _LEFT_PINKY, _LEFT_RING, _LEFT_MID, JP_UNDS,          LOWER,   KC_SPC , KC_DEL,        KC_BSPC,KC_ENT , RAISE,            JP_YEN,  KC_HOME, KC_PGDN, KC_END   \
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
    _______, _______, BL_TOGG, BL_BRTG, BL_INC , BL_DEC ,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______  \
  )
};

static bool lower_pressed = false;
static bool raise_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (lower_pressed) {
          register_code(_IME_OFF);
          unregister_code(_IME_OFF);
        }
        lower_pressed = false;
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (raise_pressed) {
          register_code(_IME_ON);
          unregister_code(_IME_ON);
        }
        raise_pressed = false;
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    default:
      if (record->event.pressed) {
        lower_pressed = false;
        raise_pressed = false;
      }
      break;
  }
  return true;
}
