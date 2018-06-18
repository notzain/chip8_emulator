//
// Created by zain on 6/18/18.
//

#ifndef CHIP8_KEYPADCANVAS_H
#define CHIP8_KEYPADCANVAS_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "ICanvas.h"

namespace core {
    class chip8;
}

namespace ui {
    class KeypadButton : public sf::RectangleShape {
    private:
        uint8_t _hex;

    public:
        KeypadButton(uint8_t const hex) : _hex(hex) {}

        uint8_t hex() const { return _hex; }

        bool overlaps(sf::Vector2i const &position) const {
            return (position.x >= getPosition().x &&
                    position.x <= getPosition().x + getSize().x &&
                    position.y >= getPosition().y &&
                    position.y <= getPosition().y + getSize().y);
        }
    };

    class KeypadCanvas : public ICanvas {
    private:
        core::chip8 &_chip8;
        KeypadButton _buttons[4][4];

    public:
        KeypadCanvas(core::chip8 &chip8, const int pos_x, const int pos_y);

        void render(sf::RenderWindow &window, int const resolution) override;
    };
}


#endif //CHIP8_KEYPADCANVAS_H
