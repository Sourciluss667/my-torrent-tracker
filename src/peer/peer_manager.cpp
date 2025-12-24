//
// Created by Quentin Cormand on 24/12/2025.
//

#include "peer_manager.hpp"
#include <algorithm>
#include <spdlog/spdlog.h>

using namespace std::chrono;

void PeerManager::add_peer(const std::string &info_hash, const PeerInfo &peer) {
    std::lock_guard lock(_mutex);

    auto &peer_list = _peers[info_hash];

    const auto it = std::ranges::find_if(peer_list,
                                         [&](const PeerInfo &p) { return p.peer_id == peer.peer_id; });

    if (it != peer_list.end()) {
        it->ip = peer.ip;
        it->port = peer.port;
        it->uploaded = peer.uploaded;
        it->downloaded = peer.downloaded;
        it->left = peer.left;
        it->last_announce = peer.last_announce;
        it->completed = peer.completed;
    } else {
        peer_list.push_back(peer);
    }

    spdlog::info("Added/Updated peer {} for torrent {}", peer.peer_id, info_hash);
}

void PeerManager::remove_peer(const std::string &info_hash, const std::string &peer_id) {
    std::lock_guard lock(_mutex);

    if (const auto it = _peers.find(info_hash); it != _peers.end()) {
        auto &peer_list = it->second;
        peer_list.erase(std::ranges::remove_if(peer_list,
                                               [&](const PeerInfo &p) { return p.peer_id == peer_id; }).begin(),
                        peer_list.end());
        spdlog::info("Removed peer {} for torrent {}", peer_id, info_hash);

        if (peer_list.empty()) {
            _peers.erase(it);
        }
    }
}

std::vector<PeerInfo> PeerManager::get_peers(const std::string &info_hash,
                                             const std::string &exclude_peer_id) const {
    std::lock_guard lock(_mutex);
    std::vector<PeerInfo> result;

    if (const auto it = _peers.find(info_hash); it != _peers.end()) {
        for (const auto &p: it->second) {
            if (p.peer_id != exclude_peer_id) {
                result.push_back(p);
            }
        }
    }

    return result;
}
