//
// Created by zain on 6/18/18.
//

#include "fmt/printf.h"

#include "core/chip8.h"
#include "KeypadCanvas.h"

#include <SFML/Window/Mouse.hpp>


namespace ui {
    KeypadCanvas::KeypadCanvas(core::chip8 &chip8, const int pos_x, const int pos_y, const int resolution)
            : _chip8(chip8),
              ICanvas(pos_x, pos_y, 32, 32),
              _resolution(resolution),
              _buttons{{0x01, 0x04, 0x07, 0x0A},
                       {0x02, 0x05, 0x08, 0x00},
                       {0x03, 0x06, 0x09, 0x0B},
                       {0x0C, 0x0D, 0x0E, 0x0F}} {

        int const div_size = (32 * _resolution) / 4;
        int const pad_size = 2;
        auto const actual_size = static_cast<float>(div_size - pad_size);

        for (int row = 0; row < 4; ++row) {
            for (int column = 0; column < 4; ++column) {
                auto &btn = _buttons[row][column];

                btn.setSize({actual_size, actual_size});
                btn.setPosition(row * div_size + pad_size + (start_x() * resolution),
                                column * div_size + pad_size + (start_y() * resolution));
                btn.setOutlineColor(sf::Color::Black);
            }
        }
    }

    void KeypadCanvas::render(sf::RenderWindow &window) {
        static bool last_pressed = false;

        bool const mouse_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        auto const mouse_pos = sf::Mouse::getPosition(window);

        bool to_press = last_pressed != mouse_pressed;

        for (int row = 0; row < 4; ++row) {
            for (int column = 0; column < 4; ++column) {
                auto &btn = _buttons[row][column];

                if (to_press) {
                    if (btn.overlaps(mouse_pos) && !btn.is_pressed()) {
                        auto const hex = btn.hex();

                        _chip8.press_key(hex);
                        btn.press();

                        btn.setFillColor(sf::Color::Green);
                    }
                } else {
                    btn.setFillColor(sf::Color::White);
                    btn.release();
                }

                window.draw(btn);
            }
        }

        last_pressed = mouse_pressed;
    }
}
