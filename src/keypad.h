//
// Created by zain on 5/28/18.
//

#ifndef CHIP8_KEYPAD_H
#define CHIP8_KEYPAD_H

#include <array>

class keypad {
private:
    std::array<bool, 16> _keys {};

public:
    keypad() = default;

    bool is_pressed(uint8_t const key) const;

    void press(uint8_t const key, bool const state);
};

#endif //CHIP8_KEYPAD_H
