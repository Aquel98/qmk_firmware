/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "action_layer.h"
#include "color.h"
#include "keycodes.h"
#include "sendstring_swedish.h"
#include "rgb_matrix.h"

enum keymapLayers{
    LAYER_BASE = 0,
    LAYER_GAMING,
    LAYER_NUMPAD,
    LAYER_SYMBOLS,
    LAYER_NAVIGATION,
    LAYER_FUNCTION,
    LAYER_7,
    LAYER_8,
};

#define DEL_NAV LT(LAYER_NAVIGATION, KC_DEL)
#define BSP_SYM LT(LAYER_SYMBOLS, KC_BSPC)
#define SPC_NUM LT(LAYER_NUMPAD, KC_SPC)
#define ENT_FUN LT(LAYER_FUNCTION, KC_ENT)
#define GAMING TG(LAYER_GAMING)
#define ESC_L_7 LT(LAYER_7, KC_ESC)
#define TAB_L_8 LT(LAYER_8, KC_TAB)


#define LAYOUT_LAYER_BASE                                                                                                             \
       KC_TAB,    SE_Q,    SE_W,    SE_E,    SE_R,    SE_T,                         SE_Y,    SE_U,    SE_I,    SE_O,    SE_P, SE_ARNG,\
      CW_TOGG,    SE_A,    SE_S,    SE_D,    SE_F,    SE_G,                         SE_H,    SE_J,    SE_K,    SE_L, SE_ODIA, SE_ADIA,\
      KC_LSFT,    SE_Z,    SE_X,    SE_C,    SE_V,    SE_B,                         SE_N,    SE_M, SE_COMM,  SE_DOT, SE_SLSH,  GAMING,\
                                          ESC_L_7, DEL_NAV, SPC_NUM,    ENT_FUN, BSP_SYM, TAB_L_8

#define LAYOUT_LAYER_GAMING                                                                                                           \
       KC_TAB,    SE_Q,    SE_W,    SE_E,    SE_R,    SE_T,                         SE_Y,    SE_U,    SE_I,    SE_O,    SE_P, SE_ARNG,\
      KC_LCTL,    SE_A,    SE_S,    SE_D,    SE_F,    SE_G,                         SE_H,    SE_J,    SE_K,    SE_L, SE_ODIA, SE_ADIA,\
      KC_LSFT,    SE_Z,    SE_X,    SE_C,    SE_V,    SE_B,                         SE_N,    SE_M, SE_COMM,  SE_DOT, SE_SLSH,  GAMING,\
                                           KC_ESC, DEL_NAV,  KC_SPC,    ENT_FUN, BSP_SYM, SPC_NUM

#define LAYOUT_LAYER_SYMBOLS                                                                                                          \
      _______, SE_EXLM, SE_QUES, SE_LCBR, SE_RCBR, SE_PIPE,                      _______, SE_LABK, SE_RABK,  SE_DLR, SE_QUOT, SE_DQUO,\
      KC_LCTL, SE_AMPR, SE_HASH, SE_LPRN, SE_RPRN,   SE_AT,                      SE_BSLS, SE_SCLN, SE_COLN,  SE_EQL, SE_UNDS, _______,\
      KC_LSFT, SE_PERC, SE_CIRC, SE_LBRC, SE_RBRC, SE_TILD,                      SE_PLUS, SE_MINS, SE_ASTR, SE_SLSH, SE_ACUT, _______,\
                                          _______, _______, _______,    _______, _______, _______

#define LAYOUT_LAYER_NAVIGATION                                                                                                       \
      QK_BOOT, _______, _______, _______, _______, _______,                      _______, KC_HOME,   KC_UP,  KC_END, _______, _______,\
      _______, _______, _______, _______, _______, _______,                      _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,\
      _______, _______, _______, _______, _______, _______,                      _______,  KC_DEL, _______, _______, _______, _______,\
                                          _______, _______, _______,     KC_ENT, KC_BSPC,  KC_TAB

#define LAYOUT_LAYER_NUMPAD                                                                                                           \
      _______, _______, _______, _______, _______, _______,                      _______,    SE_7,    SE_8,    SE_9, _______, _______,\
      _______, _______, _______, _______, _______, _______,                      _______,    SE_4,    SE_5,    SE_6, _______, _______,\
      _______, _______, _______, _______, _______, _______,                      _______,    SE_1,    SE_2,    SE_3, _______, _______,\
                                          _______, _______, _______,    _______, _______,    SE_0

#define LAYOUT_LAYER_FUNCTION                                                                                                         \
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,\
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,\
      _______,  KC_F12, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,\
                                          _______, _______, _______,    _______, _______, _______



/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 12-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 24 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
 #define _HOME_ROW_MOD_GACS(                                                        \
    L00, L01, L02, L03, L04, L05, R06, R07, R08, R09, R10, R11,                     \
    L12, L13, L14, L15, L16, L17, R18, R19, R20, R21, R22, R23,                     \
    ...)                                                                            \
               L00,         L01,         L02,         L03,         L04,         L05,\
               R06,         R07,         R08,         R09,         R10,         R11,\
               L12, LGUI_T(L13), LALT_T(L14), LCTL_T(L15), LSFT_T(L16),  MEH_T(L17),\
        MEH_T(R18), RSFT_T(R19), RCTL_T(R20), LALT_T(R21),         R22,         R23,\
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_wrapper(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE)),
    [LAYER_GAMING] = LAYOUT_wrapper(LAYOUT_LAYER_GAMING),
    [LAYER_NUMPAD] = LAYOUT_wrapper(LAYOUT_LAYER_NUMPAD),
    [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
    [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
    [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', 'R',
                       '*', '*', '*',   '*', '*', '*'
    );

#ifdef RGB_MATRIX_ENABLE
rgb_t limitColor(hsv_t colorHsv)
{
    if (colorHsv.v > rgb_matrix_get_val())
    {
        colorHsv.v = rgb_matrix_get_val();
    }
    return hsv_to_rgb(colorHsv);
}

void setColor(int8_t i, rgb_t color)
{
    float underglowBrightnessFactor = 2.0;
    if(HAS_FLAGS(g_led_config.flags[i], 0x02))
    {
        rgb_matrix_set_color(i, color.r * underglowBrightnessFactor, color.g * underglowBrightnessFactor, color.b * underglowBrightnessFactor);
    }
    else
    {
        rgb_matrix_set_color(i, color.r, color.g, color.b);
    }
}


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    rgb_t colorLightGreen = limitColor(
        (hsv_t){100, 160, 25});
    rgb_t colorBlue = limitColor(
        (hsv_t){140, 200, 20});
    rgb_t colorYellow = limitColor(
        (hsv_t){35, 220, 20});
    rgb_t colorViolet = limitColor(
        (hsv_t){190, 150, 20});
    rgb_t colorOrange = limitColor((hsv_t){20, 180, 20});

    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case LAYER_FUNCTION:
                setColor(i, colorOrange);
                break;
            case LAYER_SYMBOLS:
                setColor(i, colorViolet);
                break;
            case LAYER_NAVIGATION:
                setColor(i, colorBlue);
                break;
            case LAYER_NUMPAD:
                setColor(i, colorYellow);
                break;
            case LAYER_BASE:
                setColor(i, colorLightGreen);
                break;
            default:
                break;
        }
    }
    return false;
}

#endif

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case SE_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case SE_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
