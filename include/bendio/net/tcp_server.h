#pragma once

#include "bendio/net/tcp_client.h"

namespace net {
    // A simple TCP server class that listens for and accepts client connections
    class TcpServer {
    public:
        // Default constructor
        TcpServer();

        // Start the server and bind to the given port
        void start(int port);

        // Accept an incoming client connection
        // Returns a TcpClient object representing the connected client
        TcpClient accept();

        // Accept an incoming client connection asynchronously
        // Returns a Task<TcpClient> that completes once a client is connected
        std::unique_ptr<async::Task<TcpClient>> accept_async();

    private:
        int _server_fd;  // File descriptor for the server socket
        int _port;       // Listening port
    };
}
