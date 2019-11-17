#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

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
#define _LOWER 3
#define _RAISE 4
#define _NAV   5
#define _NAV2  6
#define _NAV3  7
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
  RGBRST
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
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
#define KC_RMOD  RGB_RMOD
#define KC_ALTTB ALT_T(KC_TAB)
#define KC_ENTCTL CTL_T(KC_ENT)
//#define KC_LOWER TD(LOWER_LGUI)
#define KC_LOWER MO(_LOWER)
#define KC_RALT_LGUI TD(RALT_LGUI)
//#define KC_RAISE LT(_RAISE, KC_BSPC)
#define KC_RAISE MO(_RAISE)
#define KC_NAV MO(_NAV)
#define KC_LOCK  RGUI(KC_L)
#define KC_MGKSPC LT(_NAV3, KC_SPC)
#define KC_FORWRD LCTL(KC_RIGHT)
#define KC_BACKWRD LCTL(KC_LEFT)
#define KC_YANK LCTL(KC_INS)
#define KC_PASTE LSFT(KC_INS)

enum td_keycodes {
  RALT_LGUI = 0
};

typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD
} td_state_t;

static td_state_t td_state;

int curr_dance (qk_tap_dance_state_t *state);

void raltlgui_finished(qk_tap_dance_state_t *state, void *user_data);
void raltlgui_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      ALTTB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      NAV,       Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,   DEL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER, LSFT, ENTCTL,   RALT_LGUI, MGKSPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX,  TILD, XXXXX, SLASH,  LCBR,  LBRC,                   RBRC,  RCBR,BSLASH, MINUS,  PLUS,  PIPE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       XXXXX, XXXXX, XXXXX, XXXXX, LGUI, XXXXX,                  XXXXX, XXXXX, _____,  UNDS,  EQL, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER, LSFT, ENTCTL,   RALT_LGUI,MGKSPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX,  TILD, XXXXX, SLASH,  LCBR,  LBRC,                   RBRC,  RCBR,BSLASH, MINUS,  PLUS,  PIPE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX,  MNXT,  VOLD,  VOLU,  MPLY,                  XXXXX, XXXXX, _____,  UNDS,   EQL, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER, LSFT, ENTCTL,   RALT_LGUI,MGKSPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

[_NAV] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,    F1,    F2,    F3,    F4, XXXXX,                  XXXXX, XXXXX,    UP, XXXXX, XXXXX,XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      ALTTB,    F5,    F6,    F7,    F9, XXXXX,                  XXXXX,  LEFT,  DOWN, RIGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX,    F9,   F10,   F11,   F12, XXXXX,                  XXXXX,  MNXT,  VOLD,  VOLU,  MPLY, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER, ENTCTL, LSFT,   RALT_LGUI,MGKSPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_NAV2] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,    F1,    F2,    F3,    F4, XXXXX,                  XXXXX, XXXXX,  PGUP, XXXXX, XXXXX, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      ALTTB,    F5,    F6,    F7,    F9, XXXXX,                  XXXXX,  HOME,  PGDN,   END, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX,    F9,   F10,   F11,   F12, XXXXX,                  XXXXX,  MNXT,  VOLD,  VOLU,  MPLY,XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER, ENTCTL, LSFT,   RALT_LGUI,MGKSPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_NAV3] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____, _____, _____,FORWRD, _____, _____,                   YANK, _____, _____, _____, PASTE, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  HOME,  PGDN,  PGUP,   END, _____,                  LEFT,   DOWN,    UP, RIGHT, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____,   DEL, _____, _____,BACKWRD,                 _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER, ENTCTL, LSFT,   RALT_LGUI,MGKSPC, RAISE \
                              //`--------------------'  `--------------------'
  ),


  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       LTOG,  LRST, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX,  LOCK, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       RMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER, ENTCTL, LSFT,   RALT_LGUI, SPC, RAISE \
                              //`--------------------'  `--------------------'
  )
};

/*
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
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
*/

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
/*
// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
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


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
    // set_timelog();
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
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case NAV:
      if (record->event.pressed) {
        layer_on(_NAV);
        update_tri_layer_RGB(_LOWER, _NAV, _NAV2);
      } else {
        layer_off(_NAV);
        update_tri_layer_RGB(_LOWER, _NAV, _NAV2);
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
  }
  return true;
}
*/


#endif

uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  state = update_tri_layer_state(state, _LOWER, _NAV, _NAV2);
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
    /*
  case COLEMAK:
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
    break;
  case GAME:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_GAME);
    }
    return false;
    break;
    */
  }
  return true;
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}
#endif

//tap dance for lower/lgui
int curr_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) { return SINGLE_TAP;}
        else { return SINGLE_HOLD;}
    }
    return 2;
}
void raltlgui_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = curr_dance(state);
    switch (td_state)
    {
    case SINGLE_TAP:
        /* code */
        register_code16(KC_LGUI);
        break;

    case SINGLE_HOLD:
        /* code */
        //layer_on(_LOWER);
        register_code16(KC_RALT);

    default:
        break;
    }
}
void raltlgui_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state)
    {
    case SINGLE_TAP:
        /* code */
        unregister_code16(KC_LGUI);
        break;

    case SINGLE_HOLD:
        /* code */
        //layer_off(_LOWER);
        unregister_code16(KC_RALT);
        break;

    default:
        break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [RALT_LGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, raltlgui_finished, raltlgui_reset)
};
