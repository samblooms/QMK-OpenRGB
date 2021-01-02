#include QMK_KEYBOARD_H
#include "hid_protocol.h"
#include "string.h"
#include "version.h"

uint8_t raw_hid_buffer[RAW_EPSIZE];

char zone_names[ZONES_COUNT][RAW_EPSIZE] =
{ 
    "Keyboard"
};

uint8_t zone_types[ZONES_COUNT] =
{ 
    ZONE_TYPE_MATRIX
};

uint8_t zone_sizes[ZONES_COUNT] =
{ 
    105
};

char led_names[DRIVER_LED_TOTAL][RAW_EPSIZE] =
{
   "Key: Escape", // 0
    "Key: F1", // 1
    "Key: F2", // 2
    "Key: F3", // 3
    "Key: F4", // 4
    "Key: F5", // 5
    "Key: F6", // 6
    "Key: F7", // 7
    "Key: F8", // 8
    "Key: F9", // 9
    "Key: F10", // 10
    "Key: F11", // 11
    "Key: F12", // 12
    "Key: Print Screen", // 13
    "Key: Scroll Lock", // 14
    "Key: Pause/Break", // 15
    "Key: `", // 16
    "Key: 1", // 17
    "Key: 2", // 18
    "Key: 3", // 19
    "Key: 4", // 20
    "Key: 5", // 21
    "Key: 6", // 22
    "Key: 7", // 23
    "Key: 8", // 24
    "Key: 9", // 25
    "Key: 0", // 26
    "Key: -", // 27
    "Key: =", // 28
    "Key: Backspace", // 29
    "Key: Insert", // 30
    "Key: Home", // 31
    "Key: Page Up", // 32
    "Key: Tab", // 33
    "Key: Q", // 34
    "Key: W", // 35
    "Key: E", // 36
    "Key: R", // 37
    "Key: T", // 38
    "Key: Y", // 39
    "Key: U", // 40
    "Key: I", // 41
    "Key: O", // 42
    "Key: P", // 43
    "Key: [", // 44
    "Key: ]", // 45
    "Key: /", // 46
    "Key: Delete", // 47
    "Key: End", // 48
    "Key: Page Down", // 49
    "Key: Caps Lock", // 50
    "Key: A", // 51
    "Key: S", // 52
    "Key: D", // 53
    "Key: F", // 54
    "Key: G", // 55
    "Key: H", // 56
    "Key: J", // 57
    "Key: K", // 58
    "Key: L", // 59
    "Key: ;", // 60
    "Key: '", // 61
    "Key: Enter", // 62
    "Key: Left Shift", // 63
    "Key: Z", // 64
    "Key: X", // 65
    "Key: C", // 66
    "Key: V", // 67
    "Key: B", // 68
    "Key: N", // 69
    "Key: M", // 70
    "Key: ,", // 71
    "Key: .", // 72
    "Key: /", // 73
    "Key: Right Shift", // 74
    "Key: Up Arrow", // 75
    "Key: Left Control", // 76
    "Key: Left Windows", // 77
    "Key: Left Alt", // 78
    "Key: Space", // 79
    "Key: Right Alt", // 80
    "Key: Right Fn", // 81
    "Key: Right Windows", // 82
    "Key: Right Control", // 83
    "Key: Left Arrow", // 84
    "Key: Down Arrow", // 85
    "Key: Right Arrow", // 86
    "Lightbar: 0", // 87
    "Lightbar: 1", // 88
    "Lightbar: 2", // 89
    "Lightbar: 3", // 90
    "Lightbar: 4", // 91
    "Lightbar: 5", // 92
    "Lightbar: 6", // 93
    "Lightbar: 7", // 94
    "Lightbar: 8", // 95
    "Lightbar: 9", // 96
    "Lightbar: 10", // 97
    "Lightbar: 11", // 98
    "Lightbar: 12", // 99
    "Lightbar: 13", // 100
    "Lightbar: 14", // 101
    "Lightbar: 15", // 102
    "Lightbar: 16", // 103
    "Lightbar: 17", // 104
    "Lightbar: 18", // 105
    "Lightbar: 19", // 106
    "Lightbar: 20", // 107
    "Lightbar: 21", // 108
    "Lightbar: 22", // 109
    "Lightbar: 23", // 110
    "Lightbar: 24", // 111
    "Lightbar: 25", // 112
    "Lightbar: 26", // 113
    "Lightbar: 27", // 114
    "Lightbar: 28", // 115
    "Lightbar: 29", // 116
    "Lightbar: 30", // 117
    "Lightbar: 31", // 118
};

#define NA 0xFFFFFFFF

static unsigned int matrix_map_ctrl[6][17] =
{
    { 0,   NA,  1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  15 },
    { 16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32 },
    { 33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49 },
    { 50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  NA,  NA,  NA,  NA },
    { 63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  NA,  NA,  NA,  72,  NA },
    { 76,  77,  78,  NA,  NA,  NA,  79,  NA,  NA,  NA,  80,  81,  82,  83,  84,  85,  86 }
};

void raw_hid_perform_send(void) 
{
    raw_hid_send(raw_hid_buffer, RAW_EPSIZE);
}
void raw_hid_receive(uint8_t *data, uint8_t length)
 {
    switch (*data) 
    {
        case RAW_HID_RGBMATRIX_SET_COLOR_AND_MODE_AND_SPEED:
            raw_hid_rgbmatrix_set_color_and_mode_and_speed(data);
            break;
        case RAW_HID_RGBMATRIX_SET_SINGLE_LED:
            raw_hid_rgbmatrix_set_single_led(data);
            break;
        case RAW_HID_RGBMATRIX_SET_LEDS:
            raw_hid_rgbmatrix_set_leds(data);
            break;
        case RAW_HID_RGBMATRIX_SET_COLOR_ALL:
            raw_hid_rgbmatrix_set_color_all(data);
            break;
        case RAW_HID_RGBMATRIX_SET_COLOR:
            raw_hid_rgbmatrix_set_color(data);
            break;
        case RAW_HID_RGBMATRIX_TOGGLE:
            raw_hid_rgbmatrix_toggle(data);
            break;
        case RAW_HID_RGBMATRIX_ENABLE:
            raw_hid_rgbmatrix_enable(data);
            break;
        case RAW_HID_RGBMATRIX_DISABLE:
            raw_hid_rgbmatrix_disable(data);
            break;
        case RAW_HID_RGBMATRIX_MODE:
            raw_hid_rgbmatrix_mode(data);
            break;
        case RAW_HID_RGBMATRIX_STEP:
            raw_hid_rgbmatrix_step(data);
            break;
        case RAW_HID_RGBMATRIX_STEP_REVERSE:
            raw_hid_rgbmatrix_step_reverse(data);
            break;
        case RAW_HID_RGBMATRIX_INCREASE_SPEED:
            raw_hid_rgbmatrix_increase_speed(data);
            break;
        case RAW_HID_RGBMATRIX_DECREASE_SPEED:
            raw_hid_rgbmatrix_decrease_speed(data);
            break;
        case RAW_HID_RGBMATRIX_SET_SPEED:
            raw_hid_rgbmatrix_set_speed(data);
            break;
        case RAW_HID_RGBMATRIX_INCREASE_HUE:
            raw_hid_rgbmatrix_increase_hue(data);
            break;
        case RAW_HID_RGBMATRIX_DECREASE_HUE:
            raw_hid_rgbmatrix_decrease_hue(data);
            break;
        case RAW_HID_RGBMATRIX_INCREASE_SAT:
            raw_hid_rgbmatrix_increase_sat(data);
            break;
        case RAW_HID_RGBMATRIX_DECREASE_SAT:
            raw_hid_rgbmatrix_decrease_sat(data);
            break;
        case RAW_HID_RGBMATRIX_INCREASE_VAL:
            raw_hid_rgbmatrix_increase_val(data);
            break;
        case RAW_HID_RGBMATRIX_DECREASE_VAL:
            raw_hid_rgbmatrix_decrease_val(data);
            break;
        case RAW_HID_RGBMATRIX_SET_HSV:
            raw_hid_rgbmatrix_set_hsv(data);
            break;
        case RAW_HID_GET_QMK_VERSION:
            raw_hid_get_qmk_version();
            break;
        case RAW_HID_GET_NAME:
            raw_hid_get_name();
            break;
        case RAW_HID_GET_ZONES_COUNT:
            raw_hid_get_zones_count();
            break;
        case RAW_HID_GET_ZONE_NAME:
            raw_hid_get_zone_name(data);
            break;
        case RAW_HID_GET_ZONE_TYPE:
            raw_hid_get_zone_type(data);
            break;
        case RAW_HID_GET_ZONE_SIZE:
            raw_hid_get_zone_size(data);
            break;
        case RAW_HID_GET_LED_NAME:
            raw_hid_get_led_name(data);
            break;
        case RAW_HID_GET_LED_MATRIX_COLUMNS:
            raw_hid_get_led_matrix_columns();
            break;
        case RAW_HID_GET_LED_MATRIX_ROWS:
            raw_hid_get_led_matrix_rows();
            break;
        case RAW_HID_GET_LED_VALUE_IN_MATRIX:
            raw_hid_get_led_value_in_matrix(data);
            break;
        case RAW_HID_RGBMATRIX_GET_IS_ENABLED:
            raw_hid_rgbmatrix_get_is_enabled();
            break;
        case RAW_HID_RGBMATRIX_GET_MODE:
            raw_hid_rgbmatrix_get_mode();
            break;
        case RAW_HID_RGBMATRIX_GET_HUE:
            raw_hid_rgbmatrix_get_hue();
            break;
        case RAW_HID_RGBMATRIX_GET_SAT:
            raw_hid_rgbmatrix_get_sat();
            break;
        case RAW_HID_RGBMATRIX_GET_VAL:
            raw_hid_rgbmatrix_get_val();
            break;
        case RAW_HID_RGBMATRIX_GET_HSV:
            raw_hid_rgbmatrix_get_hsv();
            break;
        case RAW_HID_RGBMATRIX_GET_SPEED:
            raw_hid_rgbmatrix_get_speed();
            break;
        case RAW_HID_RGBMATRIX_GET_SUSPEND_STATE:
            raw_hid_rgbmatrix_get_suspend_state();
            break;   
    }

    raw_hid_perform_send();
}

// Used by OpenRGB
void raw_hid_rgbmatrix_set_color_and_mode_and_speed(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;
    const uint8_t h = data[2];
    const uint8_t s = data[3];
    const uint8_t v = data[4];
    const uint8_t mode = data[5];
    const uint8_t speed = data[6];

    if (mode >= RGB_MATRIX_EFFECT_MAX || speed > 255) 
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    if(should_save_to_eeprom) 
    {
        rgb_matrix_sethsv(h, s, v);
        rgb_matrix_mode(mode);
        rgb_matrix_set_speed(speed);
    }
    else 
    {
        rgb_matrix_sethsv_noeeprom(h, s, v);
        rgb_matrix_mode_noeeprom(mode);
        rgb_matrix_set_speed_noeeprom(speed);
    }

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_set_single_led(uint8_t *data)
{
    const uint8_t led = data[1];

    if (led >= DRIVER_LED_TOTAL) 
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = DRIVER_LED_TOTAL;
        raw_hid_buffer[3] = RAW_HID_EOM;
        return;
    }

    //rgb_matrix_led_state[led].r = data[2];
    //rgb_matrix_led_state[led].g = data[3];
    //rgb_matrix_led_state[led].b = data[4];
    
    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_set_leds(uint8_t *data)
{
    const uint8_t first_led = data[1];
    const uint8_t number_leds = data[2];
 
    uint8_t i = 0;
    while (i < number_leds && first_led + i < DRIVER_LED_TOTAL && i * 3 + 5 < RAW_EPSIZE) 
    {
        rgb_matrix_led_state[first_led + i].r = data[3 + i * 3 + 0];
        rgb_matrix_led_state[first_led + i].g = data[3 + i * 3 + 1];
        rgb_matrix_led_state[first_led + i].b = data[3 + i * 3 + 2];
        i++;
    }

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = i;
    raw_hid_buffer[3] = RAW_HID_EOM;
}

// Direct Operation
void raw_hid_rgbmatrix_set_color_all(uint8_t *data)
{
    const uint8_t r = data[1];
    const uint8_t g = data[2];
    const uint8_t b = data[3];

    if(r > 255 || g > 255 || b > 255)
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    rgb_matrix_set_color_all(r, g, b);

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_set_color(uint8_t *data)
{
    const uint8_t i = data[1];
    const uint8_t r = data[2];
    const uint8_t g = data[3];
    const uint8_t b = data[4];

    if(i > DRIVER_LED_TOTAL || r > 255 || g > 255 || b > 255)
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    rgb_matrix_set_color(i, r, g, b);

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}

// Disable/Enable Effects
void raw_hid_rgbmatrix_toggle(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_toggle();
    else rgb_matrix_toggle_noeeprom();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_enable(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_enable();
    else rgb_matrix_enable_noeeprom();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_disable(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_disable();
    else rgb_matrix_disable();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}

// Change Effect Mode
void raw_hid_rgbmatrix_mode(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;
    const uint8_t mode = data[2];
    if (mode >= RGB_MATRIX_EFFECT_MAX) 
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    if(should_save_to_eeprom) rgb_matrix_mode(mode);
    else rgb_matrix_mode_noeeprom(mode);

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_step(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_step();
    else rgb_matrix_step_noeeprom();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_step_reverse(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_step_reverse();
    else rgb_matrix_step_reverse_noeeprom();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_increase_speed(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_increase_speed();
    else rgb_matrix_increase_speed_noeeprom();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_decrease_speed(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_decrease_speed();
    else rgb_matrix_decrease_speed_noeeprom();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_set_speed(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;
    const uint8_t speed = data[2];
    if (speed > 255) 
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    if (should_save_to_eeprom) rgb_matrix_set_speed(speed);
    else rgb_matrix_set_speed_noeeprom(speed);

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}

// Change Color
void raw_hid_rgbmatrix_increase_hue(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_increase_hue();
    else rgb_matrix_increase_hue_noeeprom();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_decrease_hue(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_decrease_hue();
    else rgb_matrix_decrease_hue_noeeprom();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_increase_sat(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_increase_sat();
    else rgb_matrix_increase_sat_noeeprom();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_decrease_sat(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_decrease_sat();
    else rgb_matrix_decrease_sat_noeeprom();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_increase_val(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_increase_val();
    else rgb_matrix_increase_val_noeeprom();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_decrease_val(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    if (should_save_to_eeprom) rgb_matrix_decrease_val();
    else rgb_matrix_decrease_val_noeeprom();

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_set_hsv(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;

    const uint8_t h = data[2];
    const uint8_t s = data[3];
    const uint8_t v = data[4];

    if(h > 255 || s > 255 || v > 255)
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    if (should_save_to_eeprom) rgb_matrix_sethsv(h, s, v);
    else rgb_matrix_sethsv_noeeprom(h, s, v);

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}

// Query Current Status
void raw_hid_get_qmk_version(void)
{
    const char *qmk_version = QMK_VERSION;
    uint8_t i = 0;
    while (qmk_version[i] != 0 && i + 2 < RAW_EPSIZE) 
    {
        raw_hid_buffer[i + 1] = qmk_version[i];
        i++;
    }
    raw_hid_buffer[i + 1] = RAW_HID_EOM;
}
void raw_hid_get_name(void)
{
    char *name = malloc(strlen(MANUFACTURER) + strlen(" ") + strlen(PRODUCT) + 1); 
    strcpy(name, MANUFACTURER);
    strcat(name, " ");
    strcat(name, PRODUCT);

    uint8_t i = 0;
    while (name[i] != 0 && i + 2 < RAW_EPSIZE) 
    {
        raw_hid_buffer[i + 1] = name[i];
        i++;
    }
    raw_hid_buffer[i + 1] = RAW_HID_EOM;
}
void raw_hid_get_zones_count(void)
{
    raw_hid_buffer[1] = ZONES_COUNT;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_get_zone_name(uint8_t *data)
{  
    const uint8_t zone = data[1];

    const char *zone_name = zone_names[zone];
    uint8_t i = 0;
    while (zone_name[i] != 0 && i + 2 < RAW_EPSIZE) 
    {
        raw_hid_buffer[i + 1] = zone_name[i];
        i++;
    }
    raw_hid_buffer[i + 1] = RAW_HID_EOM;
}
void raw_hid_get_zone_type(uint8_t *data)
{
    const uint8_t zone = data[1];
    raw_hid_buffer[1] = zone_types[zone];
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_get_zone_size(uint8_t *data)
{
    const uint8_t zone = data[1];
    raw_hid_buffer[1] = zone_sizes[zone];
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_get_led_name(uint8_t *data)
{  
    const uint8_t led = data[1];

    const char *led_name = led_names[led];
    uint8_t i = 0;
    while (led_name[i] != 0 && i + 2 < RAW_EPSIZE) 
    {
        raw_hid_buffer[i + 1] = led_name[i];
        i++;
    }
    raw_hid_buffer[i + 1] = RAW_HID_EOM;
}
void raw_hid_get_led_matrix_columns(void)
{
    raw_hid_buffer[1] = LED_MATRIX_COLUMNS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_get_led_matrix_rows(void)
{
    raw_hid_buffer[1] = LED_MATRIX_ROWS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_get_led_value_in_matrix(uint8_t *data)
{
    const uint8_t column = data[1];
    const uint8_t row = data[2];

    raw_hid_buffer[1] = matrix_map[column][row];
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_get_is_enabled(void)
{

}
void raw_hid_rgbmatrix_get_mode(void)
{

}
void raw_hid_rgbmatrix_get_hue(void)
{

}
void raw_hid_rgbmatrix_get_sat(void)
{

}
void raw_hid_rgbmatrix_get_val(void)
{

}
void raw_hid_rgbmatrix_get_hsv(void)
{

}
void raw_hid_rgbmatrix_get_speed(void)
{

}
void raw_hid_rgbmatrix_get_suspend_state(void)
{

}
