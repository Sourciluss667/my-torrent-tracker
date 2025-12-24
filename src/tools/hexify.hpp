//
// Created by Quentin Cormand on 24/12/2025.
//

#ifndef MY_TORRENT_TRACKER_HEXIFY_HPP
#define MY_TORRENT_TRACKER_HEXIFY_HPP

#pragma once

#include <sstream>
#include <iomanip>

class Hexify {
public:
    static std::string hexify(const std::array<uint8_t, 20> &arr);
};

#endif //MY_TORRENT_TRACKER_HEXIFY_HPP
