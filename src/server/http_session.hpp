//
// Created by Quentin Cormand on 23/12/2025.
//

#ifndef MY_TORRENT_TRACKER_HTTP_SESSION_HPP
#define MY_TORRENT_TRACKER_HTTP_SESSION_HPP

#pragma once

#include "http_server.hpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class HttpSession : public std::enable_shared_from_this<HttpSession> {
public:
    explicit HttpSession(tcp::socket socket);

    void run();

private:
    tcp::socket _socket;
    beast::flat_buffer _buffer;
    HttpRequest _req;
    HttpResponse _res;

    void read_request();

    void process_request();

    void handle_request();

    void handle_announce();

    void handle_not_found();
};

#endif //MY_TORRENT_TRACKER_HTTP_SESSION_HPP
