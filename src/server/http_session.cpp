//
// Created by Quentin Cormand on 23/12/2025.
//

#include "http_session.hpp"
#include "http_parser.hpp"

#include <spdlog/spdlog.h>

#include "../tools/hexify.hpp"

HttpSession::HttpSession(tcp::socket socket)
    : _socket(std::move(socket)) {
}

void HttpSession::run() {
    read_request();
}

void HttpSession::read_request() {
    auto self = shared_from_this();
    http::async_read(_socket, _buffer, _req,
                     [self](const boost::system::error_code &ec, std::size_t) {
                         if (ec == http::error::end_of_stream) {
                             return;
                         } else if (ec) {
                             spdlog::error("HTTP read error: {}", ec.message());
                             return;
                         }
                         self->process_request();
                     });
}

void HttpSession::process_request() {
    handle_request();

    auto self = shared_from_this();
    http::async_write(_socket, _res,
                      // self is important here to keep the session alive until the response is sent
                      [self](const boost::system::error_code &ec, std::size_t) {
                          if (ec) {
                              spdlog::error("HTTP write error: {}", ec.message());
                          }
                      });
}

void HttpSession::handle_request() {
    if (HttpParser::is_announce(_req)) {
        handle_announce();
    } else {
        handle_not_found();
    }
}

void HttpSession::handle_not_found() {
    _res = HttpResponse(http::status::not_found, _req.version());
    _res.set(http::field::server, "Tracker");
    _res.set(http::field::content_type, "text/plain");
    _res.keep_alive(false);

    _res.body() = "Not found";

    _res.prepare_payload();
}

void HttpSession::handle_announce() {
    _res = HttpResponse(http::status::ok, _req.version());
    _res.set(http::field::server, "Tracker");
    _res.set(http::field::content_type, "text/plain");
    _res.keep_alive(false);

    _res.body() = "Tracker alive";

    AnnounceRequest announce;

    try {
        announce = HttpParser::parse_announce(_req, _socket.remote_endpoint().address().to_string());
    } catch (std::exception &e) {
        spdlog::error("Invalid announce params: {}", e.what());
        // TODO bencode the error
        _res.body() = "Invalid announce request";
        _res.prepare_payload();

        return;
    }

    spdlog::info(
        "IP: {} | Port: {} | Uploaded: {} | Downloaded: {} | Left: {} | Event: {} | Peer ID: {} | Info Hash: {}",
        announce.ip,
        announce.port,
        announce.uploaded,
        announce.downloaded,
        announce.left,
        announce.event,
        Hexify::hexify(announce.peer_id),
        Hexify::hexify(announce.info_hash)
    );

    _res.prepare_payload();
}
