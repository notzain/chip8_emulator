//
// Created by zain on 5/27/18.
//

#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include <array>
#include <map>

class chip8;

class cpu {
private:
    chip8 &_chip8;
    /*
     * Chip8 has 15 general purpose registers: V0, V1 .. VE (15)
     * VF (16) is used for the 'carry flag'.
     * When this flag is set, it indicates that a sum of 2 registers exceeds 255.
     */
    std::array<uint8_t, 16> _v_reg;

    /*
     * The I register stores one memory address.
     */
    uint16_t _i_reg;

    /*
     * The program counter register holds the address of the next opcode to fetch.
     */
    uint16_t _pc_reg = 0x200;

    using opcode_func = void (cpu::*)(uint16_t const);
    static const std::map<uint16_t, opcode_func> _instruction_set;

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
    explicit cpu(chip8 &chip);

    inline uint16_t fetch() const { return _pc_reg; }

    uint16_t decode(uint16_t const opcode) const;

    void execute(uint16_t const opmask, uint16_t const opcode);
};

#endif //CHIP8_CPU_H
