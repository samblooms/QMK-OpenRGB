#pragma once

#include <color.h>
#include <raw_hid.h>

typedef enum commands_id 
{ 
    RAW_HID_EOM,
    RAW_HID_SUCCESS,
    RAW_HID_FAILURE,

    RAW_HID_SET_SINGLE_LED,
    RAW_HID_SET_LEDS,

    RAW_HID_SET_MODE_AND_SPEED,
    RAW_HID_SET_COLOR_MODE_AND_SPEED,

    RAW_HID_GET_QMK_VERSION,
    RAW_HID_GET_DEVICE_NAME,
    RAW_HID_GET_ZONES_COUNT,
    RAW_HID_GET_ZONE_NAME,
    RAW_HID_GET_ZONE_TYPE,
    RAW_HID_GET_ZONE_SIZE,
    RAW_HID_GET_LED_NAME,
    RAW_HID_GET_LED_MATRIX_COLUMNS,
    RAW_HID_GET_LED_MATRIX_ROWS,
    RAW_HID_GET_LED_VALUE_IN_MATRIX,
    RAW_HID_GET_LED_COLOR,

    RAW_HID_RGBMATRIX_SET_COLOR_ALL,
    RAW_HID_RGBMATRIX_SET_COLOR,

    RAW_HID_RGBMATRIX_TOGGLE,
    RAW_HID_RGBMATRIX_ENABLE,
    RAW_HID_RGBMATRIX_DISABLE,

    RAW_HID_RGBMATRIX_MODE,
    RAW_HID_RGBMATRIX_STEP,
    RAW_HID_RGBMATRIX_STEP_REVERSE,
    RAW_HID_RGBMATRIX_INCREASE_SPEED,
    RAW_HID_RGBMATRIX_DECREASE_SPEED,
    RAW_HID_RGBMATRIX_SET_SPEED,

    RAW_HID_RGBMATRIX_INCREASE_HUE,
    RAW_HID_RGBMATRIX_DECREASE_HUE,
    RAW_HID_RGBMATRIX_INCREASE_SAT,
    RAW_HID_RGBMATRIX_DECREASE_SAT,
    RAW_HID_RGBMATRIX_INCREASE_VAL,
    RAW_HID_RGBMATRIX_DECREASE_VAL,
    RAW_HID_RGBMATRIX_SET_HSV,

    RAW_HID_RGBMATRIX_GET_IS_ENABLED,
    RAW_HID_RGBMATRIX_GET_MODE,
    RAW_HID_RGBMATRIX_GET_HUE,
    RAW_HID_RGBMATRIX_GET_SAT,
    RAW_HID_RGBMATRIX_GET_VAL,
    RAW_HID_RGBMATRIX_GET_HSV,
    RAW_HID_RGBMATRIX_GET_SPEED,
    RAW_HID_RGBMATRIX_GET_SUSPEND_STATE,
} commands_id;

typedef enum eeprom_commands
{
    RAW_HID_EEPROM_SAVE,
    RAW_HID_EEPROM_DONT_SAVE
} eeprom_commands;

typedef enum zone_commands
{
    ZONE_TYPE_SINGLE,
    ZONE_TYPE_LINEAR,
    ZONE_TYPE_MATRIX
} zone_commands;

extern uint8_t raw_hid_buffer[RAW_EPSIZE];

void raw_hid_receive(uint8_t *data, uint8_t length);
void raw_hid_perform_send(void);

// Used by OpenRGB
void raw_hid_set_single_led(uint8_t *data);
void raw_hid_set_leds(uint8_t *data);
void raw_hid_set_mode_and_speed(uint8_t *data);
void raw_hid_set_color_mode_and_speed(uint8_t *data);

void raw_hid_get_qmk_version(void);
void raw_hid_get_device_name(void);
void raw_hid_get_zones_count(void);
void raw_hid_get_zone_name(uint8_t *data);
void raw_hid_get_zone_type(uint8_t *data);
void raw_hid_get_zone_size(uint8_t *data);
void raw_hid_get_led_name(uint8_t *data);
void raw_hid_get_led_matrix_columns(void);
void raw_hid_get_led_matrix_rows(void);
void raw_hid_get_led_value_in_matrix(uint8_t *data);
void raw_hid_get_led_color(uint8_t *data);

// Direct Operation
void raw_hid_rgbmatrix_set_color_all(uint8_t *data);
void raw_hid_rgbmatrix_set_color(uint8_t *data);

// Disable/Enable Effects
void raw_hid_rgbmatrix_toggle(uint8_t *data);
void raw_hid_rgbmatrix_enable(uint8_t *data);
void raw_hid_rgbmatrix_disable(uint8_t *data);

// Change Effect Mode
void raw_hid_rgbmatrix_mode(uint8_t *data);
void raw_hid_rgbmatrix_step(uint8_t *data);
void raw_hid_rgbmatrix_step_reverse(uint8_t *data);
void raw_hid_rgbmatrix_increase_speed(uint8_t *data);
void raw_hid_rgbmatrix_decrease_speed(uint8_t *data);
void raw_hid_rgbmatrix_set_speed(uint8_t *data);

// Change Color
void raw_hid_rgbmatrix_increase_hue(uint8_t *data);
void raw_hid_rgbmatrix_decrease_hue(uint8_t *data);
void raw_hid_rgbmatrix_increase_sat(uint8_t *data);
void raw_hid_rgbmatrix_decrease_sat(uint8_t *data);
void raw_hid_rgbmatrix_increase_val(uint8_t *data);
void raw_hid_rgbmatrix_decrease_val(uint8_t *data);
void raw_hid_rgbmatrix_set_hsv(uint8_t *data);

// Query Current Status
void raw_hid_rgbmatrix_get_is_enabled(void);
void raw_hid_rgbmatrix_get_mode(void);
void raw_hid_rgbmatrix_get_hue(void);
void raw_hid_rgbmatrix_get_sat(void);
void raw_hid_rgbmatrix_get_val(void);
void raw_hid_rgbmatrix_get_hsv(void);
void raw_hid_rgbmatrix_get_speed(void);
void raw_hid_rgbmatrix_get_suspend_state(void);