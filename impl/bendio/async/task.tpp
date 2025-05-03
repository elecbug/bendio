#pragma once

#include "bendio/async/task.h"

#include <exception>
#include <iostream>

namespace async {

    template<typename T> 
    template<typename F, typename... Args>
    Task<T>::Task(F&& f, Args&&... args) {
        auto bound_func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

        std::packaged_task<T()> task([this, bound_func]() {
            try {
                if (_canceled) {
                     throw std::runtime_error("Task was cancelled before execution");
                }

                T result = bound_func();
                _done = true;
                
                return result;
            } catch (...) {
                _done = true;
                
                throw;
            }
        });

        _fut = task.get_future();
        _t = std::thread(std::move(task));
    }

    template<typename T>
    template<typename F, typename... Args>
    std::unique_ptr<Task<T>> Task<T>::run(F&& f, Args&&... args) {
        return std::make_unique<Task<T>>(std::forward<F>(f), std::forward<Args>(args)...);
    }

    template<typename T>
    template<typename F>
    auto Task<T>::then(F&& f) -> std::unique_ptr<Task<decltype(f(std::declval<T>()))>> {
        using U = decltype(f(std::declval<T>()));

        return Task<U>::run([prev = this, func = std::forward<F>(f)] {
            return func(prev->get());
        });
    }

    template<typename T>
    template<typename Rep, typename Period>
    bool Task<T>::get_with_timeout(const std::chrono::duration<Rep, Period>& dur) {
        return _fut.wait_for(dur) == std::future_status::ready;
    }

    template<typename T>
    T Task<T>::get() {
        if (_t.joinable()) {
            _t.join();
        } 

        return _fut.get();
    }

    template<typename T>
    void Task<T>::join() {
        if (_t.joinable()) {
            _t.join();
        }
    }

    template<typename T>
    void Task<T>::cancel() {
        if (!_done && _fut.valid()) {
            _canceled = true;
        }
    }

    template<typename T>
    bool Task<T>::is_done() const {
        return _done;
    }

    template<typename T>
    Task<T>::~Task() {
        if (_t.joinable()) {
            _t.detach();
        }
    }

}