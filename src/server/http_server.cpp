//
// Created by Quentin Cormand on 23/12/2025.
//

#include "http_server.hpp"
#include "http_session.hpp"

#include <spdlog/spdlog.h>

HttpServer::HttpServer(const unsigned short port) : _port(port), _peer_manager(std::make_shared<PeerManager>()) {
}

void HttpServer::run() const {
    auto ioc = std::make_shared<asio::io_context>(1);
    auto acceptor = std::make_shared<tcp::acceptor>(*ioc, tcp::endpoint(tcp::v4(), _port));

    spdlog::info("HTTP Server listening on {}", _port);

    std::function<void()> do_accept;
    do_accept = [ioc, acceptor, &do_accept, peer_manager = _peer_manager]() {
        acceptor->async_accept(
            [ioc, acceptor, &do_accept, peer_manager](const boost::system::error_code &ec,
                                                      tcp::socket socket) {
                if (!ec) {
                    std::make_shared<HttpSession>(std::move(socket), peer_manager)->run();
                }
                do_accept();
            });
    };

    do_accept();
    ioc->run();
}
