#include "ThreadSafeQueue.hpp"

template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue() {}

template<typename T>
void ThreadSafeQueue<T>::enqueue(T item) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(item);
    cv_.notify_one();
}

template<typename T>
T ThreadSafeQueue<T>::dequeue() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return !queue_.empty(); });
    T item = queue_.front();
    queue_.pop();
    return item;
}

template class ThreadSafeQueue<int>;