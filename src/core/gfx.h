//
// Created by zain on 5/28/18.
//

#ifndef CHIP8_GFX_H
#define CHIP8_GFX_H

#include <array>

namespace core {
    class gfx {
    private:
        using ScreenArray = std::array<std::array<bool, 32>, 64>;
        ScreenArray _screen{};

    public:
        gfx() = default;

        void clear();

        bool pixel_at(uint8_t const x, uint8_t const y) const;

        void pixel_set(uint8_t const x, uint8_t const y, bool is_set);
    };
}
#endif //CHIP8_GFX_H
