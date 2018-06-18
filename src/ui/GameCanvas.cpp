//
// Created by zain on 6/17/18.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include "GameCanvas.h"

#include "core/chip8.h"

ui::GameCanvas::GameCanvas(core::chip8 &chip8, const int pos_x, const int pos_y) : _chip8(chip8), ICanvas(pos_x, pos_y, 64, 32) {}

void ui::GameCanvas::render(sf::RenderWindow &window, int const resolution) {
    if (_chip8.to_draw()) {
        window.clear();

        sf::RectangleShape pixel({resolution, resolution});
        for (int x = 0; x < 64; x++) {
            for (int y = 0; y < 32; ++y) {
                if (_chip8.pixel_at(x, y)) {
                    pixel.setPosition((x * resolution) + (start_x() * resolution),
                                      (y * resolution) + (start_y() * resolution));
                    window.draw(pixel);
                }
            }
        }

        window.display();
        _chip8.has_drawn();
    }
}
