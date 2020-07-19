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
  KC_IMEOF,
  KC_IMEON,
  KC_WIN,
  KC_CTL,
  KC_ALT,
};

enum tapdances{
  TD_SCCL = 0,
  TD_SLBS,
  TD_MIEQ,
  TD_CTTB,
};

// macro key definitions
#define XXXXXXX  KC_NO
#define KC_SCCL  TD(TD_SCCL)
#define KC_SLBS  TD(TD_SLBS)
#define KC_MIEQ  TD(TD_MIEQ)
#define KC_CTTB  TD(TD_CTTB)
#define KC_ALTB  LALT(KC_TAB)
#define KC_RATB  LSFT(LALT(KC_TAB))

#define _IS_MAC   (keymap_config.swap_lalt_lgui == false)

// Layer Mode aliases
#define KC_MLAD  MO(_ADJUST)

// Layer taps
#define KC_SPLO  LT(_LOWER, KC_SPC)
#define KC_BSRA  LT(_RAISE, KC_BSPC)

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
    KC_CTTB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCCL, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
    XXXXXXX, KC_LCTL, KC_ALT,  KC_WIN,  KC_IMEOF,KC_SPLO, KC_BSRA, KC_IMEON,KC_ALT,  KC_ALTB, KC_RATB, KC_GRV
),
/* Lower */
[_LOWER] = LAYOUT(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
    KC_TAB,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_QUOT,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, KC_LABK, KC_RABK, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, _______, KC_DEL,  _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_TILD
),
/* Raise */
[_RAISE] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX, KC_PGUP, KC_UP,   KC_PGDN, XXXXXXX, XXXXXXX,
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,  _______,
    _______, KC_F11,  KC_F12,  XXXXXXX, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, KC_MLAD, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
/* Adjust */
[_ADJUST] = LAYOUT(
    RESET,   _______, _______, AG_NORM, AG_SWAP, _______, _______, _______, _______, _______, _______, _______,
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

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  switch (layer) {
  case 0:
    // LED 00
    writePinHigh(B0);
    writePinHigh(D5);
    break;
  case 1:
    // LED 01
    writePinHigh(B0);
    writePinLow(D5);
    break;
  case 2:
    // LED 10
    writePinLow(B0);
    writePinHigh(D5);
    break;
  case 3:
    // LED 11
    writePinLow(B0);
    writePinLow(D5);
    break;
  }
}

void led_set_user(uint8_t usb_led) {
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
  switch (keycode) {
    case KC_IMEOF:
      if (record->event.pressed) {
        _change_ime(false);
      }
      return false;
      break;
    case KC_IMEON:
      if (record->event.pressed) {
        _change_ime(true);
      }
      return false;
      break;
    case KC_WIN:
      if (record->event.pressed) {
          _send_win_by_mode(true);
      } else {
          _send_win_by_mode(false);
      }
      return false;
      break;
    case KC_CTL:
      if (record->event.pressed) {
          _send_ctrl_by_mode(true);
      } else {
          _send_ctrl_by_mode(false);
      }
      return false;
      break;
    case KC_ALT:
      if (record->event.pressed) {
        register_code(KC_LALT);
      } else {
        unregister_code(KC_LALT);
      }
      return false;
      break;
    default:
      break;
  }
  return true;
}
