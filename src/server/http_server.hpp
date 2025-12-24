//
// Created by Quentin Cormand on 23/12/2025.
//

#ifndef MY_TORRENT_TRACKER_HTTP_SERVER_HPP
#define MY_TORRENT_TRACKER_HTTP_SERVER_HPP

#pragma once

#include <boost/beast.hpp>
#include <boost/asio.hpp>

#include "../peer/peer_manager.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

using HttpRequest = http::request<http::string_body>;
using HttpResponse = http::response<http::string_body>;

class HttpServer {
public:
    explicit HttpServer(unsigned short port);

    void run() const;

private:
    unsigned short _port;
    std::shared_ptr<PeerManager> _peer_manager;
};

#endif //MY_TORRENT_TRACKER_HTTP_SERVER_HPP
