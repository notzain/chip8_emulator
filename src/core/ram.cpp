//
// Created by zain on 5/26/18.
//

#include "ram.h"

#include <cassert>
#include <iostream>

namespace core {
    uint8_t ram::read(uint16_t const address) const {
        assert(address >= 0 && address < 4096);

        return _memory[address];
    }

    void ram::write(uint16_t const address, uint8_t const value) {
        assert(address >= 0 && address < 4096);

        _memory[address] = value;
    }
}

void print_ram(core::ram const &ram) {
    for (int i = 0; i < core::MAX_RAM_SIZE; i += 8) {
        for (int j = 0; j < 8; ++j) {
            std::cout << std::hex << static_cast<int>(ram.read(i + j)) << " ";
        }
        std::cout << '\n';
    }
}
