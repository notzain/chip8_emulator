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

cpu::cpu(ram &ram, gfx &gfx, keypad &keypad) : _ram(ram), _gfx(gfx), _keypad(keypad) {}

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

    if (_delay_timer > 0) --_delay_timer;
    if (_sound_timer > 0) --_sound_timer;
}

void cpu::op_0(uint16_t const opcode) {

    // 00E0	Clear the screen
    if (opcode == 0x00E0) {
        _gfx.clear();
        std::cout << "Clear screen. \n";
        _pc_reg += 2;
    }
        // 00EE	Return from a subroutine
    else if (opcode == 0x00EE) {
        std::cout << "Return from subroutine. \n";
        _pc_reg = _stack[--_stack_idx];
        _pc_reg += 2;
    }
        // 0NNN	Execute machine language subroutine at address NNN
    else {
        uint16_t const address = (opcode & 0x0FFF);
        std::cout << "Exec ML subroutine: " << std::hex << static_cast<int>(address) << '\n';
    }
}

void cpu::op_1(uint16_t const opcode) {
    // 1NNN	Jump to address NNN
    uint16_t const address = (opcode & 0x0FFF);
    _pc_reg = address;

    std::cout << "Jump to address: " << std::hex << static_cast<int>(address) << '\n';
}

void cpu::op_2(uint16_t const opcode) {
    // 2NNN	Execute subroutine starting at address NNN
    uint16_t const address = (opcode & 0x0FFF);

    _stack[_stack_idx++] = _pc_reg;

    _pc_reg = address;
    std::cout << "Exec at address: " << std::hex << static_cast<int>(address) << '\n';
}

void cpu::op_3(uint16_t const opcode) {
    // 3XNN	Skip the following instruction if the value of register VX equals NN
    uint8_t const v_idx = (opcode & 0x0F00) >> 8;
    uint8_t const compare_val = (opcode & 0x00FF);

    if (_v_reg[v_idx] == compare_val) {
        std::cout << "Skip following instruction. \n";
        _pc_reg += 4;
    } else {
        _pc_reg += 2;
    }
}

void cpu::op_4(uint16_t const opcode) {
    // 4XNN	Skip the following instruction if the value of register VX is not equal to NN
    uint8_t const v_idx = (opcode & 0x0F00) >> 8;
    uint8_t const compare_val = (opcode & 0x00FF);

    if (_v_reg[v_idx] != compare_val) {
        std::cout << "Skip following instruction. \n";
        _pc_reg += 4;
    } else {
        _pc_reg += 2;

    }
}

void cpu::op_5(uint16_t const opcode) {
    // 5XY0	Skip the following instruction if the value of register VX is equal to the value of register VY
    uint8_t const v_idx_x = (opcode & 0x0F00) >> 8;
    uint8_t const v_idx_y = (opcode & 0x00F0) >> 4;

    if (_v_reg[v_idx_x] == _v_reg[v_idx_y]) {
        std::cout << "Skip following instruction. \n";
        _pc_reg += 4;
    } else {
        _pc_reg += 2;
    }
}

void cpu::op_6(uint16_t const opcode) {
    // 6XNN	Store number NN in register VX
    uint8_t const v_idx = (opcode & 0x0F00) >> 8;
    uint8_t const value = (opcode & 0x00FF);

    _v_reg[v_idx] = value;

    _pc_reg += 2;

    std::cout << "Store (NN) in (X): " << std::hex
              << static_cast<int>(value) << " " << static_cast<int>(v_idx) << '\n';
}

void cpu::op_7(uint16_t const opcode) {
    // 7XNN	Add the value NN to register VX
    uint8_t const v_idx = (opcode & 0x0F00) >> 8;
    uint8_t const value = (opcode & 0x00FF);

    _v_reg[v_idx] += value;

    _pc_reg += 2;

    std::cout << "Add (NN) to (X): " << std::hex
              << static_cast<int>(value) << " " << static_cast<int>(v_idx) << '\n';
}

void cpu::op_8(uint16_t const opcode) {

    // 8XY0
    uint8_t const v_idx_x = (opcode & 0x0F00) >> 8;
    uint8_t const v_idx_y = (opcode & 0x00F0) >> 4;

    switch (opcode & 0x000F) {
        // 8XY0	Store the value of register VY in register VX
        case 0x0000: {
            _v_reg[v_idx_x] = _v_reg[v_idx_y];

            break;
        }
            // 8XY1	Set VX to VX OR VY
        case 0x0001: {
            uint8_t const vx = _v_reg[v_idx_x];
            uint8_t const vy = _v_reg[v_idx_y];

            _v_reg[v_idx_x] = vx | vy;
            break;
        }
            // 8XY2	Set VX to VX AND VY
        case 0x0002: {
            uint8_t const vx = _v_reg[v_idx_x];
            uint8_t const vy = _v_reg[v_idx_y];

            _v_reg[v_idx_x] = vx & vy;
            break;
        }
            // 8XY3	Set VX to VX XOR VY
        case 0x0003: {
            uint8_t const vx = _v_reg[v_idx_x];
            uint8_t const vy = _v_reg[v_idx_y];

            _v_reg[v_idx_x] = vx ^ vy;
            break;
        }
            // 8XY4	Add the value of register VY to register VX
            //      Set VF to 01 if a carry occurs
            //      Set VF to 00 if a carry does not occur
        case 0x0004: {
            uint8_t const vx = _v_reg[v_idx_x];
            uint8_t const vy = _v_reg[v_idx_y];

            // If (UINT8_MAX - vy) is bigger than vx,
            // we know that the result of vx + vy will be bigger than UINT8_MAX. Set carry
            if (vx > (UINT8_MAX - vy)) {
                _v_reg[0x000F] = 0x01;
            } else {
                _v_reg[0x000F] = 0x00;
            }

            _v_reg[v_idx_x] = vx + vy;

            break;
        }
            // 8XY5	Subtract the value of register VY from register VX
            //      Set VF to 00 if a borrow occurs
            //      Set VF to 01 if a borrow does not occur
        case 0x0005: {
            uint8_t const vx = _v_reg[v_idx_x];
            uint8_t const vy = _v_reg[v_idx_y];

            // If vx is bigger than vy, then the result of vx - vy will always be positive. No carry
            if (vx > vy) {
                _v_reg[0x000F] = 0x00;
            } else {
                _v_reg[0x000F] = 0x01;
            }

            _v_reg[v_idx_x] = vx - vy;

            break;
        }
            // 8XY6	Store the value of register VY shifted right one bit in register VX
            //      Set register VF to the least significant bit prior to the shift
        case 0x0006: {
            uint8_t const vy = _v_reg[v_idx_y];

            _v_reg[0x000F] = vy & 0x01;

            _v_reg[v_idx_x] = vy >> 1;

            break;
        }
            // 8XY7	Set register VX to the value of VY minus VX
            //      Set VF to 00 if a borrow occurs
            //      Set VF to 01 if a borrow does not occur
        case 0x0007: {
            uint8_t const vx = _v_reg[v_idx_x];
            uint8_t const vy = _v_reg[v_idx_y];

            // If vx is bigger than vy, then the result of vx - vy will always be positive. No carry
            if (vy > vx) {
                _v_reg[0x000F] = 0x00;
            } else {
                _v_reg[0x000F] = 0x01;
            }

            _v_reg[v_idx_x] = vy - vx;

            break;
        }
            // 8XYE	Store the value of register VY shifted left one bit in register VX
            //      Set register VF to the most significant bit prior to the shift
        case 0x000E: {
            uint8_t const vy = _v_reg[v_idx_y];

            _v_reg[0x000F] = vy >> 7;

            _v_reg[v_idx_x] = vy << 1;
            break;
        }
        default: {
            break;
        }
    }
    _pc_reg += 2;
}


void cpu::op_9(uint16_t const opcode) {
    // 9XY0	Skip the following instruction if the value of register VX is not equal to the value of register VY
    uint8_t const v_idx_x = (opcode & 0x0F00) >> 8;
    uint8_t const v_idx_y = (opcode & 0x00F0) >> 4;

    if (_v_reg[v_idx_x] != _v_reg[v_idx_y]) {
        std::cout << "Skip following instruction. \n";
        _pc_reg += 4;
    } else {
        _pc_reg += 2;
    }
}

void cpu::op_A(uint16_t const opcode) {
    // ANNN	Store memory address NNN in register I
    _i_reg = (opcode & 0x0FFF);

    _pc_reg += 2;
    std::cout << "Store (NNN) in reg I: " << std::hex << static_cast<int>(_i_reg) << '\n';
}

void cpu::op_B(uint16_t const opcode) {
    // BNNN	Jump to address NNN + V0
    uint16_t const address = (opcode + 0x0FFF) + _v_reg[0];

    _pc_reg += 2;

    std::cout << "Go to address: " << std::hex << static_cast<int>(address) << '\n';
}

void cpu::op_C(uint16_t const opcode) {
    // CXNN	Set VX to a random number with a mask of NN
    uint8_t const v_idx = (opcode & 0x0F00) >> 8;

    uint8_t const random_val = /* should be random */ (3 & (opcode & 0x00FF));

    _pc_reg += 2;

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

    uint8_t const v_idx_x = (opcode & 0x0F00) >> 8;
    uint8_t const v_idx_y = (opcode & 0x00F0) >> 4;

    uint8_t const pos_x = _v_reg[v_idx_x];
    assert(pos_x >= 0 && pos_x < 64);

    uint8_t const pos_y = _v_reg[v_idx_y];
    assert(pos_y >= 0 && pos_y < 32);

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

                const auto new_pixel = current_pixel ^0x01;
                _gfx.pixel_set(new_x, new_y, new_pixel);

                std::cout << "Setting pixel at (x, y) to (N): "
                          << "(" << std::dec << static_cast<int>(new_x) << ", " << static_cast<int>(new_y) << ") "
                          << new_pixel << '\n';
            }
        }
    }

    _pc_reg += 2;
}

void cpu::op_E(uint16_t const opcode) {
    uint8_t const v_idx = (opcode & 0x0F00) >> 8;
    uint8_t const key = _v_reg[v_idx];

    switch (opcode & 0x00FF) {
        // EX9E	Skip the following instruction if the key corresponding to
        //      the hex value currently stored in register VX is pressed
        case 0x009E: {
            std::cout << "Key in V register (X): " << std::hex << static_cast<int>(key) << '\n';

            if (_keypad.is_pressed(key)) {
                _pc_reg += 4;
            } else {
                _pc_reg += 2;
            }

            break;
        }
            // EXA1	Skip the following instruction if the key corresponding to
            //      the hex value currently stored in register VX is not pressed
        case 0x00A1: {
            std::cout << "Key in V register (X): " << std::hex << static_cast<int>(key) << '\n';

            if (!_keypad.is_pressed(key)) {
                _pc_reg += 4;
            } else {
                _pc_reg += 2;
            }
            break;
        }
        default: {
            break;
        }
    }
}

void cpu::op_F(uint16_t const opcode) {
    switch (opcode & 0x00FF) {
        // FX07	Store the current value of the delay timer in register VX
        case 0x0007: {
            uint8_t const v_idx = (opcode & 0x0F00) >> 8;

            _v_reg[v_idx] = _delay_timer;

            _pc_reg += 2;

            break;
        }
            // FX0A	Wait for a keypress and store the result in register VX
            // Note: Blocking operation
        case 0x000A: {
            uint8_t const v_idx = (opcode & 0x0F00) >> 8;

            bool is_key_pressed = false;
            uint8_t key;

            while (!is_key_pressed) {
                for (key = 0; key < 16 && !is_key_pressed; ++key) {
                    is_key_pressed = _keypad.is_pressed(key);
                }
            }
            _v_reg[v_idx] = key;

            _pc_reg += 2;

            break;
        }
            // FX15	Set the delay timer to the value of register VX
        case 0x0015: {
            uint8_t const v_idx = (opcode & 0x0F00) >> 8;
            uint8_t const value = _v_reg[v_idx];

            _delay_timer = value;

            _pc_reg += 2;

            break;
        }
            // FX18	Set the sound timer to the value of register VX
        case 0x0018: {
            uint8_t const v_idx = (opcode & 0x0F00) >> 8;
            uint8_t const value = _v_reg[v_idx];

            _sound_timer = value;

            _pc_reg += 2;

            break;
        }
            // FX1E	Add the value stored in register VX to register I
        case 0x001E: {
            uint8_t const v_idx = (opcode & 0x0F00) >> 8;
            uint8_t const value = _v_reg[v_idx];

            _i_reg = value;

            _pc_reg += 2;

            break;
        }
            // FX29	Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX
        case 0x0029: {
            uint8_t const v_idx = (opcode & 0x0F00) >> 8;
            uint8_t const value = _v_reg[v_idx];

            _i_reg = value * 5; // Fontset is 4x5

            _pc_reg += 2;

            break;
        }
            // FX33 Stores the binary-coded decimal representation of VX,
            //      with the most significant of three digits at the address in I,
            //      the middle digit at I plus 1, and the least significant digit at I plus 2.
        case 0x0033: {
            uint8_t const v_idx = (opcode & 0x0F00) >> 8;
            uint8_t const v_x = _v_reg[v_idx];

            _ram.write(_i_reg, (v_x / 100));
            _ram.write(_i_reg + 1, (v_x / 10) % 10);
            _ram.write(_i_reg + 2, (v_x % 10) % 10);

            _pc_reg += 2;

            break;
        }
            // FX55	Store the values of registers V0 to VX inclusive in memory starting at address I
            //      I is set to I + X + 1 after operation
        case 0x0055: {
            uint8_t const v_idx_end = (opcode & 0x0F00) >> 8;
            assert(v_idx_end >= 0 && v_idx_end < 8);

            for (uint8_t i = 0; i < v_idx_end; ++i) {
                _ram.write(_i_reg++, _v_reg[i]);
            }

            _pc_reg += 2;

            break;
        }
            // FX65	Fill registers V0 to VX inclusive with the values stored in memory starting at address I
            //      I is set to I + X + 1 after operation
        case 0x0065: {
            uint8_t const v_idx_end = (opcode & 0x0F00) >> 8;
            assert(v_idx_end >= 0 && v_idx_end < 8);

            for (uint8_t i = 0; i < v_idx_end; ++i) {
                _v_reg[i] = _ram.read(_i_reg++);
            }

            _pc_reg += 2;

            break;
        }
        default: {
            break;
        }
    }

}
