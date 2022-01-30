#include "q1.h"


const matrix_row_t matrix_mask[] = {
    0b0111111111111101,
    0b0111111111111111,
    0b0111111111111111,
    0b0111111111111111,
    0b0111111111111111,
    0b0111111111111111,
};

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) { return false;}
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    return true;
}
