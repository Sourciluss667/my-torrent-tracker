//
// Created by Quentin Cormand on 24/12/2025.
//

#ifndef MY_TORRENT_TRACKER_PEER_MANAGER_HPP
#define MY_TORRENT_TRACKER_PEER_MANAGER_HPP

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>

struct PeerInfo {
    std::string ip;
    uint16_t port;
    uint64_t uploaded;
    uint64_t downloaded;
    uint64_t left;
    std::string peer_id;
    time_t last_announce;
    bool completed;
};

class PeerManager {
public:
    void add_peer(const std::string &info_hash, const PeerInfo &peer);

    void remove_peer(const std::string &info_hash, const std::string &peer_id);

    std::vector<PeerInfo> get_peers(const std::string &info_hash,
                                    const std::string &exclude_peer_id = "") const;

private:
    mutable std::mutex _mutex;
    std::unordered_map<std::string, std::vector<PeerInfo> > _peers;
};

#endif //MY_TORRENT_TRACKER_PEER_MANAGER_HPP
