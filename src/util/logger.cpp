//
// Created by zain on 6/17/18.
//

#include "logger.h"
#include "fmt/printf.h"

#include <chrono>
#include <iostream>
#include <iomanip>

#define _DEBUG 1

namespace util {
    void logger::log(logger::type type, std::string const &msg) {
#if (_DEBUG )
        auto type_as_string = [type]() -> std::string {
            switch (type) {
                case logger::type::DEBUG:
                    return "DEBUG";
                case logger::type::WARNING:
                    return "WARNING";
                case logger::type::ERROR:
                    return "ERROR";
            }
        };

        std::time_t cur_time = std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now());

        std::string const formatted_msg =
                fmt::format("[{0}] {1} - {2}",
                            type_as_string(),
                            std::put_time(std::localtime(&cur_time), "%T"),
                            msg);

        if (type == logger::type::ERROR) {
            std::cerr << formatted_msg << '\n';
        } else {
            std::cout << formatted_msg << '\n';
        }
#endif
    }
}
