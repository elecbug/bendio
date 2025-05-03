#pragma once

#include <string>

namespace net {

    class IPEndPoint {
    public:
        IPEndPoint();
        IPEndPoint(const std::string& ip, int port);
        IPEndPoint(const std::string& full);
        IPEndPoint(const IPEndPoint& other);

        std::string get_ip() const;

        int get_port() const;
        
        std::string to_string() const;

    private:
        std::string ip_;
        int port_;
    };

}
