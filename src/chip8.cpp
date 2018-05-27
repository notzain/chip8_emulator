//
// Created by zain on 5/26/18.
//

#include "chip8.h"

#include <iostream>
#include <fstream>

chip8::chip8() : _cpu(*this) {}

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

uint8_t chip8::read_from_mem(uint16_t const address) const {
    return _ram.read(address);
}

void chip8::write_to_mem(uint16_t const address, uint8_t value) {
    _ram.write(address, value);
}

void chip8::tick() {
    auto const pc = _cpu.fetch();
    uint16_t const opcode = read_from_mem(pc) << 8 | read_from_mem(pc + 1);

    auto const opmask = _cpu.decode(opcode);

    _cpu.execute(opmask, opcode);
}

