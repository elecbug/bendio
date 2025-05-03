#include "bendio/async.h"

#include <iostream>
#include <unistd.h>

using async::Thread;

void func(long long int x, long long int y, long long int* sum) {
    for (long long int i = x; i <= y; i++) {
        *sum += i;
    }
}

void lock_func(std::mutex* mtx, long long int x, long long int y, long long int* sum) {
    Thread::lock(*mtx, [x, y, sum]() {
        for (long long int i = x; i <= y; i++) {
            *sum += i;
        }
    });
}

void unusing_join() {
    long long int* sum = new long long int(0);

    Thread* t = new Thread(func, 1, 100, sum);
    // Thread t2 = t1;
    // Thread t3 = Thread(t1);

    t->start();
    
    std::cout << "Unusing join(): " << *sum << std::endl;

    t->join();

    delete sum;
    delete t;
}

void using_join() {
    long long int* sum = new long long int(0);

    Thread* t = new Thread(func, 1, 100, sum);
    
    t->start();
    t->join();
    
    std::cout << "Using join(): " << *sum << std::endl;
    
    delete sum;
    delete t;
}

void unusing_lock() {
    long long int* sum = new long long int(0);

    Thread* t1 = new Thread(func, 1, 100000, sum);
    Thread* t2 = new Thread(func, 1, 100000, sum);
    
    t1->start();
    t2->start();

    t1->join();
    t2->join();
    
    std::cout << "Unusing lock(): " << *sum << std::endl;
    
    delete sum;
    delete t1;
    delete t2;
}

void using_lock() {
    long long int* sum = new long long int(0);
    std::mutex mtx = std::mutex();

    Thread* t1 = new Thread(lock_func, &mtx, 1, 100000, sum);
    Thread* t2 = new Thread(lock_func, &mtx, 1, 100000, sum);
    
    t1->start();
    t2->start();

    t1->join();
    t2->join();
    
    std::cout << "Using lock(): " << *sum << std::endl;
    
    delete sum;
    delete t1;
    delete t2;
}

void thread_test() {
    unusing_join();
    using_join();
    unusing_lock();
    using_lock();
}