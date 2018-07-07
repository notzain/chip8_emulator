//
// Created by zain on 5/27/18.
//

#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include "ram.h"
#include "gfx.h"
#include "keypad.h"

#include <array>
#include <unordered_map>

namespace core {

    struct cpu_registers {
        /*
         * Chip8 has 15 general purpose cpu_registers: V0, V1 .. VE (15)
         * VF (16) is used for the 'carry flag'.
         * When this flag is set, it indicates that a sum of 2 cpu_registers exceeds 255.
         */
        std::array<uint8_t, 16> v_reg{};

        std::array<uint16_t, 16> stack{};
        uint8_t stack_idx{0};

        /*
         * The I register stores one memory address.
         */
        uint16_t i_reg{0};

        /*
         * The program counter register holds the address of the next opcode to fetch and execute.
         */
        uint16_t pc_reg = 0x200;

        uint8_t delay_timer{0};
        uint8_t sound_timer{0};
    };

    class cpu {
    private:
        ram &_ram;
        gfx &_gfx;
        keypad &_keypad;

        cpu_registers _registers;

        bool _should_draw = true;


        void op_0(uint16_t const opcode);

        void op_1(uint16_t const opcode);

        void op_2(uint16_t const opcode);

        void op_3(uint16_t const opcode);

        void op_4(uint16_t const opcode);

        void op_5(uint16_t const opcode);

        void op_6(uint16_t const opcode);

        void op_7(uint16_t const opcode);

        void op_8(uint16_t const opcode);

        void op_9(uint16_t const opcode);

        void op_A(uint16_t const opcode);

        void op_B(uint16_t const opcode);

        void op_C(uint16_t const opcode);

        void op_D(uint16_t const opcode);

        void op_E(uint16_t const opcode);

        void op_F(uint16_t const opcode);

    public:
        using opcode_func = void (cpu::*)(uint16_t const);

        struct cpu_instruction {
            std::string name;
            std::string description;
            opcode_func func;
        };

        static const std::unordered_map<uint16_t, cpu_instruction> instruction_set;

        cpu(ram &ram, gfx &gfx, keypad &keypad);

        inline uint16_t prog_counter() const { return _registers.pc_reg; }

        inline const cpu_registers& registers() const { return _registers; }

        inline bool to_draw() const { return _should_draw; }

        inline void has_drawn() { _should_draw = false; }

        uint16_t decode(uint16_t const opcode) const;

        void execute(uint16_t const opmask, uint16_t const opcode);
    };
}

#endif //CHIP8_CPU_H
