//
// Created by zain on 6/17/18.
//

#include "GameCanvas.h"
#include "core/chip8.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace ui {
    GameCanvas::GameCanvas(core::chip8 &chip8, const int pos_x, const int pos_y, const int resolution)
            : _chip8(chip8), ICanvas(pos_x, pos_y, 64, 32), _resolution(resolution) {

        for (int x = 0; x < 64; ++x) {
            for (int y = 0; y < 32; ++y) {
                auto &pixel = _pixels[x][y];
                pixel.setSize({_resolution, _resolution});
                pixel.setPosition((x * _resolution) + (start_x() * _resolution),
                                  (y * _resolution) + (start_y() * _resolution));
            }
        }
    }

    void GameCanvas::render(sf::RenderWindow &window) {
        auto const draw = _chip8.to_draw();

        for (int x = 0; x < 64; ++x) {
            for (int y = 0; y < 32; ++y) {
                auto &pixel = _pixels[x][y];

                if (draw) {
                    pixel.setFillColor(_chip8.pixel_at(x, y) ? sf::Color::White : sf::Color::Black);
                }
                window.draw(pixel);
            }
        }
    }
}
