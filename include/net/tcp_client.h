#pragma once
#include <string>
#include "type/bytes.h"

namespace net {

    class TcpClient {
    public:
        TcpClient();
        TcpClient(int socket_fd);
    
        void connect(const std::string& host, int port);
        void send(type::bytes);
        type::bytes receive();
    
        void close();
    
    private:
        int sock_fd;
        std::string host;
        int port;
    };
        
}
