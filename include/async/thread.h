#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <thread>

namespace async {

    class Thread {
    public:
        template<typename F, typename... Args>
        Thread(F&& f, Args&&... args);
        Thread(const Thread&) = delete;
        Thread(Thread&&) = default;
        
        ~Thread();

        template<typename F, typename... Args> 
        static std::unique_ptr<Thread> make_unique(F&& f, Args&&... args);
        
        static void lock(std::mutex& mtx, std::function<void()> fn);

        void start();

        void join();

        Thread& operator=(const Thread&) = delete;
        Thread& operator=(Thread&&) = default;

    private:
        std::function<void()> task;
        std::thread t;
    };

}

#include "async/thread.tpp"