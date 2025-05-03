#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <thread>

namespace async {

    // High-level wrapper around std::thread with task binding and locking utilities
    class Thread {
    public:
        // Constructor that binds a function with its arguments into a callable task
        template<typename F, typename... Args>
        Thread(F&& f, Args&&... args);

        // Deleted copy constructor to prevent copying
        Thread(const Thread&) = delete;

        // Defaulted move constructor
        Thread(Thread&&) = default;

        // Destructor: detaches the thread if still joinable
        ~Thread();

        // Factory method to create a Thread with unique_ptr
        template<typename F, typename... Args> 
        static std::unique_ptr<Thread> make_unique(F&& f, Args&&... args);

        // Static method to execute a function while holding a lock
        static void lock(std::mutex& mtx, std::function<void()> fn);

        // Starts the internal thread with the bound task
        void start();

        // Joins the thread if it is joinable
        void join();

        // Deleted copy assignment operator to prevent copying
        Thread& operator=(const Thread&) = delete;

        // Defaulted move assignment operator
        Thread& operator=(Thread&&) = default;

    private:
        std::function<void()> _task;  // Bound task to be executed in thread
        std::thread _t;               // Internal thread object
    };

}

// Include template definitions
#include "async/thread.tpp"
