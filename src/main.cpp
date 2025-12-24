#include "server/http_server.hpp"

int main() {
    const auto server = HttpServer(8080);

    server.run();

    return 0;
}
