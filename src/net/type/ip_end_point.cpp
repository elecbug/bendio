#include "net/type/ip_end_point.h"

#include <sstream>

namespace net {

    IPEndPoint::IPEndPoint() : _ip("0.0.0.0"), _port(0) {}

    IPEndPoint::IPEndPoint(const std::string& ip, int port) : _ip(ip), _port(port) {}

    IPEndPoint::IPEndPoint(const std::string& full) {
        auto pos = full.find(':');

        if (pos != std::string::npos) {
            _ip = full.substr(0, pos);
            _port = std::stoi(full.substr(pos + 1));
        } else {
            _ip = full;
            _port = 0;
        }
    }

    IPEndPoint::IPEndPoint(const IPEndPoint& other) : _ip(other._ip), _port(other._port) {}

    std::string IPEndPoint::get_ip() const {
        return _ip;
    }

    int IPEndPoint::get_port() const {
        return _port;
    }

    std::string IPEndPoint::to_string() const {
        return _ip + ":" + std::to_string(_port);
    }

}