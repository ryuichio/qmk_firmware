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
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  SP_GUI,
  SP_ALT
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
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

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SCCL] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
  [TD_SLBS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
  [TD_MIEQ] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQL),
  [TD_CTTB] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_TAB),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  MIEQ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       CTTB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCCL,   ENT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLBS,   GRV,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,   SPC,   ALT,      GUI,  BSPC, RAISE\
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  MIEQ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       CTTB,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,   ENT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX,  LBRC,  RBRC, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,   SPC,   ALT,      GUI,  BSPC, RAISE\
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,    F1,    F2,    F3,    F4,    F5,                  XXXXX,  PGUP,    UP,  PGDN, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       CTTB,    F6,    F7,    F8,    F9,   F10,                   HOME,  LEFT,  DOWN, RIGHT,   END,   ENT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,   F11,   F12, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,   SPC,   ALT,      GUI,   DEL, RAISE\
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
                                  LOWER,   SPC,   ALT,      GUI,  BSPC, RAISE\
                              //`--------------------'  `--------------------'
  )
};

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
    if (keymap_config.swap_lalt_lgui == false) {  // mac
        if (enable) {
            _send_key(KC_LANG1);
        } else {
            _send_key(KC_LANG2);
        }
    } else {  // win
        if (enable) {
            _send_key(KC_HENK);
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
const char *read_logo(int pattern);
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

static int logo_pattern = 0;
void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, " ");
    matrix_write(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo(logo_pattern));
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
    logo_pattern = 1;
  } else {
    logo_pattern = 0;
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
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
    case KC_ALT:
      if (record->event.pressed) {
        register_code(KC_LALT);
      } else {
        unregister_code(KC_LALT);
      }
      break;
    case KC_GUI:
      if (record->event.pressed) {
        register_code(KC_LGUI);
      } else {
        unregister_code(KC_LGUI);
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
