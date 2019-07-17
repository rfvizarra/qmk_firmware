/* Copyright 2018  Rodrigo Fernández-Vizarra
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

// Layer shorthand
enum xd75_layers {
  _QWERTY,
  _MENU,
  _RAISE,
  _LOWER,
  _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  GAME
};

#define MENU MO(_MENU)
#define CTRIGHT LCTL(KC_RGHT)
#define CTLEFT LCTL(KC_LEFT)
#define CTLINS LCTL(KC_INS)
#define SHFTINS LSFT(KC_INS)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | +      | `      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      |  ]     | \      | \      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | LCRTL  | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | "      | ENTER  | HOME   | PGUP   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | RSHIFT | ENTER  | END    | PGDOWN |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCRTL  | LCTRL  | LGUI   | LALT   | LOWER  | SPC    | SPC    | RAISE  | RGUI   | RCTRL  | RALT   | LEFT   | UP     | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QWERTY] = LAYOUT_ortho_5x15(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS,KC_EQUAL,KC_GRV,  KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y ,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_BSLS,
  KC_RCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_HOME, KC_PGUP,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_ENT, KC_END,  KC_PGDN,
  MENU,    KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RGUI, KC_RCTL, KC_RALT, KC_LEFT,  KC_UP,  KC_DOWN, KC_RIGHT
 ),

 /* MENU
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |  VOL+  |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        | NEXT   |  VOL-  | PLAY   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
  [_MENU] = LAYOUT_ortho_5x15(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 , _______, _______,
    _______, _______, _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, _______, _______, _______,_______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_MPLY
  ),

/* RAISE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        | CTRIGHT|        |        | CTLINS |        |        |        | SHFTINS|        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | HOME   | PGDOWN | PGUP   | END    |        | LEFT   | DOWN   | UP     | RIGHT  |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | DEL    |        |        | CTLEFT |        |        |        |        |        |        |        |  VOL+  |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        | NEXT   |  VOL-  | PLAY   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_RAISE] = LAYOUT_ortho_5x15(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, CTRIGHT, _______, _______, CTLINS,  _______, _______, _______, SHFTINS, _______, _______, _______, _______,
  _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______, _______, _______, _______,
  _______, _______, KC_DEL,  _______, _______, CTLEFT,  _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT,  KC_VOLD, KC_MPLY
 ),

 /* LOWER
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        | CTRIGHT|        |        | CTLINS |        |        |        | SHFTINS|        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | HOME   | PGDOWN | PGUP   | END    |        | LEFT   | DOWN   | UP     | RIGHT  |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |  VOL+  |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | DEL    |        |        | CTLEFT |        |        |        |        |        |        | NEXT   |  VOL-  | PLAY   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
  [_LOWER] = LAYOUT_ortho_5x15(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, CTRIGHT, _______, _______, CTLINS,  _______, _______, _______, SHFTINS, _______, _______, _______, _______,
    _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______,
    _______, _______, KC_DEL,  _______, _______, CTLEFT, _______, _______, _______, _______, _______, _______, KC_MNXT,  KC_VOLD, KC_MPLY
  ),


  /* ADJUST
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | RESET  |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        | QWERTY |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
  [_ADJUST] = LAYOUT_ortho_5x15(
    RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, QWERTY,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};

uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case QWERTY:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY);
    }
    return false;
    break;
  }
  return true;
}
