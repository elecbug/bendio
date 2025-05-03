#pragma once

#include "async/thread.h"

namespace async {

    template<typename F, typename... Args>
    Thread::Thread(F&& f, Args&&... args) {
        _task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    }

    template<typename F, typename... Args>
    std::unique_ptr<Thread> Thread::make_unique(F&& f, Args&&... args) {
        return std::make_unique<Thread>(std::forward<F>(f), std::forward<Args>(args)...);
    }

    void Thread::start() {
        _t = std::thread([this]() {
            _task();
        });
    }

    void Thread::join() {
        if (_t.joinable()) {
            _t.join();
        }
    }

    void Thread::lock(std::mutex& mtx, std::function<void()> fn) {
        std::lock_guard<std::mutex> lock(mtx);
        fn();
    }

    Thread::~Thread() = default;
}
