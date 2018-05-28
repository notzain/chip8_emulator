//
// Created by zain on 5/26/18.
//

#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include "cpu.h"
#include "ram.h"
#include "gfx.h"
#include "keypad.h"

class chip8 {
private:
    cpu _cpu;
    ram _ram;
    gfx _gfx;
    keypad _keypad;

public:
    chip8();

    void load_game_from_file(char const *path, uint16_t pos = MEM_PROG_START);

    void tick();

    bool pixel_at(uint8_t const x, uint8_t const y);
};

#endif //CHIP8_CHIP8_H
