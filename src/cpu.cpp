//
// Created by zain on 5/27/18.
//

#include <iostream>
#include "cpu.h"

const std::map<uint16_t, cpu::opcode_func> cpu::_instruction_set = {
};

cpu::cpu(chip8 &chip) : _chip8(chip) {}

void cpu::handle_opcode() {
    uint16_t const opcode = _chip8.read_from_mem(_pc_reg) << 8 | _chip8.read_from_mem(_pc_reg + 1);

    auto const op_mask = (opcode & 0xF000);
    auto const instr = _instruction_set.find(op_mask);

    if (instr != _instruction_set.end()) {
        (this->*_instruction_set.at(op_mask))(opcode);
    } else {
        std::cerr << "op not handled: " << std::hex << static_cast<int>(opcode) << '\n';
    }

    _pc_reg += 2;
}
