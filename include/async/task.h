#pragma once

#include <atomic>
#include <chrono>
#include <future>
#include <functional>
#include <memory>
#include <thread>

namespace async {

    // Task for returning a value of type T
    template<typename T> 
    class Task {
    public:
        // Constructor: wraps a function with arguments into a task
        template<typename F, typename... Args> 
        Task(F&& f, Args&&... args);

        // Destructor: ensures thread is detached if not joined
        ~Task();

        // Factory method to create and start the task
        template<typename F, typename... Args> 
        static std::unique_ptr<Task<T>> run(F&& f, Args&&... args);

        // Blocking call to get the result; joins the thread if needed
        T get();

        // Check if the task is ready within given duration
        template<typename Rep, typename Period> 
        bool get_with_timeout(const std::chrono::duration<Rep, Period>& dur);

        // Wait for the thread to finish execution
        void join();
        
        // Mark the task as canceled (checked before execution starts)
        void cancel();

        // Chain another task to run after this one completes
        template<typename F> 
        auto then(F&& f) -> std::unique_ptr<Task<decltype(f(std::declval<T>()))>>;

        // Check if the task has completed
        bool is_done() const;

    private:
        std::thread _t;                     // Background thread running the task
        std::future<T> _fut;                // Future object to get result
        std::atomic<bool> _canceled{false}; // Indicates if task was canceled
        std::atomic<bool> _done{false};     // Indicates if task finished
    };

    // Specialization for void return type
    template<>
    class Task<void> {
    public:
        // Constructor: wraps a void-returning function into a task
        template<typename F, typename... Args>
        Task(F&& f, Args&&... args);

        // Destructor: ensures thread is detached if not joined
        ~Task();

        // Factory method to create and start the task
        template<typename F, typename... Args>
        static std::unique_ptr<Task<void>> run(F&& f, Args&&... args);
        
        // Blocking call to wait for completion
        void get();
        
        // Check if the task is ready within given duration
        template<typename Rep, typename Period>
        bool get_with_timeout(const std::chrono::duration<Rep, Period>& dur);

        // Wait for the thread to finish execution
        void join();

        // Mark the task as canceled (checked before execution starts)
        void cancel();
        
        // Chain another task to run after this one completes
        template<typename F>
        auto then(F&& f) -> std::unique_ptr<Task<decltype(f())>>;

        // Check if the task has completed
        bool is_done() const;

    private:
        std::thread _t;                     // Background thread running the task
        std::future<void> _fut;             // Future object for synchronization
        std::atomic<bool> _canceled{false}; // Indicates if task was canceled
        std::atomic<bool> _done{false};     // Indicates if task finished
    };

}

// Include implementation of template functions
#include "async/task.tpp"
#include "async/task_void.tpp"
