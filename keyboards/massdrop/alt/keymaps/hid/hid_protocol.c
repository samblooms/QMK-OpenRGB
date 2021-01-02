#include QMK_KEYBOARD_H
#include "hid_protocol.h"
#include "version.h"
#include "string.h"

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

uint8_t led_matrix_map[LED_MATRIX_COLUMNS][LED_MATRIX_ROWS] =
{
    { 100,  99,  98,  97,  96,  95,  NO_LED,  94,  NO_LED,  93,  92,  91,  90,  89,  88,  87,  86 },
    { 101,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  85 },
    { 102,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  84 },
    { 103,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  NO_LED,  42,  43,  83 },
    { 104,  44,  NO_LED,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  82 },
    { NO_LED,   58,  59,  60,  NO_LED,  NO_LED,  NO_LED,  61,  NO_LED,  NO_LED,  NO_LED,  62,  63,  64,  65,  66,  NO_LED },
    { 67,   68,  69,  70,  71,  72,  NO_LED,  73,  NO_LED,  74,  75,  76,  77,  78,  79,  80,  81 }
};

char led_names[DRIVER_LED_TOTAL][RAW_EPSIZE] =
{
    "Key: Escape", // 0
    "Key: 1", // 1
    "Key: 2", // 2
    "Key: 3", // 3
    "Key: 4", // 4
    "Key: 5", // 5
    "Key: 6", // 6
    "Key: 7", // 7
    "Key: 8", // 8
    "Key: 9", // 9
    "Key: 0", // 10
    "Key: -", // 11
    "Key: =", // 12
    "Key: Backspace", // 13
    "Key: Delete", // 14
    "Key: Tab", // 15
    "Key: Q", // 16
    "Key: W", // 17
    "Key: E", // 18
    "Key: R", // 19
    "Key: T", // 20
    "Key: Y", // 21
    "Key: U", // 22
    "Key: I", // 23
    "Key: O", // 24
    "Key: P", // 25
    "Key: [", // 26
    "Key: ]", // 27
    "Key: /", // 28
    "Key: Home", // 29
    "Key: Caps Lock", // 30
    "Key: A", // 31
    "Key: S", // 32
    "Key: D", // 33
    "Key: F", // 34
    "Key: G", // 35
    "Key: H", // 36
    "Key: J", // 37
    "Key: K", // 38
    "Key: L", // 39
    "Key: ;", // 40
    "Key: '", // 41
    "Key: Enter", // 42
    "Key: Page Up", // 43
    "Key: Left Shift", // 44
    "Key: Z", // 45
    "Key: X", // 46
    "Key: C", // 47
    "Key: V", // 48
    "Key: B", // 49
    "Key: N", // 50
    "Key: M", // 51
    "Key: ,", // 52
    "Key: .", // 53
    "Key: /", // 54
    "Key: Right Shift", // 55
    "Key: Up Arrow", // 56
    "Key: Page Down", // 57
    "Key: Left Control", // 58
    "Key: Left Windows", // 59
    "Key: Left Alt", // 60
    "Key: Space", // 61
    "Key: Right Alt", // 62
    "Key: Right Windows", // 63
    "Key: Left Arrow", // 64
    "Key: Down Arrow", // 65
    "Key: Right Arrow", // 66
    "Lightbar: 0", // 67
    "Lightbar: 1", // 68
    "Lightbar: 2", // 69
    "Lightbar: 3", // 70
    "Lightbar: 4", // 71
    "Lightbar: 5", // 72
    "Lightbar: 6", // 73
    "Lightbar: 7", // 74
    "Lightbar: 8", // 75
    "Lightbar: 9", // 76
    "Lightbar: 10", // 77
    "Lightbar: 11", // 78
    "Lightbar: 12", // 79
    "Lightbar: 13", // 80
    "Lightbar: 14", // 81
    "Lightbar: 15", // 82
    "Lightbar: 16", // 83
    "Lightbar: 17", // 84
    "Lightbar: 18", // 85
    "Lightbar: 19", // 86
    "Lightbar: 20", // 87
    "Lightbar: 21", // 88
    "Lightbar: 22", // 89
    "Lightbar: 23", // 90
    "Lightbar: 24", // 91
    "Lightbar: 25", // 92
    "Lightbar: 26", // 93
    "Lightbar: 27", // 94
    "Lightbar: 28", // 95
    "Lightbar: 29", // 96
    "Lightbar: 30", // 97
    "Lightbar: 31", // 98
    "Lightbar: 32", // 99
    "Lightbar: 33", // 100
    "Lightbar: 34", // 101
    "Lightbar: 35", // 102
    "Lightbar: 36", // 103
    "Lightbar: 37", // 104
};

void raw_hid_receive(uint8_t *data, uint8_t length)
 {
    switch (*data) 
    {
        case RAW_HID_SET_SINGLE_LED:
            raw_hid_set_single_led(data);
            break;
        case RAW_HID_SET_LEDS:
            raw_hid_set_leds(data);
            break;
        case RAW_HID_SET_MODE_AND_SPEED:
            raw_hid_set_mode_and_speed(data);
            break;
        case RAW_HID_SET_COLOR_MODE_AND_SPEED:
            raw_hid_set_color_mode_and_speed(data);
            break;
        case RAW_HID_GET_QMK_VERSION:
            raw_hid_get_qmk_version();
            break;
        case RAW_HID_GET_DEVICE_NAME:
            raw_hid_get_device_name();
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
        case RAW_HID_GET_LED_COLOR:
            raw_hid_get_led_color(data);
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
void raw_hid_perform_send(void) 
{
    raw_hid_send(raw_hid_buffer, RAW_EPSIZE);
}

// Used by OpenRGB
void raw_hid_set_single_led(uint8_t *data)
{
    const uint8_t led = data[1];
    const uint8_t r = data[2];
    const uint8_t g = data[3];
    const uint8_t b = data[4];

    if(led >= DRIVER_LED_TOTAL || r > 255 || g > 255 || b > 255)
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    g_rgb_matrix_hid_direct_mode_colors[led].r = r;
    g_rgb_matrix_hid_direct_mode_colors[led].g = g;
    g_rgb_matrix_hid_direct_mode_colors[led].b = b;
    
    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_set_leds(uint8_t *data)
{
    const uint8_t first_led = data[1];
    const uint8_t number_leds = data[2];

    if(first_led + number_leds > DRIVER_LED_TOTAL)
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }
 
    uint8_t i = 0;
    while (i < number_leds && first_led + i < DRIVER_LED_TOTAL && i * 3 + 5 < RAW_EPSIZE) 
    {
        const uint8_t r = data[3 + i * 3 + 0];
        const uint8_t g = data[3 + i * 3 + 1];
        const uint8_t b = data[3 + i * 3 + 2];

        if(r > 255 || g > 255 || b > 255)
        {
            raw_hid_buffer[1] = RAW_HID_FAILURE;
            raw_hid_buffer[2] = RAW_HID_EOM;
            continue;
        }

        g_rgb_matrix_hid_direct_mode_colors[first_led + i].r = r;
        g_rgb_matrix_hid_direct_mode_colors[first_led + i].g = g;
        g_rgb_matrix_hid_direct_mode_colors[first_led + i].b = b;
        i++;
    }

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_set_mode_and_speed(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;
    const uint8_t mode = data[2];
    const uint8_t speed = data[3];

    if (mode > RGB_MATRIX_EFFECT_MAX || speed > 255) 
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    if(should_save_to_eeprom) 
    {
        rgb_matrix_mode(mode);
        rgb_matrix_set_speed(speed);
    }
    else 
    {        
        rgb_matrix_mode_noeeprom(mode);
        rgb_matrix_set_speed_noeeprom(speed);
    }

    raw_hid_buffer[1] = RAW_HID_SUCCESS;
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_set_color_mode_and_speed(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;
    const uint8_t h = data[2];
    const uint8_t s = data[3];
    const uint8_t v = data[4];
    const uint8_t mode = data[5];
    const uint8_t speed = data[6];

    if (h > 255 || s > 255 || v > 255 || mode > RGB_MATRIX_EFFECT_MAX || speed > 255) 
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
void raw_hid_get_device_name(void)
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

    if(zone >= ZONES_COUNT)
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }
    
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

    if(zone >= ZONES_COUNT)
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    raw_hid_buffer[1] = zone_types[zone];
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_get_zone_size(uint8_t *data)
{
    const uint8_t zone = data[1];

    if(zone >= ZONES_COUNT)
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    raw_hid_buffer[1] = zone_sizes[zone];
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_get_led_name(uint8_t *data)
{  
    const uint8_t led = data[1];

    if(led >= DRIVER_LED_TOTAL)
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

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

    if(column >= LED_MATRIX_COLUMNS || row >= LED_MATRIX_ROWS)
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    raw_hid_buffer[1] = led_matrix_map[column][row];
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_get_led_color(uint8_t *data)
{
    const uint8_t led = data[1];

    if(led >= DRIVER_LED_TOTAL)
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    raw_hid_buffer[1] = g_rgb_matrix_hid_direct_mode_colors[led].r;
    raw_hid_buffer[2] = g_rgb_matrix_hid_direct_mode_colors[led].g;
    raw_hid_buffer[3] = g_rgb_matrix_hid_direct_mode_colors[led].b;
    raw_hid_buffer[4] = RAW_HID_EOM;
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
    const uint8_t led = data[1];
    const uint8_t r = data[2];
    const uint8_t g = data[3];
    const uint8_t b = data[4];

    if(led > DRIVER_LED_TOTAL || r > 255 || g > 255 || b > 255)
    {
        raw_hid_buffer[1] = RAW_HID_FAILURE;
        raw_hid_buffer[2] = RAW_HID_EOM;
        return;
    }

    rgb_matrix_set_color(led, r, g, b);

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
void raw_hid_rgbmatrix_get_is_enabled(void)
{
    raw_hid_buffer[1] = rgb_matrix_is_enabled();
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_get_mode(void)
{
    raw_hid_buffer[1] = rgb_matrix_get_mode();
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_get_hue(void)
{
    raw_hid_buffer[1] = rgb_matrix_get_hue();
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_get_sat(void)
{
    raw_hid_buffer[1] = rgb_matrix_get_sat();
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_get_val(void)
{
    raw_hid_buffer[1] = rgb_matrix_get_val();
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_get_hsv(void)
{
    HSV hsv_color = rgb_matrix_get_hsv();
    raw_hid_buffer[1] = hsv_color.h;
    raw_hid_buffer[2] = hsv_color.s;
    raw_hid_buffer[3] = hsv_color.v;
    raw_hid_buffer[4] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_get_speed(void)
{
    raw_hid_buffer[1] = rgb_matrix_get_speed();
    raw_hid_buffer[2] = RAW_HID_EOM;
}
void raw_hid_rgbmatrix_get_suspend_state(void)
{
    raw_hid_buffer[1] = rgb_matrix_get_suspend_state();
    raw_hid_buffer[2] = RAW_HID_EOM;
}
