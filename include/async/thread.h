#pragma once
#include <thread>
#include <functional>
#include <mutex>
#include <memory>

namespace async {

    class Thread {
    public:
        template<typename F, typename... Args> Thread(F&& f, Args&&... args);
        
        template<typename F, typename... Args> static std::unique_ptr<Thread> make_unique(F&& f, Args&&... args);
        static void lock(std::mutex& mtx, std::function<void()> fn);

        void start();
        void join();

        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;

        Thread(Thread&&) = default;
        Thread& operator=(Thread&&) = default;

        ~Thread();

    private:
        std::function<void()> task;
        std::thread t;
    };

}

#include "async/thread.tpp"