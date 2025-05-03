#include "async/thread.h"
#include "async/task.h"
#include "net/tcp_server.h"
#include "net/tcp_client.h"
#include "net/type/bytes.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace net;
using namespace async;

void task_test() {
    auto task1 = async::Task<int>::run([] {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 123;
    });
    
    task1->cancel();
    if (!task1->is_done()) {
        std::cout << "Task is not done yet\n";
    }
    
    try {
        int result = task1->get();
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    auto task2 = async::Task<int>::run([] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return 10;
    });
    
    auto next = task2->then([](int x) {
        return x * 2;
    });
    
    if (next->get_with_timeout(std::chrono::milliseconds(200))) {
        std::cout << "Result: " << next->get() << std::endl;
    } else {
        std::cout << "Timeout!" << std::endl;
    }
}

void net_test() {
    Thread server_thread([] {
        TcpServer server = TcpServer();
        server.start(8888);

        TcpClient client = server.accept();

        bytes received = client.receive();
        std::cout << "[Server] Received: " << received.to_string() << std::endl;

        client.send(bytes("Echo: " + received.to_string()));
        client.close();
    });

    server_thread.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    TcpClient client = TcpClient();
    client.connect("127.0.0.1", 8888);
    client.send(bytes("Hello Server!"));

    bytes response = client.receive();
    std::cout << "[Client] Received: " << response.to_string() << std::endl;

    client.close();

    server_thread.join();
}

int main(int argc, char* argv[]) {
    std::cout << "Start \"" << argv[1] << "\" Test" << std::endl;
    
    if (strcmp(argv[1], "task") == 0) {
        task_test();
    } else if (strcmp(argv[1], "net") == 0) {
        net_test();
    }

    return 0;
}
