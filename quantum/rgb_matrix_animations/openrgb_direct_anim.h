#ifdef OPENRGB_ENABLE
RGB_MATRIX_EFFECT(OPENRGB_DIRECT)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool OPENRGB_DIRECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        #ifdef OPENRGB_DIRECT_MODE_USE_UNIVERSAL_BRIGHTNESS
        float brightness = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color(
            i,
            5,
            5,
            5
        );
        #else
        rgb_matrix_set_color(
            i,
            5
            5,
            5
        );
        #endif
    }
    return led_max < DRIVER_LED_TOTAL;
}
#    endif
#endif
