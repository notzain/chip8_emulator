//
// Created by zain on 5/27/18.
//

#include "cpu.h"
#include "chip8.h"

#include "fmt/format.h"
#include "util/logger.h"

#include <cassert>

namespace core {

    const std::unordered_map<uint16_t, cpu::cpu_instruction> cpu::instruction_set = {
            {0x0000, {"0x0000", "no description", &cpu::op_0}},
            {0x1000, {"0x1000", "no description", &cpu::op_1}},
            {0x2000, {"0x2000", "no description", &cpu::op_2}},
            {0x3000, {"0x3000", "no description", &cpu::op_3}},
            {0x4000, {"0x4000", "no description", &cpu::op_4}},
            {0x5000, {"0x5000", "no description", &cpu::op_5}},
            {0x6000, {"0x6000", "no description", &cpu::op_6}},
            {0x7000, {"0x7000", "no description", &cpu::op_7}},
            {0x8000, {"0x8000", "no description", &cpu::op_8}},
            {0x9000, {"0x9000", "no description", &cpu::op_9}},
            {0xA000, {"0xA000", "no description", &cpu::op_A}},
            {0xB000, {"0xB000", "no description", &cpu::op_B}},
            {0xC000, {"0xC000", "no description", &cpu::op_C}},
            {0xD000, {"0xD000", "no description", &cpu::op_D}},
            {0xE000, {"0xE000", "no description", &cpu::op_E}},
            {0xF000, {"0xF000", "no description", &cpu::op_F}},
    };

    cpu::cpu(ram &ram, gfx &gfx, keypad &keypad) : _ram(ram), _gfx(gfx), _keypad(keypad) {
        srand(time(NULL));
    }

    uint16_t cpu::decode(uint16_t const opcode) const {
        return (opcode & 0xF000);
    }

    void cpu::execute(uint16_t const opmask, uint16_t const opcode) {
        auto const instr = instruction_set.find(opmask);

        if (instr != instruction_set.cend()) {
            (this->*(instr->second).func)(opcode);
        } else {
            util::logger::log(
                util::logger::type::ERROR,
                fmt::format("Invalid hex code: opcode {:#x} | opmask {:#x}", opcode, opmask)
            );
        }

        if (_registers.delay_timer > 0) --_registers.delay_timer;
        if (_registers.sound_timer > 0) --_registers.sound_timer;
    }

    void cpu::op_0(uint16_t const opcode) {

        // 00E0	Clear the screen
        if (opcode == 0x00E0) {
            _gfx.clear();
            _should_draw = true;
            _registers.pc_reg += 2;
        }
            // 00EE	Return from a subroutine
        else if (opcode == 0x00EE) {
            _registers.pc_reg = _registers.stack[--_registers.stack_idx];
            _registers.pc_reg += 2;
        }
            // 0NNN	Execute machine language subroutine at address NNN
        else {
            uint16_t const address = (opcode & 0x0FFF);
        }
    }

    void cpu::op_1(uint16_t const opcode) {
        // 1NNN	Jump to address NNN
        uint16_t const address = (opcode & 0x0FFF);
        _registers.pc_reg = address;

    }

    void cpu::op_2(uint16_t const opcode) {
        // 2NNN	Execute subroutine starting at address NNN
        uint16_t const address = (opcode & 0x0FFF);

        _registers.stack[_registers.stack_idx++] = _registers.pc_reg;

        _registers.pc_reg = address;
    }

    void cpu::op_3(uint16_t const opcode) {
        // 3XNN	Skip the following instruction if the value of register VX equals NN
        uint8_t const v_idx = (opcode & 0x0F00) >> 8;
        uint8_t const compare_val = (opcode & 0x00FF);

        if (_registers.v_reg[v_idx] == compare_val) {
            _registers.pc_reg += 4;
        } else {
            _registers.pc_reg += 2;
        }
    }

    void cpu::op_4(uint16_t const opcode) {
        // 4XNN	Skip the following instruction if the value of register VX is not equal to NN
        uint8_t const v_idx = (opcode & 0x0F00) >> 8;
        uint8_t const compare_val = (opcode & 0x00FF);

        if (_registers.v_reg[v_idx] != compare_val) {
            _registers.pc_reg += 4;
        } else {
            _registers.pc_reg += 2;
        }
    }

    void cpu::op_5(uint16_t const opcode) {
        // 5XY0	Skip the following instruction if the value of register VX is equal to the value of register VY
        uint8_t const v_idx_x = (opcode & 0x0F00) >> 8;
        uint8_t const v_idx_y = (opcode & 0x00F0) >> 4;

        if (_registers.v_reg[v_idx_x] == _registers.v_reg[v_idx_y]) {
            _registers.pc_reg += 4;
        } else {
            _registers.pc_reg += 2;
        }
    }

    void cpu::op_6(uint16_t const opcode) {
        // 6XNN	Store number NN in register VX
        uint8_t const v_idx = (opcode & 0x0F00) >> 8;
        uint8_t const value = (opcode & 0x00FF);

        _registers.v_reg[v_idx] = value;

        _registers.pc_reg += 2;
    }

    void cpu::op_7(uint16_t const opcode) {
        // 7XNN	Add the value NN to register VX
        uint8_t const v_idx = (opcode & 0x0F00) >> 8;
        uint8_t const value = (opcode & 0x00FF);

        _registers.v_reg[v_idx] += value;

        _registers.pc_reg += 2;

    }

    void cpu::op_8(uint16_t const opcode) {

        // 8XY0
        uint8_t const v_idx_x = (opcode & 0x0F00) >> 8;
        uint8_t const v_idx_y = (opcode & 0x00F0) >> 4;

        switch (opcode & 0x000F) {
            // 8XY0	Store the value of register VY in register VX
            case 0x0000: {
                _registers.v_reg[v_idx_x] = _registers.v_reg[v_idx_y];

                break;
            }
                // 8XY1	Set VX to VX OR VY
            case 0x0001: {
                _registers.v_reg[v_idx_x] |= _registers.v_reg[v_idx_y];
                break;
            }
                // 8XY2	Set VX to VX AND VY
            case 0x0002: {
                _registers.v_reg[v_idx_x] &= _registers.v_reg[v_idx_y];
                break;
            }
                // 8XY3	Set VX to VX XOR VY
            case 0x0003: {
                _registers.v_reg[v_idx_x] ^= _registers.v_reg[v_idx_y];
                break;
            }
                // 8XY4	Add the value of register VY to register VX
                //      Set VF to 01 if a carry occurs
                //      Set VF to 00 if a carry does not occur
            case 0x0004: {
                uint8_t const vx = _registers.v_reg[v_idx_x];
                uint8_t const vy = _registers.v_reg[v_idx_y];

                uint16_t const sum = vx + vy;

                if (sum > UINT8_MAX) {
                    _registers.v_reg[0x000F] = 0x01;
                } else {
                    _registers.v_reg[0x000F] = 0x00;
                }

                _registers.v_reg[v_idx_x] = sum;

                break;
            }
                // 8XY5	Subtract the value of register VY from register VX (VX - VY)
                //      Set VF to 00 if a borrow occurs
                //      Set VF to 01 if a borrow does not occur
            case 0x0005: {
                uint8_t const vx = _registers.v_reg[v_idx_x];
                uint8_t const vy = _registers.v_reg[v_idx_y];

                // If vy is bigger than vx, the result will be negative.
                if (vy > vx) {
                    _registers.v_reg[0x000F] = 0x00;
                } else {
                    _registers.v_reg[0x000F] = 0x01;
                }

                _registers.v_reg[v_idx_x] = vx - vy;

                break;
            }
                // 8XY6	Store the value of register VY shifted right one bit in register VX
                //      Set register VF to the least significant bit prior to the shift
            case 0x0006: {
                uint8_t const vy = _registers.v_reg[v_idx_y];

                _registers.v_reg[0x000F] = vy & 0x01;

                _registers.v_reg[v_idx_x] = vy >> 1;

                break;
            }
                // 8XY7	Set register VX to the value of VY minus VX (VY - VX)
                //      Set VF to 00 if a borrow occurs
                //      Set VF to 01 if a borrow does not occur
            case 0x0007: {
                uint8_t const vx = _registers.v_reg[v_idx_x];
                uint8_t const vy = _registers.v_reg[v_idx_y];

                // If vx is bigger than vy, then the result of vx - vy will always be positive. No carry
                if (vx > vy) {
                    _registers.v_reg[0x000F] = 0x00;
                } else {
                    _registers.v_reg[0x000F] = 0x01;
                }

                _registers.v_reg[v_idx_x] = vy - vx;

                break;
            }
                // 8XYE	Store the value of register VY shifted left one bit in register VX
                //      Set register VF to the most significant bit prior to the shift
            case 0x000E: {
                uint8_t const vy = _registers.v_reg[v_idx_y];

                _registers.v_reg[0x000F] = vy >> 7;

                _registers.v_reg[v_idx_x] = vy << 1;
                break;
            }
            default: {
                break;
            }
        }
        _registers.pc_reg += 2;
    }

    void cpu::op_9(uint16_t const opcode) {
        // 9XY0	Skip the following instruction if the value of register VX is not equal to the value of register VY
        uint8_t const v_idx_x = (opcode & 0x0F00) >> 8;
        uint8_t const v_idx_y = (opcode & 0x00F0) >> 4;

        if (_registers.v_reg[v_idx_x] != _registers.v_reg[v_idx_y]) {
            _registers.pc_reg += 4;
        } else {
            _registers.pc_reg += 2;
        }
    }

    void cpu::op_A(uint16_t const opcode) {
        // ANNN	Store memory address NNN in register I
        _registers.i_reg = (opcode & 0x0FFF);

        _registers.pc_reg += 2;
    }

    void cpu::op_B(uint16_t const opcode) {
        // BNNN	Jump to address NNN + V0
        uint16_t const address = (opcode + 0x0FFF) + _registers.v_reg[0];

        _registers.pc_reg += 2;

    }

    void cpu::op_C(uint16_t const opcode) {
        // CXNN	Set VX to a random number with a mask of NN
        uint8_t const v_idx = (opcode & 0x0F00) >> 8;

        uint8_t const random_val = (rand() & 0xFF) & (opcode & 0x00FF);

        _registers.v_reg[v_idx] = random_val;

        _registers.pc_reg += 2;

    }

    void cpu::op_D(uint16_t const opcode) {

        /* DXYN
         * Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
         * Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
         *
         * The two cpu_registers passed to this instruction determine the x and y location of the sprite on the screen.
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

        uint8_t const pos_x = _registers.v_reg[v_idx_x];
        assert(pos_x >= 0 && pos_x < 64);

        uint8_t const pos_y = _registers.v_reg[v_idx_y];
        assert(pos_y >= 0 && pos_y < 32);

        uint8_t const height = (opcode & 0x000F);

        _registers.v_reg[0x000F] = 0x00;
        for (uint8_t y = 0; y < height; ++y) {
            // This byte contains 8 bits, each represent a pixel.
            auto const pixel_row = _ram.read(_registers.i_reg + y);

            for (uint8_t x = 0; x < 8; ++x) {
                // Extract one byte from the pixel_row.
                auto const pixel = pixel_row & (0b10000000 >> x);

                // Should a pixel be drawn?
                if (pixel) {
                    uint8_t const new_x = pos_x + x;
                    uint8_t const new_y = pos_y + y;

                    auto const current_pixel = _gfx.pixel_at(new_x, new_y);
                    if (current_pixel == 1) {
                        _registers.v_reg[0x000F] = 0x01;
                    }

                    _gfx.pixel_set(new_x, new_y, current_pixel ^ 0x01);

                    util::logger::log(util::logger::type::DEBUG,
                                      fmt::format("Setting pixel at ({}, {})", new_x, new_y));
                }
            }
        }

        _should_draw = true;

        _registers.pc_reg += 2;
    }

    void cpu::op_E(uint16_t const opcode) {
        uint8_t const v_idx = (opcode & 0x0F00) >> 8;
        uint8_t const key = _registers.v_reg[v_idx];

        switch (opcode & 0x00FF) {
            // EX9E	Skip the following instruction if the key corresponding to
            //      the hex value currently stored in register VX is pressed
            case 0x009E: {

                if (_keypad.is_pressed(key)) {
                    _registers.pc_reg += 4;
                } else {
                    _registers.pc_reg += 2;
                }
                _keypad.press(key, false);

                break;
            }
                // EXA1	Skip the following instruction if the key corresponding to
                //      the hex value currently stored in register VX is not pressed
            case 0x00A1: {

                if (!_keypad.is_pressed(key)) {
                    _registers.pc_reg += 4;
                } else {
                    _registers.pc_reg += 2;
                }
                _keypad.press(key, false);

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

                _registers.v_reg[v_idx] = _registers.delay_timer;

                _registers.pc_reg += 2;

                break;
            }
                // FX0A	Wait for a keypress and store the result in register VX
                // Note: Blocking operation
            case 0x000A: {
                uint8_t const v_idx = (opcode & 0x0F00) >> 8;

                util::logger::log(util::logger::type::DEBUG, fmt::format("Waiting for key press"));

                bool is_key_pressed = false;
                uint8_t key;

                for (key = 0; key < 16 && !is_key_pressed; ++key) {
                    is_key_pressed = _keypad.is_pressed(key);
                }

                /*
                * If no key has been pressed, return from function
                * This makes sure that the program counter is not forwarded
                * And this function will run in the next iteration as well
                *
                * Do not run in an infinite while loop, else other parts of the emulator will block as well.
                */

                if (!is_key_pressed) {
                    return;
                }

                _keypad.press(key, false);

                _registers.v_reg[v_idx] = key;

                _registers.pc_reg += 2;

                break;
            }
                // FX15	Set the delay timer to the value of register VX
            case 0x0015: {
                uint8_t const v_idx = (opcode & 0x0F00) >> 8;
                uint8_t const value = _registers.v_reg[v_idx];

                _registers.delay_timer = value;

                _registers.pc_reg += 2;

                break;
            }
                // FX18	Set the sound timer to the value of register VX
            case 0x0018: {
                uint8_t const v_idx = (opcode & 0x0F00) >> 8;
                uint8_t const value = _registers.v_reg[v_idx];

                _registers.sound_timer = value;

                _registers.pc_reg += 2;

                break;
            }
                // FX1E	Add the value stored in register VX to register I
            case 0x001E: {
                uint8_t const v_idx = (opcode & 0x0F00) >> 8;
                uint8_t const value = _registers.v_reg[v_idx];

                _registers.i_reg += value;

                _registers.pc_reg += 2;

                break;
            }
                // FX29	Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX
            case 0x0029: {
                uint8_t const v_idx = (opcode & 0x0F00) >> 8;
                uint8_t const value = _registers.v_reg[v_idx];

                _registers.i_reg = value * 0x05; // Fontset is 4x5

                _registers.pc_reg += 2;

                break;
            }
                // FX33 Stores the binary-coded decimal representation of VX,
                //      with the most significant of three digits at the address in I,
                //      the middle digit at I plus 1, and the least significant digit at I plus 2.
            case 0x0033: {
                uint8_t const v_idx = (opcode & 0x0F00) >> 8;
                uint8_t const vx = _registers.v_reg[v_idx];

                _ram.write(_registers.i_reg, (vx / 100));
                _ram.write(_registers.i_reg + 1, (vx / 10) % 10);
                _ram.write(_registers.i_reg + 2, (vx % 10) % 10);

                _registers.pc_reg += 2;

                break;
            }
                // FX55	Store the values of cpu_registers V0 to VX inclusive in memory starting at address I
                //      I is set to I + X + 1 after operation
            case 0x0055: {
                uint8_t const v_idx_end = (opcode & 0x0F00) >> 8;
                assert(v_idx_end >= 0 && v_idx_end < 8);

                for (uint8_t i = 0; i <= v_idx_end; ++i) {
                    _ram.write(_registers.i_reg++, _registers.v_reg[i]);
                }

                _registers.pc_reg += 2;

                break;
            }
                // FX65	Fill cpu_registers V0 to VX inclusive with the values stored in memory starting at address I
                //      I is set to I + X + 1 after operation
            case 0x0065: {
                uint8_t const v_idx_end = (opcode & 0x0F00) >> 8;
                assert(v_idx_end >= 0 && v_idx_end < 8);

                for (uint8_t i = 0; i <= v_idx_end; ++i) {
                    _registers.v_reg[i] = _ram.read(_registers.i_reg++);
                }

                _registers.pc_reg += 2;
                break;
            }
            default: {
                break;
            }
        }
    }
}
