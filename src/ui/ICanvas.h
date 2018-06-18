//
// Created by zain on 6/17/18.
//

#ifndef CHIP8_ICANVAS_H
#define CHIP8_ICANVAS_H

#include <SFML/Graphics/RenderWindow.hpp>

namespace ui {
    class ICanvas {
        const int _start_x;
        const int _start_y;

        const int _size_x;
        const int _size_y;

    public:
        ICanvas(int const x, int const y, int const size_x, int const size_y) : _start_x(x), _start_y(y),
                                                                                _size_x(size_x), _size_y(size_y) {}

        virtual  ~ICanvas() = default;

        virtual void render(sf::RenderWindow &window, int const resolution) = 0;

        int start_x() const { return _start_x; }
        int start_y() const { return _start_y; }

        int size_x() const { return _size_x; }
        int size_y() const { return _size_y; }
    };
}

#endif //CHIP8_ICANVAS_H
