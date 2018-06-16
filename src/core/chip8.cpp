//
// Created by zain on 5/26/18.
//

#include "chip8.h"

#include <iostream>
#include <fstream>


uint8_t const fontset[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, //0
        0x20, 0x60, 0x20, 0x20, 0x70, //1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
        0x90, 0x90, 0xF0, 0x10, 0x10, //4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
        0xF0, 0x10, 0x20, 0x40, 0x40, //7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
        0xF0, 0x90, 0xF0, 0x90, 0x90, //A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
        0xF0, 0x80, 0x80, 0x80, 0xF0, //C
        0xE0, 0x90, 0x90, 0x90, 0xE0, //D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
        0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};

chip8::chip8() : _cpu(_ram, _gfx, _keypad) {

    for (uint8_t i = 0; i < 80; ++i) {
        _ram.write(i, fontset[i]);
    }
}

void chip8::load_game_from_file(char const *path, uint16_t pos) {

    std::ifstream file(path, std::ios::in | std::ios::binary);

    if (!file) {
        std::cerr << "Couldn't read file: " << path << "\n";
        return;
    }

    /*
     * TODO: Implement bound check.
     * Chip8's RAM is only 4096 bytes. If the ROM exceeds 4096 (minus 0x200), it will not fit in the RAM.
    */
    while (file.good()) {
        _ram.write(pos++, static_cast<uint8_t>(file.get()));
    }
}


void chip8::tick() {
    auto const pc = _cpu.prog_counter();
    uint16_t const opcode = _ram.read(pc) << 8 | _ram.read(pc + 1);

    auto const opmask = _cpu.decode(opcode);

    _cpu.execute(opmask, opcode);
}

bool chip8::pixel_at(uint8_t const x, uint8_t const y) {
    return _gfx.pixel_at(x, y);
}

void chip8::press_key(uint8_t const key) {
    _keypad.press(key, true);
}

bool chip8::to_draw() const { return _cpu.to_draw(); }

void chip8::has_drawn() { _cpu.has_drawn(); }

