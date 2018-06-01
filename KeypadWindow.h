//
// Created by zain on 6/1/18.
//

#ifndef CHIP8_KEYPADWINDOW_H
#define CHIP8_KEYPADWINDOW_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "src/chip8.h"

class KeypadWindow : public sf::RenderWindow {
private:
    chip8& _chip8;
    const int _resolution;

public:
    KeypadWindow(chip8 &chip8, std::string window_name, int resolution = 10);

    void update();
};


#endif //CHIP8_KEYPADWINDOW_H
