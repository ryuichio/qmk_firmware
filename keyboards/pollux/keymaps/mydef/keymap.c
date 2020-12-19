//
// make pollux/rev2:mydef:avrdude
//

#include "pollux.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
#include "./rgb.c"
#endif

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  IMEOFF,
  IMEON,
  ADJUST,
  BACKLIT,
  RGBRST,
  SP_GUI,
  SP_ALT,
  SP_SPC,
  SP_BS,
};

#define _IS_MAC   (keymap_config.swap_lalt_lgui == false)

/* KEYCODE DEFINITIONS */

#define KC_____ KC_TRNS
#define KC_XXXX KC_NO
#define KC_IMEOF IMEOFF
#define KC_IMEON IMEON
#define KC_RST  RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD

#define KC_NORM  AG_NORM
#define KC_SWAP  AG_SWAP
#define KC_GUI   SP_GUI
#define KC_ALT   SP_ALT
#define KC_SSPC  SP_SPC
#define KC_SBS   SP_BS

// Layer Mode aliases
#define KC_MLAD  MO(_ADJUST)


// Tap dances
enum tapdances{
  TD_SCCL = 0,
  TD_SLBS,
  TD_MIEQ,
  TD_CTTB,
};
#define KC_SCCL  TD(TD_SCCL)
#define KC_SLBS  TD(TD_SLBS)
#define KC_MIEQ  TD(TD_MIEQ)
#define KC_CTTB  TD(TD_CTTB)

static inline void _send_ctrl_by_mode(bool to_register) {
  if (to_register) {
    if (_IS_MAC) {
        register_code (KC_LGUI);
    } else {
        register_code (KC_LCTL);
    }
  } else {
    if (_IS_MAC) {
        unregister_code (KC_LGUI);
    } else {
        unregister_code (KC_LCTL);
    }
  }
}

static inline void _send_win_by_mode(bool to_register) {
  if (to_register) {
    if (_IS_MAC) {
        register_code (KC_LCTL);
    } else {
        register_code (KC_LGUI);
    }
  } else {
    if (_IS_MAC) {
        unregister_code (KC_LCTL);
    } else {
        unregister_code (KC_LGUI);
    }
  }
}

void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->keycode) {
    case KC_CTTB:
      if (state->count == 1) {
        _send_ctrl_by_mode(true);
      } else if (state->count == 2) {
        register_code(KC_TAB);
      }
      break;
  }
}
void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->keycode) {
    case KC_CTTB:
      if (state->count == 1) {
        _send_ctrl_by_mode(false);
      } else if (state->count == 2) {
        unregister_code(KC_TAB);
      }
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SCCL] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
  [TD_SLBS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
  [TD_MIEQ] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQL),
  [TD_CTTB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
};

/* KEYMAPS */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(                                                   \
    ESC,  Q,    W,    E,    R,    T,    Y,    /**/ Y,    U,    I,    O,    P,    MINS, EQL,  \
    CTTB, A,    S,    D,    F,    G,          /**/ H,    J,    K,    L,    SCCL, ENT, \
    LALT, LSFT, Z,    X,    C,    V,    B,    /**/ XXXX, N,    M,    COMM, DOT,  SLBS, GRV,  \
    /*                         */ IMEOF,SSPC,      SBS,  IMEON              \
  ),

  [_LOWER] = LAYOUT_kc(                                                  \
    ____, 1,    2,    3,    4,    5,    6,    /**/ 6,    7,    8,    9,    0,    UNDS, PLUS, \
    TAB,  EXLM, AT,   HASH, DLR,  PERC,       /**/ CIRC, AMPR, ASTR, LPRN, RPRN, ____, \
    GUI,  ____, XXXX, XXXX, XXXX, LCBR, LBRC, /**/ RBRC, RCBR, XXXX, XXXX, XXXX, XXXX, XXXX, \
    /*                         */ ____, ____,      DEL,  ____        \
  ),

  [_RAISE] = LAYOUT_kc(                                               \
    ____, F1,   F2,   F3,   F4,   F5,   F6,   /**/ XXXX, PGUP, UP,   PGDN, XXXX, XXXX, XXXX, \
    ____, F6,   F7,   F8,   F9,   F10,        /**/ HOME, LEFT, DOWN, RGHT, END,  ____, \
    ____, ____, F11,  F12,  XXXX, XXXX, XXXX, /**/ XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, \
    /*                         */ ____, ____,      DEL,  ____           \
  ),

  [_ADJUST] = LAYOUT_kc(                                               \
    RST,  LRST, XXXX, NORM, SWAP, XXXX, XXXX, /**/ XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, \
    LTOG, LHUI, LSAI, LVAI, XXXX, XXXX,       /**/ XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, \
    LMOD, XXXX, LHUD, LSAD, LVAD, XXXX, XXXX,  /**/ XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, \
    /*                         */ XXXX, XXXX,      XXXX, XXXX           \
  ),

};

/* USER TASKS */
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
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
      if (_IS_MAC) {
        _send_key(KC_LANG1);
      } else {
        _send_key(KC_HENK);
      }
    } else {
      if (_IS_MAC) {
        _send_key(KC_LANG2);
      } else {
        _send_key(KC_MHEN);
      }
    }
}

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
  return lower_pressed && (TIMER_DIFF_16(time, lower_pressed_time) < TAPPING_LAYER_TERM);
}

static inline bool is_raise_pressed(uint16_t time) {
  return raise_pressed && (TIMER_DIFF_16(time, raise_pressed_time) < TAPPING_LAYER_TERM);
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

// void matrix_scan_user (void) {
//  #ifdef RGBLIGHT_ENABLE
//   rgb_update(false);
//  #endif
// }

// void keybaord_post_init_user (void) {
//  #ifdef RGBLIGHT_ENABLE
//   rgb_update(false);
//  #endif
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGBLIGHT_ENABLE
  rgb_process_record(keycode, record);
#endif
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case IMEOFF:
      if (record->event.pressed) {
        _change_ime(false);
      }
      return false;
      break;
    case IMEON:
      if (record->event.pressed) {
        _change_ime(true);
      }
      return false;
      break;
    case SP_SPC:
      if (record->event.pressed) {
        set_lower_pressed(record->event.time);
      } else {
        if (is_lower_pressed(record->event.time)) {
          _send_key(KC_SPC);
        }
        lower_pressed = false;
      }
      update_change_layer(record->event.pressed, _LOWER, _RAISE, _ADJUST);
      return false;
      break;
    case SP_BS:
      if (record->event.pressed) {
        set_raise_pressed(record->event.time);
      } else {
        if (is_raise_pressed(record->event.time)) {
          _send_key(KC_BSPC);
        }
        raise_pressed = false;
      }
      update_change_layer(record->event.pressed, _RAISE, _LOWER, _ADJUST);
      return false;
      break;
    case KC_ALT:
      if (record->event.pressed) {
        register_code(KC_LALT);
      } else {
        unregister_code(KC_LALT);
      }
      break;
    case KC_GUI:
      if (record->event.pressed) {
        _send_win_by_mode(true);
      } else {
        _send_win_by_mode(false);
      }
      break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    default:
      if (record->event.pressed) {
        reset_layer_pressed();
      }
      break;
  }
  return true;
}
