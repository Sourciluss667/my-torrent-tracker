//
// Created by Quentin Cormand on 24/12/2025.
//

#include "bencode.hpp"
#include "../peer/peer_manager.hpp"

namespace Bencode {
    std::string encode_peers_compact(const std::vector<PeerInfo> &peers) {
        std::string out;
        for (const auto &p: peers) {
            uint32_t ip = 0;
            sscanf(p.ip.c_str(), "%u.%u.%u.%u",
                   ((unsigned int *) &ip) + 0,
                   ((unsigned int *) &ip) + 1,
                   ((unsigned int *) &ip) + 2,
                   ((unsigned int *) &ip) + 3);
            ip = htonl(ip);
            out.append(reinterpret_cast<const char *>(&ip), 4);

            uint16_t port = htons(p.port);
            out.append(reinterpret_cast<const char *>(&port), 2);
        }
        return out;
    }
}
