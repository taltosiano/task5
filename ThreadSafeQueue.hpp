#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue();

    void enqueue(T item);

    T dequeue();

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
};

#endif