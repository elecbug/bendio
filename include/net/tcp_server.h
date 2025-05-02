#pragma once
#include "tcp_client.h"

namespace net {

    class TcpServer {
    public:
        TcpServer();
        void start(int port);
        TcpClient accept();
    
    private:
        int server_fd;
        int port;
    };
        
}
