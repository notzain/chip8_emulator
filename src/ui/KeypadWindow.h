//
// Created by zain on 6/1/18.
//

#ifndef CHIP8_KEYPADWINDOW_H
#define CHIP8_KEYPADWINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class chip8;

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

class KeypadWindow : public sf::RenderWindow {
private:
    chip8 &_chip8;
    const int _resolution;

    KeypadButton _buttons[4][4];

public:
    KeypadWindow(chip8 &chip8, std::string window_name, int resolution = 10);

    void update();
};


#endif //CHIP8_KEYPADWINDOW_H
