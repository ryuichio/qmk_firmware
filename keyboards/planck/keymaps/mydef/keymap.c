/* Copyright 2015-2017 Jack Humbert
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
// make planck/rev6:mydef:dfu-util
//

#include QMK_KEYBOARD_H
#include "muse.h"


enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
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

/* Qwerty */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MIEQ,
    KC_CTTB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCCL, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
    XXXXXXX, KC_LCTL, KC_WIN,  KC_ALT,  KC_IMEOF,KC_SPLO, KC_BSRA, KC_IMEON,KC_ALT,  KC_ALTB, KC_RATB, KC_GRV
),

/* Lower */
[_LOWER] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX, KC_PGUP, KC_UP,   KC_PGDN, XXXXXXX, XXXXXXX,
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,  _______,
    _______, KC_F11,  KC_F12,  XXXXXXX, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, KC_MLAD, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Raise */
[_RAISE] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX, KC_PGUP, KC_UP,   KC_PGDN, XXXXXXX, XXXXXXX,
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,  _______,
    _______, KC_F11,  KC_F12,  XXXXXXX, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, KC_MLAD, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    RESET,  _______, _______, AG_NORM, AG_SWAP, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, _______,
    AU_ON,  RGB_TOG, MU_MOD,  _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    MU_OFF, RGB_MOD, MUV_IN,  MU_ON,   MU_OFF,  _______, _______, TERM_ON, TERM_OFF, _______, _______, _______,
    DEBUG,  MUV_DE,  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
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

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

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
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}
