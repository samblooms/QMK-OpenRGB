/* Copyright 2021 Sleepdealer
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

// 00 Functionality
enum custom_keycodes {
    MC_00 = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MC_00:
            if (record->event.pressed) {
                SEND_STRING("00");
            }
            break;
    }
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        KC_MUTE,         KC_PGUP, KC_PGDN,
		TG(1),  KC_PSLS, KC_PAST, KC_PMNS,
		KC_P7,  KC_P8,   KC_P9,   KC_PPLS,  KC_PPLS,
		KC_P4,  KC_P5,   KC_P6,   KC_PIPE,
		KC_P1,  KC_P2,   KC_P3,   KC_ENTER, KC_ENTER,
		KC_P0,  MC_00,   KC_PDOT, KC_PDOT,   
                KC_P0),
    LAYOUT(
        KC_TRNS,          RGB_HUI, RGB_VAI,
		TG(1),   RGB_TOG, RGB_HUD, RGB_VAD,
		KC_PGUP, KC_UP,   KC_PGDN, RGB_MOD,  RGB_MOD,
		KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,
		KC_INS,  KC_HOME, KC_END,  RGB_RMOD, RGB_RMOD,
		KC_ESC,  KC_TRNS, KC_DEL,  KC_TRNS, 
        KC_ESC)
};
