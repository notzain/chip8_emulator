//
// Created by zain on 5/26/18.
//

#include "chip8.h"

#include <iostream>
#include <fstream>

void chip8::load_game_from_file(char const *path, uint16_t pos) {

    std::ifstream file(path, std::ios::in | std::ios::binary);

    if (!file) {
        std::cerr << "Couldn't read file: " << path << "\n";
        return;
    }

    while (file.good()) {
        _ram.write(pos++, static_cast<uint8_t>(file.get()));
    }
}

uint8_t chip8::read_from_mem(uint16_t const address) const {
    return _ram.read(address);
}

void chip8::write_to_mem(uint16_t const address, uint8_t value) {
    _ram.write(address, value):
}

void chip8::tick() {
    _cpu.handle_opcode();
}
