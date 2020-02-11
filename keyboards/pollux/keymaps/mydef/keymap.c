// make pollux/rev2:mydef

#include "pollux.h"

extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
#include "./rgb.c"
#endif

/* GLOBAL VARS */

enum layer_layouts {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  KC_LOWR = SAFE_RANGE,
  KC_RAIS,
  KC_AJST,
};

enum tapdances{
  TD_SCCL = 0,
  TD_SLBS,
  TD_MIEQ,
};

/* KEYCODE DEFINITIONS */

#define KC_____ KC_TRNS
#define KC_XXXX KC_NO
#define KC_RST  RESET

#define KC_SCCL  TD(TD_SCCL)
#define KC_SLBS  TD(TD_SLBS)
#define KC_MIEQ  TD(TD_MIEQ)

//#define _MAC
#ifdef _MAC
#define KC_CTRL  KC_LGUI
#define KC_WIN   KC_LCTL
#else
#define KC_CTRL  KC_LCTL
#define KC_WIN   KC_LGUI
#endif

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SCCL] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
  [TD_SLBS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
  [TD_MIEQ] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQL),
};

/* KEYMAPS */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_kc(                                                   \
    ESC,  Q,    W,    E,    R,    T,    Y,    /**/ Y,    U,    I,    O,    P,    MINS, EQL,  \
    CTRL, A,    S,    D,    F,    G,          /**/ H,    J,    K,    L,    SCLN, ENT, \
    LSFT, LALT, Z,    X,    C,    V,    B,    /**/ B,    N,    M,    COMM, DOT,  SLSH, BSLS, \
    /*                         */ LOWR, SPC,       BSPC, RAIS              \
  ),

  [_LOWER] = LAYOUT_kc(                                                  \
    TAB,  1,    2,    3,    4,    5,    6,    /**/ 6,    7,    8,    9,    0,    UNDS, PLUS, \
    ____, EXLM, AT,   HASH, DLR,  PERC,       /**/ CIRC, AMPR, ASTR, LPRN, RPRN, ____, \
    ____, WIN,  XXXX, XXXX, XXXX, LCBR, LBRC, /**/ RBRC, RCBR, XXXX, LBRC, RBRC, XXXX, XXXX, \
    /*                         */ ____, ____,      DEL,  ____        \
  ),

  [_RAISE] = LAYOUT_kc(                                               \
    TAB,  F1,   F2,   F3,   F4,   F5,   F6,   /**/ XXXX, PGUP, UP,   PGDN, XXXX, XXXX, XXXX, \
    RST,  F6,   F7,   F8,   F9,   F10,        /**/ HOME, LEFT, DOWN, RGHT, END,  ____, \
    ____, WIN,  F11,  F12,  XXXX, XXXX, XXXX, /**/ XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, \
    /*                         */ ____, ____,      DEL,  ____           \
  ),

  [_ADJUST] = LAYOUT_kc(                                               \
    RST,  ____, ____, ____, ____, ____, ____, /**/ ____, ____, ____, ____, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____,       /**/ ____, ____, ____, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, /**/ ____, ____, ____, ____, ____, ____, ____, \
    /*                         */ ____, ____,      ____, ____           \
  ),

};

/* USER TASKS */

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

void matrix_scan_user (void) {
 #ifdef RGBLIGHT_ENABLE
  rgb_update(false);
 #endif
}

void keybaord_post_init_user (void) {
 #ifdef RGBLIGHT_ENABLE
  rgb_update(false);
 #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGBLIGHT_ENABLE
  rgb_process_record(keycode, record);
#endif
  switch (keycode) {
    case KC_LOWR:
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
    case KC_RAIS:
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
