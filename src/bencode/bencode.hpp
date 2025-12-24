//
// Created by Quentin Cormand on 24/12/2025.
//

#ifndef MY_TORRENT_TRACKER_BENCODE_HPP
#define MY_TORRENT_TRACKER_BENCODE_HPP

#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <arpa/inet.h>

struct PeerInfo;

namespace Bencode {
    inline std::string encode_int(int64_t value) {
        return "i" + std::to_string(value) + "e";
    }

    inline std::string encode_string(const std::string &s) {
        return std::to_string(s.size()) + ":" + s;
    }

    inline std::string encode_list(const std::vector<std::string> &items) {
        std::string out = "l";
        for (const auto &i: items) out += i;
        out += "e";
        return out;
    }

    inline std::string encode_dict(const std::vector<std::pair<std::string, std::string> > &items) {
        std::string out = "d";
        for (const auto &p: items) {
            out += encode_string(p.first);
            out += p.second;
        }
        out += "e";
        return out;
    }

    std::string encode_peers_compact(const std::vector<PeerInfo> &peers);
}

#endif //MY_TORRENT_TRACKER_BENCODE_HPP
