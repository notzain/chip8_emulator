//
// Created by zain on 5/31/18.
//

#ifndef CHIP8_GAMEWINDOW_H
#define CHIP8_GAMEWINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class chip8;

class GameWindow : public sf::RenderWindow {
private:
    chip8 &_chip8;
    const int _resolution;

public:
    GameWindow(chip8 &chip8, std::string window_name, int resolution = 10);

    void update();
};


#endif //CHIP8_GAMEWINDOW_H
