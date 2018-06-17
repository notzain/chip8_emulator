//
// Created by zain on 6/17/18.
//

#ifndef CHIP8_LOGGER_H
#define CHIP8_LOGGER_H

#include <string>

class logger {
public:
    enum class type {
        DEBUG,
        WARNING,
        ERROR
    };

    static void log(type type, std::string const & msg);
};


#endif //CHIP8_LOGGER_H
