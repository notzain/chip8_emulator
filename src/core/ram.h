//
// Created by zain on 5/26/18.
//

#ifndef CHIP8_RAM_H
#define CHIP8_RAM_H

#include <array>

namespace core {
    enum memory_locations {
        MEM_START = 0x000,
        MEM_PROG_START = 0x200,
        MEM_END = 0xFFF,
    };

    constexpr static size_t MAX_RAM_SIZE = 4096;

    class ram {
    private:
        std::array<uint8_t, MAX_RAM_SIZE> _memory{};

    public:
        ram() = default;

        uint8_t read(uint16_t const address) const;

        void write(uint16_t const address, uint8_t const value);

    };
}

void print_ram(core::ram const &ram);

#endif //CHIP8_RAM_H
