#pragma once

#include "async/task.h"

#include <exception>
#include <iostream>

namespace async {

    template<typename F, typename... Args>
    Task<void>::Task(F&& f, Args&&... args) {
        auto bound_func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

        std::packaged_task<void()> task([this, bound_func]() {
            try {
                if (canceled) {
                    throw std::runtime_error("Task was cancelled before execution");
                }
                
                bound_func();
                done = true;
            } catch (...) {
                done = true;
                
                throw;
            }
        });

        fut = task.get_future();
        t = std::thread(std::move(task));
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
        return fut.wait_for(dur) == std::future_status::ready;
    }

    void Task<void>::get() {
        if (t.joinable()) {
            t.join();
        }
        
        fut.get();
    }

    void Task<void>::join() {
        if (t.joinable()) {
            t.join();
        }
    }

    void Task<void>::cancel() {
        if (!done && fut.valid()) {
            canceled = true;
        }
    }

    bool Task<void>::is_done() const {
        return done;
    }

    Task<void>::~Task() {
        if (t.joinable()){
            t.detach();
        } 
    }

}