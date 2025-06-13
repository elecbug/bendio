#pragma once

#include <string>

namespace net {
    // Represents an IP endpoint (IP address + port)
    class IPEndPoint {
    public:
        // Default constructor (empty IP and port = 0)
        IPEndPoint();

        // Constructor from IP string and port number
        IPEndPoint(const std::string& ip, int port);

        // Constructor from full string format: "IP:port"
        IPEndPoint(const std::string& full);

        // Copy constructor
        IPEndPoint(const IPEndPoint& other);

        // Get the IP address
        std::string get_ip() const;

        // Get the port number
        int get_port() const;

        // Get the full string representation "IP:port"
        std::string to_string() const;

    private:
        std::string _ip;  // IP address
        int _port;        // Port number
    };
}
