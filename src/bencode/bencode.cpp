//
// Created by Quentin Cormand on 24/12/2025.
//

#include "bencode.hpp"
#include "../peer/peer_manager.hpp"
#include <arpa/inet.h>
#include <spdlog/spdlog.h>

namespace Bencode {
    std::string encode_peers_compact(const std::vector<PeerInfo> &peers) {
        std::string out;
        for (const auto &p: peers) {
            struct in_addr addr;
            if (inet_pton(AF_INET, p.ip.c_str(), &addr) != 1) {
                spdlog::error("Invalid IP address: {}", p.ip);
                continue;
            }

            out.append(reinterpret_cast<const char *>(&addr.s_addr), 4);

            uint16_t port = htons(p.port);
            out.append(reinterpret_cast<const char *>(&port), 2);
        }
        return out;
    }
}
