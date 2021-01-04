#include QMK_KEYBOARD_H
#include "keymap_jp.h"

//
// make treadstone32/lite:mydef:avrdude
//
#define _MAC

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  LOWER,
  RAISE,
};

enum tapdances{
    TD_PMIN = 0,
    TD_OEQL,
};

// Layer Mode aliases
#define KC_MLAD  MO(_ADJUST)

#ifdef _MAC
#define MY_LGUI KC_LCTL
#define IME_ON  KC_LANG1
#define IME_OFF KC_LANG2
#else
#define MY_LGUI KC_LGUI
#define IME_ON  KC_HENK
#define IME_OFF KC_MHEN
#endif

// Base layer mod tap
#ifdef _MAC
#define KC_A_CT  LGUI_T(KC_A)
#else
#define KC_A_CT  LCTL_T(KC_A)
#endif
#define KC_Z_SF  LSFT_T(KC_Z)
#define KC_X_AL  LALT_T(KC_X)
#ifdef _MAC
#define KC_C_GU  LCTL_T(KC_C)
#define KC_V_GU  LCTL_T(KC_V)
#else
#define KC_C_GU  LGUI_T(KC_C)
#define KC_V_GU  LGUI_T(KC_V)
#endif
#define KC_SSSF  RSFT_T(KC_SLSH)
#ifdef _MAC
#define KC_ENCT  RGUI_T(KC_ENT)
#else
#define KC_ENCT  RCTL_T(KC_ENT)
#endif

// Lower layer mod tap
#ifdef _MAC
#define KC_F6CT  LGUI_T(KC_F6)
#else
#define KC_F6CT  LCTL_T(KC_F6)
#endif
#define KC_QUCT  RCTL_T(KC_QUOT)
#define KC_11SF  LSFT_T(KC_F11)
#define KC_12AL  LALT_T(KC_F12)

// Layer tap
#define KC_SPLO  LT(_LOWER, KC_SPC)
#define KC_BSRA  LT(_RAISE, KC_BSPC)

// Tap dance
#define KC_PMIN  TD(TD_PMIN)
#define KC_OEQL  TD(TD_OEQL)

qk_tap_dance_action_t tap_dance_actions[] = {
   [TD_PMIN] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_MINS),
   [TD_OEQL] = ACTION_TAP_DANCE_DOUBLE(KC_O, KC_EQL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //,---------------------------------------------------------------------------------------------------.
          KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,  KC_OEQL,  KC_PMIN,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_A_CT,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,  KC_ENCT,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_Z_SF,  KC_X_AL,     KC_C,  KC_V_GU,     KC_B,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SSSF,
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               KC_SPLO,  KC_BSRA
  //                                        `---------|---------'
  ),

  [_LOWER] = LAYOUT(
  //,---------------------------------------------------------------------------------------------------.
          KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_SCLN,  KC_QUCT,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_ESC,   KC_TAB,  XXXXXXX,  KC_LCBR,  KC_LBRC,  KC_RBRC,  KC_RCBR,  XXXXXXX,    KC_RO,   KC_GRV,
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               _______,   KC_DEL
  //                                        `---------|---------'
  ),

  [_RAISE] = LAYOUT(
  //,---------------------------------------------------------------------------------------------------.
         KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,  XXXXXXX,  KC_PGUP,    KC_UP,  KC_PGDN,  KC_BSLS,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_F6CT,    KC_F7,    KC_F8,    KC_F9,   KC_F10,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_11SF,  KC_12AL,  XXXXXXX,  MY_LGUI,  IME_OFF,   IME_ON,    KC_RO,  KC_COMM,   KC_DOT,  KC_SSSF,
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               KC_MLAD,  _______
  //                                        `---------|---------'
  ),

  [_ADJUST] = LAYOUT(
  //,---------------------------------------------------------------------------------------------------.
        RESET,    RGBRST,  AG_NORM,  AG_SWAP,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_INS,  KC_PSCR,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  XXXXXXX,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  KC_NLCK,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  XXXXXXX,  KC_BTN1,  KC_BTN2,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               _______,  _______
  //                                        `---------|---------'
  )
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SPLO:
      return TAPPING_LAYER_TERM;
    case KC_BSRA:
      return TAPPING_LAYER_TERM;
    default:
      return TAPPING_TERM;
  }
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    #ifdef RGBLIGHT_ENABLE
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGBRST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    default:
      result = true;
      break;
  }

  return result;
}

void keyboard_post_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
}
