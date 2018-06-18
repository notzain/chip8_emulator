//
// Created by zain on 5/28/18.
//

#include <cassert>
#include "keypad.h"

namespace core {
    bool keypad::is_pressed(uint8_t const key) const {
        assert (key >= 0 && key < 16);

        return _keys[key];
    }

    void keypad::press(uint8_t const key, bool const state) {
        assert (key >= 0 && key < 16);

        _keys[key] = state;
    }
}
