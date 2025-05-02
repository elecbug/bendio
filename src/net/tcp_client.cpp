#include "net/tcp_client.h"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

namespace net {

    TcpClient::TcpClient() : sock_fd(-1), port(0) {}

    TcpClient::TcpClient(int socket_fd) : sock_fd(socket_fd) {}

    void TcpClient::connect(const std::string& host, int port) {
        this->host = host;
        this->port = port;
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_fd < 0) {
            perror("socket");
            return;
        }

        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr);

        if (::connect(sock_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            perror("connect");
            ::close(sock_fd);
            sock_fd = -1;
            return;
        }
    }

    void TcpClient::send(type::bytes b) {
        ::send(sock_fd, b.data(), b.size(), 0);
    }

    type::bytes TcpClient::receive() {
        char buffer[1024];
        ssize_t len = ::recv(sock_fd, buffer, sizeof(buffer), 0);
        if (len <= 0) return type::bytes();
        return type::bytes(buffer, static_cast<size_t>(len));
    }

    void TcpClient::close() {
        if (sock_fd >= 0) {
            ::close(sock_fd);
            sock_fd = -1;
        }
    }

}
