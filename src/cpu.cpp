//
// Created by zain on 5/27/18.
//

#include "cpu.h"
#include "chip8.h"

#include <iostream>

const std::map<uint16_t, cpu::opcode_func> cpu::_instruction_set = {
        {0x0000, &cpu::op_0},
        {0x1000, &cpu::op_1},
        {0x2000, &cpu::op_2},
        {0x3000, &cpu::op_3},
        {0x4000, &cpu::op_4},
        {0x5000, &cpu::op_5},
        {0x6000, &cpu::op_6},
        {0x7000, &cpu::op_7},
        {0x8000, &cpu::op_8},
        {0x9000, &cpu::op_9},
        {0xA000, &cpu::op_A},
        {0xB000, &cpu::op_B},
        {0xC000, &cpu::op_C},
        {0xD000, &cpu::op_D},
        {0xE000, &cpu::op_E},
        {0xF000, &cpu::op_F},
};

cpu::cpu(chip8 &chip) : _chip8(chip) {}

uint16_t cpu::decode(uint16_t const opcode) const {
    //uint16_t const opcode = _chip8.read_from_mem(_pc_reg) << 8 | _chip8.read_from_mem(_pc_reg + 1);

    return (opcode & 0xF000);
}

void cpu::execute(uint16_t const opmask, uint16_t const opcode) {
    auto const instr = _instruction_set.find(opmask);

    if (instr != _instruction_set.end()) {
        (this->*_instruction_set.at(opmask))(opcode);
    } else {
        std::cerr << "Op not found: " << std::hex
                  << static_cast<int>(opmask) << " "
                  << static_cast<int>(opcode) << '\n';
    }

    _pc_reg += 2;
}

void cpu::op_0(uint16_t const opcode) {
    if (opcode == 0x00E0) {
        std::cout << "Clear screen. \n";
        return;
    } else if (opcode == 0x00EE) {
        std::cout << "Return from subroutine. \n";
        return;
    }

    uint16_t const op_masked = (opcode & 0x0FFF);
    std::cout << "Exec ML subroutine: " << std::hex << static_cast<int>(op_masked) << '\n';
}

void cpu::op_1(uint16_t const opcode) {
    uint16_t const op_masked = (opcode & 0x0FFF);
    std::cout << "Jump to address: " << std::hex << static_cast<int>(op_masked) << '\n';
}

void cpu::op_2(uint16_t const opcode) {
    uint16_t const op_masked = (opcode & 0x0FFF);
    std::cout << "Exec at address: " << std::hex << static_cast<int>(op_masked) << '\n';
}

void cpu::op_3(uint16_t const opcode) {
    uint8_t const v_idx = (opcode & 0x0F00) >> 8;
    uint8_t const compare_val = (opcode && 0x00FF);

    if (_v_reg[v_idx] == compare_val) {
        std::cout << "Skip following instruction. \n";
    } else {

    }
}

void cpu::op_4(uint16_t const opcode) {
    uint8_t const v_idx = (opcode & 0x0F00) >> 8;
    uint8_t const compare_val = (opcode && 0x00FF);

    if (_v_reg[v_idx] != compare_val) {
        std::cout << "Skip following instruction. \n";
    } else {

    }
}

void cpu::op_5(uint16_t const opcode) {
    uint8_t const v_idx_x = (opcode & 0x0F00) >> 8;
    uint8_t const v_idx_y = (opcode & 0x00F0) >> 4;

    if (_v_reg[v_idx_x] != _v_reg[v_idx_y]) {
        std::cout << "Skip following instruction. \n";
    } else {

    }
}

void cpu::op_6(uint16_t const opcode) {
    uint8_t const v_idx = (opcode & 0x0F00) >> 8;
    uint8_t const val = (opcode & 0x00FF);

    std::cout << "Store (NN) in (X): " << std::hex
              << static_cast<int>(val) << " " << static_cast<int>(v_idx) << '\n';
}

void cpu::op_7(uint16_t const opcode) {
    uint8_t const v_idx = (opcode & 0x0F00) >> 8;
    uint8_t const val = (opcode & 0x00FF);

    std::cout << "Add (NN) to (X): " << std::hex
              << static_cast<int>(val) << " " << static_cast<int>(v_idx) << '\n';
}

void cpu::op_8(uint16_t const opcode) {
    uint8_t const v_idx_x = (opcode & 0x0F00) >> 8;
    uint8_t const v_idx_y = (opcode & 0x00F0) >> 4;

    switch (opcode & 0x000F) {
        case 0x0000: {
            break;
        },
        case 0x0001: {
            break;
        },
        case 0x0002: {
            break;
        },
        case 0x0003: {
            break;
        },
        case 0x0004: {
            break;
        },
        case 0x0005: {
            break;
        },
        case 0x0006: {
            break;
        },
        case 0x0007: {
            break;
        },
        case 0x000E: {
            break;
        },
    }

}

void cpu::op_9(uint16_t const opcode) {
    std::cerr << "op not handled: " << std::hex << static_cast<int>(opcode) << '\n';

}

void cpu::op_A(uint16_t const opcode) {
    std::cerr << "op not handled: " << std::hex << static_cast<int>(opcode) << '\n';

}

void cpu::op_B(uint16_t const opcode) {
    std::cerr << "op not handled: " << std::hex << static_cast<int>(opcode) << '\n';

}

void cpu::op_C(uint16_t const opcode) {
    std::cerr << "op not handled: " << std::hex << static_cast<int>(opcode) << '\n';

}

void cpu::op_D(uint16_t const opcode) {
    std::cerr << "op not handled: " << std::hex << static_cast<int>(opcode) << '\n';

}

void cpu::op_E(uint16_t const opcode) {
    std::cerr << "op not handled: " << std::hex << static_cast<int>(opcode) << '\n';

}

void cpu::op_F(uint16_t const opcode) {
    std::cerr << "op not handled: " << std::hex << static_cast<int>(opcode) << '\n';

}
