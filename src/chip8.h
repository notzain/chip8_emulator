//
// Created by zain on 5/26/18.
//

#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include "ram.h"
#include "cpu.h"

class chip8 {
private:
    ram _ram;
    cpu _cpu;

public:
    chip8();

    void load_game_from_file(char const *path, uint16_t pos = MEM_PROG_START);

    uint8_t read_from_mem(uint16_t const address) const;

    void write_to_mem(uint16_t const address, uint8_t value);

    void tick();
};

#endif //CHIP8_CHIP8_H
