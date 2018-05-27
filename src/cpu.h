//
// Created by zain on 5/27/18.
//

#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include <array>
#include <map>
#include "chip8.h"

class cpu {
private:
    chip8 &_chip8;
    /*
     * Chip8 has 15 general purpose registers: V0, V1 .. VE (15)
     * VF (16) is used for the 'carry flag'
     */
    std::array<uint8_t, 16> _v_reg;
    uint16_t _idx_reg;
    uint16_t _pc_reg;

    using opcode_func = void (cpu::*)(uint16_t const);
    static const std::map<uint16_t, opcode_func> _instruction_set;

public:
    explicit cpu(chip8 &chip);

    void handle_opcode();
};

#endif //CHIP8_CPU_H
