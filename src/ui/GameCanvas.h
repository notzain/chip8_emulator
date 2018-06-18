//
// Created by zain on 6/17/18.
//

#ifndef CHIP8_GAMECANVAS_H
#define CHIP8_GAMECANVAS_H

#include "ICanvas.h"

namespace core {
    class chip8;
}

namespace ui {
    class GameCanvas : public ICanvas {
    private:
        core::chip8 &_chip8;
    public:
        GameCanvas(core::chip8 &chip8, const int pos_x, const int pos_y);

        void render(sf::RenderWindow &window, int const resolution) override;
    };
}


#endif //CHIP8_GAMECANVAS_H
