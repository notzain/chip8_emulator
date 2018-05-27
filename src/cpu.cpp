//
// Created by zain on 5/27/18.
//

#include "cpu.h"
#include "chip8.h"

#include <iostream>
#include <cassert>

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

cpu::cpu(ram &ram, gfx &gfx) : _ram(ram), _gfx(gfx) {}

uint16_t cpu::decode(uint16_t const opcode) const {
    return (opcode & 0xF000);
}

void cpu::execute(uint16_t const opmask, uint16_t const opcode) {
    auto const instr = _instruction_set.find(opmask);

    if (instr != _instruction_set.cend()) {
        (this->*(instr->second))(opcode);
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

    if (_v_reg[v_idx_x] == _v_reg[v_idx_y]) {
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
        }
        case 0x0001: {
            break;
        }
        case 0x0002: {
            break;
        }
        case 0x0003: {
            break;
        }
        case 0x0004: {
            break;
        }
        case 0x0005: {
            break;
        }
        case 0x0006: {
            break;
        }
        case 0x0007: {
            break;
        }
        case 0x000E: {
            break;
        }
    }

}

void cpu::op_9(uint16_t const opcode) {
    uint8_t const v_idx_x = (opcode & 0x0F00) >> 8;
    uint8_t const v_idx_y = (opcode & 0x00F0) >> 4;

    if (_v_reg[v_idx_x] != _v_reg[v_idx_y]) {
        std::cout << "Skip following instruction. \n";
    } else {

    }
}

void cpu::op_A(uint16_t const opcode) {
    _i_reg = (opcode & 0x0FFF);
    std::cout << "Store (NNN) in reg I: " << std::hex << static_cast<int>(_i_reg) << '\n';
}

void cpu::op_B(uint16_t const opcode) {
    uint16_t const address = (opcode + 0x0FFF) + _v_reg[0];

    std::cout << "Go to address: " << std::hex << static_cast<int>(address) << '\n';
}

void cpu::op_C(uint16_t const opcode) {
    uint8_t const v_idx = (opcode & 0x0F00) >> 8;

    uint8_t const random_val = /* should be random */ (3 & (opcode & 0x00FF));

    std::cerr << "op not handled: " << std::hex << static_cast<int>(opcode) << '\n';

}

void cpu::op_D(uint16_t const opcode) {

    /* DXYN
     * Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
     * Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
     *
     * The two registers passed to this instruction determine the x and y location of the sprite on the screen.
     * If the sprite is to be visible on the screen, the VX register must contain a value between 00 and 3F,
     * and the VY register must contain a value between 00 and 1F.
     *
     * When this instruction is processed by the interpreter, N bytes of data are read from memory starting from
     * the address stored in register I.
     * These bytes then represent the sprite data that will be used to draw the sprite on the screen.
     *
     * Therefore, the value of the I register determines which sprite is drawn,
     * and should always point to the memory address where the sprite data for the desired graphic is stored.
     *
     * The corresponding graphic on the screen will be eight pixels wide and N pixels high.
     */

    uint8_t const pos_x = _v_reg[(opcode & 0x0F00) >> 8];
    assert(pos_x >= 0x00 && pos_x < 0x3F);

    uint8_t const pos_y = _v_reg[(opcode & 0x00F0) >> 4];
    assert(pos_y >= 0x00 && pos_y < 0x1F);

    uint8_t const height = (opcode & 0x000F);

    _v_reg[0x000F] = 0x00;
    for (uint8_t y = 0; y < height; ++y) {
        // This byte contains 8 bits, each represent a pixel.
        auto const pixel_row = _ram.read(_i_reg + y);

        for (uint8_t x = 0; x < 8; ++x) {
            // Extract one byte from the pixel_row.
            auto const pixel = pixel_row & (0b10000000 >> x);

            // Should a pixel be drawn?
            if (pixel) {
                uint8_t const new_x = pos_x + x;
                uint8_t const new_y = pos_y + y;

                auto const current_pixel = _gfx.pixel_at(new_x, new_y);
                if (current_pixel == 1) {
                    _v_reg[0x000F] = 0x01;
                }

                const auto new_pixel = current_pixel ^ 0x01;
                _gfx.pixel_set(new_x, new_y, new_pixel);

                std::cout << "Setting pixel at (x, y) to (N): "
                          << "(" << static_cast<int>(new_x) << ", " << static_cast<int>(new_y) << ") "
                          << new_pixel << '\n';
            }
        }
    }
}

void cpu::op_E(uint16_t const opcode) {
    std::cerr << "op not handled: " << std::hex << static_cast<int>(opcode) << '\n';

}

void cpu::op_F(uint16_t const opcode) {
    std::cerr << "op not handled: " << std::hex << static_cast<int>(opcode) << '\n';

}

