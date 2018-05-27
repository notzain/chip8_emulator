//
// Created by zain on 5/28/18.
//

#include "gfx.h"

bool gfx::pixel_at(uint8_t const x, uint8_t const y) const {
    return _screen[x][y];
}

void gfx::pixel_set(uint8_t const x, uint8_t const y, bool is_set) {
    _screen[x][y] = is_set;
}
