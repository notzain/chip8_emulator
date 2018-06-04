//
// Created by zain on 6/1/18.
//

#include "src/chip8.h"
#include "KeypadWindow.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>


KeypadWindow::KeypadWindow(chip8 &chip8, std::string window_name, int resolution)
        : _chip8(chip8),
          _resolution(resolution),
          sf::RenderWindow(sf::VideoMode(32 * resolution, 32 * resolution), window_name),
          _buttons{
                  /*
                  0x01, 0x02, 0x03, 0x0C,
                  0x04, 0x05, 0x06, 0x0D,
                  0x07, 0x08, 0x09, 0x0E,
                  0x0A, 0x00, 0x0B, 0x0F
                  */
                  {0x01, 0x04, 0x07, 0x0A},
                  {0x02, 0x05, 0x08, 0x00},
                  {0x03, 0x06, 0x09, 0x0B},
                  {0x0C, 0x0D, 0x0E, 0x0F}
          } {

    const int div_size = (32 * _resolution) / 4;
    const int pad_size = 2;
    const int actual_size = div_size - pad_size;

    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            auto &btn = _buttons[row][column];

            btn.setSize({actual_size, actual_size});
            btn.setPosition(row * div_size + pad_size, column * div_size + pad_size);
            btn.setOutlineColor(sf::Color::Black);
        }
    }

}

void KeypadWindow::update() {
    sf::Event event{};
    while (pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            close();
    }

    clear();

    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            auto &btn = _buttons[row][column];
            btn.setFillColor(sf::Color::White);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                auto const mouse_pos = sf::Mouse::getPosition(*this);
                if (btn.overlaps(mouse_pos)) {
                    btn.setFillColor(sf::Color::Green);
                    auto const hex = btn.hex();
                    std::cerr << std::hex << static_cast<int>(hex) << '\n';

                    _chip8.press_key(hex);
                }
            }

            draw(btn);
        }
    }


    /*
    const int div_size = (32 * _resolution) / 4;
    const int pad_size = 2;
    const int actual_size = div_size - pad_size;
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            sf::RectangleShape keypad_btn({actual_size, actual_size});
            keypad_btn.setPosition(row * div_size + pad_size, column * div_size + pad_size);
            keypad_btn.setOutlineColor(sf::Color::Black);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                auto mouse_pos = sf::Mouse::getPosition(*this);

                if (mouse_pos.x >= keypad_btn.getPosition().x &&
                    mouse_pos.x <= keypad_btn.getPosition().x + keypad_btn.getSize().x &&
                    mouse_pos.y >= keypad_btn.getPosition().y &&
                    mouse_pos.y <= keypad_btn.getPosition().y + keypad_btn.getSize().y) {

                    keypad_btn.setFillColor(sf::Color::Green);
                }
            }

            draw(keypad_btn);
        }
    }
     */

    display();
}
