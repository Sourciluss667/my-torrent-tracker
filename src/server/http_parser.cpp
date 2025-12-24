//
// Created by Quentin Cormand on 23/12/2025.
//

#include "http_parser.hpp"

bool HttpParser::is_announce(const HttpRequest &req) {
    return req.target().starts_with("/announce");
}

AnnounceRequest HttpParser::parse_announce(const HttpRequest &req, std::string ip) {
    const boost::urls::url_view url(req.target());
    const auto params = url.params();

    AnnounceRequest announce;

    announce.info_hash = decode_binary_20(
        require_param(params, "info_hash")
    );
    announce.peer_id = decode_binary_20(
        require_param(params, "peer_id")
    );
    announce.port = static_cast<uint16_t>(
        std::stoi(std::string(require_param(params, "port")))
    );
    announce.uploaded = std::stoull(
        std::string(require_param(params, "uploaded"))
    );
    announce.downloaded = std::stoull(
        std::string(require_param(params, "downloaded"))
    );
    announce.left = std::stoull(
        std::string(require_param(params, "left"))
    );
    announce.event = require_param(params, "event");
    announce.ip = std::move(ip);

    return announce;
}

std::string_view HttpParser::require_param(
    const boost::urls::params_view &params,
    const std::string_view key
) {
    const auto it = params.find(key);

    if (it == params.end()) {
        throw std::runtime_error("Missing param: " + std::string(key));
    }

    return (*it).value;
}

std::array<uint8_t, 20> HttpParser::decode_binary_20(const std::string_view v) {
    if (v.size() != 20) {
        throw std::runtime_error("Invalid binary field size");
    }

    std::array<uint8_t, 20> out{};
    std::memcpy(out.data(), v.data(), 20);
    return out;
}
