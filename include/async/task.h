#pragma once

#include <atomic>
#include <chrono>
#include <future>
#include <functional>
#include <memory>
#include <thread>

namespace async {

    template<typename T> class Task {
    public:
        template<typename F, typename... Args> Task(F&& f, Args&&... args);

        template<typename F, typename... Args> static std::unique_ptr<Task<T>> run(F&& f, Args&&... args);

        template<typename F> auto then(F&& f) -> std::unique_ptr<Task<decltype(f(std::declval<T>()))>>;

        template<typename Rep, typename Period> bool get_with_timeout(const std::chrono::duration<Rep, Period>& dur);

        T get();
        void join();
        void cancel();
        bool is_done() const;
        
        ~Task();

    private:
        std::thread t;
        std::future<T> fut;
        std::atomic<bool> canceled{false};
        std::atomic<bool> done{false};
    };

    template<>
    class Task<void> {
    public:
        template<typename F, typename... Args>
        Task(F&& f, Args&&... args);

        template<typename F, typename... Args>
        static std::unique_ptr<Task<void>> run(F&& f, Args&&... args);

        template<typename F>
        auto then(F&& f) -> std::unique_ptr<Task<decltype(f())>>;

        template<typename Rep, typename Period>
        bool get_with_timeout(const std::chrono::duration<Rep, Period>& dur);

        void get();
        void join();
        void cancel();
        bool is_done() const;
        ~Task();

    private:
        std::thread t;
        std::future<void> fut;
        std::atomic<bool> canceled{false};
        std::atomic<bool> done{false};
    };

}

#include "task.tpp"