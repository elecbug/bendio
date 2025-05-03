#include "net/type/ip_end_point.h"

#include <sstream>

namespace net {

    IPEndPoint::IPEndPoint() : ip_("0.0.0.0"), port_(0) {}

    IPEndPoint::IPEndPoint(const std::string& ip, int port) : ip_(ip), port_(port) {}

    IPEndPoint::IPEndPoint(const std::string& full) {
        auto pos = full.find(':');

        if (pos != std::string::npos) {
            ip_ = full.substr(0, pos);
            port_ = std::stoi(full.substr(pos + 1));
        } else {
            ip_ = full;
            port_ = 0;
        }
    }

    IPEndPoint::IPEndPoint(const IPEndPoint& other) : ip_(other.ip_), port_(other.port_) {}

    std::string IPEndPoint::get_ip() const {
        return ip_;
    }

    int IPEndPoint::get_port() const {
        return port_;
    }

    std::string IPEndPoint::to_string() const {
        return ip_ + ":" + std::to_string(port_);
    }

}