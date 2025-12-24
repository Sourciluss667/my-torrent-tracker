cmake_minimum_required(VERSION 4.1)
project(my_torrent_tracker)

set(CMAKE_CXX_STANDARD 26)

# SPDLog
find_package(spdlog REQUIRED)

# Boost (http lib)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.90.0 REQUIRED COMPONENTS filesystem url)

add_executable(my_torrent_tracker src/main.cpp
        src/server/http_server.cpp
        src/server/http_server.hpp
        src/server/http_session.cpp
        src/server/http_session.hpp
        src/server/http_parser.cpp
        src/server/http_parser.hpp
        src/tools/hexify.cpp
        src/tools/hexify.hpp
        src/peer/peer_manager.cpp
        src/peer/peer_manager.hpp
        src/bencode/bencode.cpp
        src/bencode/bencode.hpp)

target_link_libraries(my_torrent_tracker PRIVATE
        spdlog::spdlog
        Boost::boost
        Boost::url
)
