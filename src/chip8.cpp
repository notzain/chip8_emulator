//
// Created by zain on 5/26/18.
//

#include "chip8.h"

#include <iostream>
#include <fstream>

chip8::chip8() : _cpu(_ram, _gfx) {}

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
    auto const pc = _cpu.fetch();
    uint16_t const opcode = _ram.read(pc) << 8 | _ram.read(pc + 1);

    auto const opmask = _cpu.decode(opcode);

    _cpu.execute(opmask, opcode);
}

