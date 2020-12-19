#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

//
// make crkbd:mydef:avrdude
//

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
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
  SP_CTL,
  SP_GUI,
  SP_ALT,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define _IS_MAC   (keymap_config.swap_lalt_lgui == false)

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_IMEOF IMEOFF
#define KC_IMEON IMEON
#define KC_RST   RESET
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
#define KC_CTL   SP_CTL

enum tapdances{
  TD_SCCL = 0,
  TD_SLBS,
  TD_MIEQ,
};
#define KC_SCCL  TD(TD_SCCL)
#define KC_SLBS  TD(TD_SLBS)
#define KC_MIEQ  TD(TD_MIEQ)

// Layer Mode aliases
#define KC_MLAD  MO(_ADJUST)

// Layer taps
#define KC_SPLO  LT(_LOWER, KC_SPC)
#define KC_BSRA  LT(_RAISE, KC_BSPC)

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

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SCCL] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
  [TD_SLBS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
  [TD_MIEQ] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  MIEQ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        CTL,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCCL,   ENT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLBS,   GRV,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  IMEOF,  SPLO,   ALT,      GUI,  BSRA, IMEON\
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  MIEQ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        TAB,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX,  LCBR,  LBRC,                   RBRC,  RCBR, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____,   DEL, _____\
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,    F1,    F2,    F3,    F4,    F5,                  XXXXX,  PGUP,    UP,  PGDN, XXXXX,   EQL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,    F6,    F7,    F8,    F9,   F10,                   HOME,  LEFT,  DOWN, RIGHT,   END, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,   F11,   F12, XXXXX,  LCBR,  LBRC,                   RBRC,  RCBR, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____,  MLAD, _____,    _____,  _____, _____\
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, XXXXX,  NORM,  SWAP, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____\
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
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

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
//const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, " ");
    matrix_write(matrix, read_mode_icon(!_IS_MAC));
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

static bool ctrl_pressed = false;
static uint16_t ctrl_pressed_time = 0;

static inline void set_ctrl_pressed(uint16_t time) {
  ctrl_pressed = true;
  ctrl_pressed_time = time;
}

static inline bool is_ctrl_pressed(uint16_t time) {
  return ctrl_pressed && (TIMER_DIFF_16(time, ctrl_pressed_time) < TAPPING_LAYER_TERM);
}

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

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
    case SP_CTL:
      if (record->event.pressed) {
        _send_ctrl_by_mode(true);
        set_ctrl_pressed(record->event.time);
      } else {
        _send_ctrl_by_mode(false);
        if (is_ctrl_pressed(record->event.time)) {
          _send_key(KC_TAB);
        }
        ctrl_pressed = false;
      }
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
      break;
  }
  return true;
}
