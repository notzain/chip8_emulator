//
// Created by zain on 6/17/18.
//

#ifndef CHIP8_GAMECANVAS_H
#define CHIP8_GAMECANVAS_H

#include "ICanvas.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace core {
    class chip8;
}

namespace ui {
    class GameCanvas : public ICanvas {
    private:
        core::chip8 &_chip8;
        int _resolution;

        sf::RectangleShape _pixels[64][32]{};
    public:
        GameCanvas(core::chip8 &chip8, const int pos_x, const int pos_y, const int resolution);

        void render(sf::RenderWindow &window) override;
    };
}

#endif //CHIP8_GAMECANVAS_H
