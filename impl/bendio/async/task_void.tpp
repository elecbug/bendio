#pragma once

#include "bendio/async/task.h"

#include <exception>
#include <iostream>

namespace async {

    template<typename F, typename... Args>
    Task<void>::Task(F&& f, Args&&... args) {
        auto bound_func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

        std::packaged_task<void()> task([this, bound_func]() {
            try {
                if (_canceled) {
                    throw std::runtime_error("Task was cancelled before execution");
                }
                
                bound_func();
                _done = true;
            } catch (...) {
                _done = true;
                
                throw;
            }
        });

        _fut = task.get_future();
        _t = std::thread(std::move(task));
    }

    template<typename F, typename... Args>
    std::unique_ptr<Task<void>> Task<void>::run(F&& f, Args&&... args) {
        return std::make_unique<Task<void>>(std::forward<F>(f), std::forward<Args>(args)...);
    }

    template<typename F>
    auto Task<void>::then(F&& f) -> std::unique_ptr<Task<decltype(f())>> {
        using U = decltype(f());

        return Task<U>::run([prev = this, func = std::forward<F>(f)] {
            prev->get();

            return func();
        });
    }

    template<typename Rep, typename Period>
    bool Task<void>::get_with_timeout(const std::chrono::duration<Rep, Period>& dur) {
        return _fut.wait_for(dur) == std::future_status::ready;
    }

    void Task<void>::get() {
        if (_t.joinable()) {
            _t.join();
        }
        
        _fut.get();
    }

    void Task<void>::join() {
        if (_t.joinable()) {
            _t.join();
        }
    }

    void Task<void>::cancel() {
        if (!_done && _fut.valid()) {
            _canceled = true;
        }
    }

    bool Task<void>::is_done() const {
        return _done;
    }

    Task<void>::~Task() {
        if (_t.joinable()){
            _t.detach();
        } 
    }

}