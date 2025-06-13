#pragma once

#include "bendio/async/task.h"
#include "bendio/net/type/bytes.h"
#include "bendio/net/type/ip_end_point.h"

#include <string>

namespace net {
    // A simple TCP client class for connecting to a server and sending/receiving data
    class TcpClient {
    public:
        // Default constructor
        TcpClient();

        // Construct with an existing socket file descriptor (e.g. accepted from a server)
        TcpClient(int socket_fd);

        // Connect to a remote host and port (e.g. "127.0.0.1", 8000)
        void connect(const std::string& host, int port);

        // Connect to a remote endpoint using IPEndPoint object
        void connect(const net::IPEndPoint ep);

        // Asynchronously connect to a remote host and port
        // Returns a Task<void> that completes once the connection is established
        std::unique_ptr<async::Task<void>> connect_async(const std::string& host, int port);

        // Asynchronously connect to a remote endpoint represented by IPEndPoint
        // Returns a Task<void> that completes once the connection is established
        std::unique_ptr<async::Task<void>> connect_async(const net::IPEndPoint ep);

        // Send a byte buffer to the connected server
        void send(net::bytes);

        // Receive a byte buffer from the connected server
        net::bytes receive();

        // Asynchronously send a byte buffer to the connected server
        // Returns a Task<void> that completes when the send operation finishes
        std::unique_ptr<async::Task<void>> send_async(net::bytes);

        // Asynchronously receive a byte buffer from the connected server
        // Returns a Task<net::bytes> containing the received data
        std::unique_ptr<async::Task<net::bytes>> receive_async();

        // Close the connection
        void close();

    private:
        int _sock_fd;         // Socket file descriptor
        std::string _host;    // Host IP or domain
        int _port;            // Port number

        // Internal connection logic (used by both connect overloads)
        void inner_connect();
    };
}
