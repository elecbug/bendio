#include "bendio/net/tcp_client.h"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

namespace net {

    TcpClient::TcpClient() : _sock_fd(-1), _port(0) {}

    TcpClient::TcpClient(int socket_fd) : _sock_fd(socket_fd) {}

    void TcpClient::connect(const std::string& host, int port) {
        _host = host;
        _port = port;
        
        inner_connect();
    }

    void TcpClient::connect(const net::IPEndPoint ep) {
        _host = ep.get_ip();
        _port = ep.get_port();

        inner_connect();
    }

    std::unique_ptr<async::Task<void>> TcpClient::connect_async(const std::string& host, int port) {
        return async::Task<void>::run([this, host, port] {
            this->connect(host, port);
        });        
    }

    std::unique_ptr<async::Task<void>> TcpClient::connect_async(const net::IPEndPoint ep) {
        return async::Task<void>::run([this, ep] {
            this->connect(ep);
        });
    }

    void TcpClient::send(net::bytes b) {
        ::send(_sock_fd, b.data(), b.size(), 0);
    }

    net::bytes TcpClient::receive() {
        char buffer[1024];
        ssize_t len = ::recv(_sock_fd, buffer, sizeof(buffer), 0);

        if (len <= 0){
            return net::bytes();
        } else {
            return net::bytes(buffer, static_cast<size_t>(len));
        }
    }

    std::unique_ptr<async::Task<void>> TcpClient::send_async(net::bytes b) {
        return async::Task<void>::run([this, b = std::move(b)]() {
            this->send(std::move(b));
        });
    }

    std::unique_ptr<async::Task<net::bytes>> TcpClient::receive_async() {
        return async::Task<net::bytes>::run([this]() {
            return this->receive();
        });
    }

    void TcpClient::close() {
        if (_sock_fd >= 0) {
            ::close(_sock_fd);

            _sock_fd = -1;
        }
    }

    void TcpClient::inner_connect() {
        _sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        
        if (_sock_fd < 0) {
            perror("socket");

            return;
        }

        sockaddr_in server_addr{};

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(_port);
        
        inet_pton(AF_INET, _host.c_str(), &server_addr.sin_addr);

        if (::connect(_sock_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            perror("connect");
            ::close(_sock_fd);

            _sock_fd = -1;
            
            return;
        }
    }
}
