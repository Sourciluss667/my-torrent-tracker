//
// Created by Quentin Cormand on 23/12/2025.
//

#ifndef MY_TORRENT_TRACKER_HTTP_PARSER_HPP
#define MY_TORRENT_TRACKER_HTTP_PARSER_HPP

#pragma once

#include "http_server.hpp"

#include <boost/url.hpp>

struct AnnounceRequest {
    std::array<uint8_t, 20> info_hash;
    std::array<uint8_t, 20> peer_id;
    std::string ip;
    uint16_t port;
    uint64_t uploaded;
    uint64_t downloaded;
    uint64_t left;
    std::string event;
};

class HttpParser {
public:
    static bool is_announce(const HttpRequest &req);

    static AnnounceRequest parse_announce(const HttpRequest &req, std::string ip);

private:
    static std::string_view require_param(const boost::urls::params_view &params, std::string_view key);

    static std::array<uint8_t, 20> decode_binary_20(std::string_view v);
};

#endif //MY_TORRENT_TRACKER_HTTP_PARSER_HPP
