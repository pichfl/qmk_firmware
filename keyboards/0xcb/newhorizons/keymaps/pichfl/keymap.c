// Copyright 2022 Conor Burns (@Conor-Burns)
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H
#include "keymap_german_mac_iso.h"
#include "lib/custom_keycodes.h"

enum layers {
    _DEFAULT = 0,
    _FN1     = 1,
    _FN2     = 2,
    _FN3     = 3,
};

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        DE_CIRC, KC_1,    KC_2   , KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, DE_ACUT, _______, KC_BSPC, KC_MUTE,
        KC_TAB ,          KC_Q   , KC_W,    KC_E,    KC_R,    KC_T,    DE_Z,    KC_U,    KC_I,    KC_O,    KC_P,    DE_UDIA, DE_PLUS, DE_HASH, KC_DEL ,
        KC_ESC ,          KC_A   , KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    DE_ODIA, DE_ADIA, KC_ENT ,          KC_PGUP,
        KC_LSFT, DE_LABK, DE_Y   , KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC , MO(_FN1),KC_SPC,                    KC_RGUI, KC_RALT, MO(_FN1), KC_LEFT, KC_DOWN,KC_RGHT
    ),
    [1] = LAYOUT_all(
        KC_ESC ,       KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,       KC_F11       , KC_F12       , _______      , RCTL(KC_BSPC), _______      ,
        RCTL(KC_TAB) ,          _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV,       KC_MPLY      , KC_MNXT      , _______      , _______      , KC_PWR       ,
        RCTL(KC_ESC) ,          _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______      , _______      , RCTL(KC_ENT) ,                _______      ,
        RCTL(KC_LSFT), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______      , RCTL(KC_RSFT),                RCTL(KC_UP)  , _______      ,
        _______,       _______, _______,                   MO(_FN3),_______, MO(_FN2),                  RCTL(KC_RGUI), RCTL(KC_RALT), _______      , RCTL(KC_LEFT), RCTL(KC_DOWN), RCTL(KC_RGHT)
    ),
    [2] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, PM_TGGL, PM_WORK, PM_BRK , _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                   _______, _______, _______,                   _______, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT_all(
        DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                   _______, _______, _______,                   _______, _______, _______, _______, _______, _______
    )
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_DEFAULT] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FN1]     = {ENCODER_CCW_CW(KC_F15, KC_F16)},
    [_FN2]     = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [_FN3]     = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
};
#endif
