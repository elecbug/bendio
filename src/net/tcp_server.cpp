#include "net/tcp_client.h"
#include "net/tcp_server.h"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace net {

    TcpServer::TcpServer() : server_fd(-1), port(0) {}

    void TcpServer::start(int port) {
        this->port = port;
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) {
            perror("socket");
            return;
        }

        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);

        int opt = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            perror("bind");
            ::close(server_fd);
            server_fd = -1;
            return;
        }

        if (listen(server_fd, 5) < 0) {
            perror("listen");
            ::close(server_fd);
            server_fd = -1;
            return;
        }

        std::cout << "Server started on port " << port << std::endl;
    }

    TcpClient TcpServer::accept() {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_fd = ::accept(server_fd, (sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept");
            return TcpClient(-1);
        }
        return TcpClient(client_fd);
    }

}
