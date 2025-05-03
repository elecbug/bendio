#include "task.cpp"
#include "thread.cpp"
#include "net.cpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>

int main(int argc, char* argv[]) {
    std::cout << "Start \"" << argv[1] << "\" Test" << std::endl;

    if (strcmp(argv[1], "task") == 0) {
        task_test();
    } else if (strcmp(argv[1], "thread") == 0) {
        thread_test();
    } else if (strcmp(argv[1], "net") == 0) {
        net_test();
    } else {
        std::cout << "Invalid test case" << std::endl;
    }

    return 0;
}