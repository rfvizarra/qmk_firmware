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
  _GAME,
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
#define CENT CTL_T(KC_ENT)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | `      | 1      | 2      | 3      | 4      | 5      | HOME   | END    | 6      | 7      | 8      | 9      | 0      | DEL    | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | ESC    | Q      | W      | E      | R      | T      | INS    | ??     | Y      | U      | I      | O      | P      | \      | PGUP   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | TAB    | A      | S      | D      | F      | G      | [      | ]      | H      | J      | K      | L      | ;      | '      | PGDOWN |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | NAV    | Z      | X      | C      | V      | B      | -      | =      | N      | M      | ,      | .      | /      | UP     | DEL    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCRTL  | LALT   | LGUI   | LOWER  | LSHIFT | CTL/EN | RGUI   | RALT   | SPACE  | RAISE  | RALT   | FN     | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QWERTY] = LAYOUT_ortho_5x15(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME, KC_END,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  KC_BSPC,
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_INS,  RGB_TOG, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, KC_PGUP,
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC, KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_PGDOWN,
  MENU,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MINS, KC_EQL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_DEL,
  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_LSFT, CENT,    KC_RGUI, KC_RALT, KC_SPC,  RAISE,   KC_RALT, MENU,    KC_LEFT, KC_DOWN, KC_RIGHT
 ),

 /* MENU
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     |        |        | F6     | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        | UP     |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        | LEFT   | DOWN   | RIGHT  |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |  VOL+  |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        | NEXT   |  VOL-  | PLAY   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
  [_MENU] = LAYOUT_ortho_5x15(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_MPLY
  ),

/* RAISE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | RGB HD | RGB HI | F6     | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | `      | 1      | 2      | 3      | 4      | 5      | RGB SD | RGB SI | 6      | 7      | 8      | 9      | 0      |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |RGB_MODE_PLAIN| RGB VD | RGB VI |RGB_MODE_BREATHE|        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | RGB RMD| RGB MD |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | Next   | Vol-   | Vol+   | Play   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_RAISE] = LAYOUT_ortho_5x15( 
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   RGB_HUD, RGB_HUI, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 ,
  KC_GRV , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    RGB_SAD, RGB_SAI, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______,
  _______, _______, _______, _______, _______, RGB_MODE_PLAIN, RGB_VAD, RGB_VAI, RGB_MODE_BREATHE,RGB_MODE_RAINBOW,RGB_MODE_SWIRL,RGB_MODE_SNAKE,RGB_MODE_KNIGHT,RGB_MODE_XMAS,RGB_MODE_GRADIENT,
  _______, _______, _______, _______, _______, _______, RGB_RMOD,RGB_MOD, _______, _______, _______, _______, _______, KC_VOLU, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_MPLY
 ),

 /* LOWER
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     |        |        | F6     | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | `      | !      | @      | #      | $      | %      |        |        | ^      | &      | *      | (      | )      |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | ~      |        | /      | {      | [      |        |        | ]      | }      | \      | -      | +      | |      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | _      | =      |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | Next   | Vol-   | Vol+   | Play   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
  [_LOWER] = LAYOUT_ortho_5x15(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 ,
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______,
    _______, KC_TILD, _______, KC_SLASH,KC_LCBR, KC_LBRC, _______, _______, KC_RBRC, KC_RCBR, KC_BSLASH,KC_MINUS,KC_PLUS,KC_PIPE, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_EQL,  KC_VOLU, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_MPLY
  ),

  /* GAME
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | `      | 1      | 2      | 3      | 4      | 5      | HOME   | END    | 6      | 7      | 8      | 9      | 0      | DEL    | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | ESC    | Q      | W      | E      | R      | T      | INS    | ??     | Y      | U      | I      | O      | P      | \      | PGUP   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | TAB    | A      | S      | D      | F      | G      | [      | ]      | H      | J      | K      | L      | ;      | '      | PGDOWN |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | -      | =      | N      | M      | ,      | .      | /      | UP     | DEL    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCRTL  | LALT   | LGUI   | LOWER  | LCRTL  | SPACE  | CTL/EN | RALT   | SPACE  | RAISE  | RALT   | FN     | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_GAME] = LAYOUT_ortho_5x15(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME, KC_END,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  KC_BSPC,
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_INS,  RGB_TOG, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, KC_PGUP,
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC, KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_PGDOWN,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MINS, KC_EQL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_DEL,
  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_LCTL, KC_SPC,  CENT,    KC_RALT, KC_SPC,  RAISE,   KC_RALT, MENU,    KC_LEFT, KC_DOWN, KC_RIGHT
 ),

  /* ADJUST
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | RESET  |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |  GAME  |        |        |        |        | QWERTY |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
  [_ADJUST] = LAYOUT_ortho_5x15(
    RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, GAME,    _______, _______, _______, _______, QWERTY,  _______, _______, _______, _______, _______,
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
  /*case COLEMAK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_COLEMAK);
    }
    return false;
    break;
  case DVORAK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_DVORAK);
    }
    return false;
    break;*/
  case GAME:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_GAME);
    }
    return false;
    break;
  }
  return true;
}