//
// Created by Quentin Cormand on 24/12/2025.
//

#include "hexify.hpp"

std::string Hexify::hexify(const std::array<uint8_t, 20> &arr) {
    std::ostringstream oss;
    for (auto b: arr) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int) b;
    }
    return oss.str();
}
