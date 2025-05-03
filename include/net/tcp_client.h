#pragma once

#include "net/type/bytes.h"
#include "net/type/ip_end_point.h"

#include <string>

namespace net {

    class TcpClient {
    public:
        TcpClient();
        TcpClient(int socket_fd);
    
        void connect(const std::string& host, int port);
        void connect(const net::IPEndPoint ep);

        void send(net::bytes);
        
        net::bytes receive();
    
        void close();
    
    private:
        int sock_fd;
        std::string host;
        int port;

        void connect();
    };
        
}
