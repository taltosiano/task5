#include "ActiveObject.hpp"

template<typename T>
ActiveObject<T>::ActiveObject(ThreadSafeQueue<T>* queue, std::function<void(T)> func) :
    queue_(queue), func_(func), running_(false) {}

template<typename T>
void ActiveObject<T>::start() {
    running_ = true;
    thread_ = std::thread(&ActiveObject::run, this);
}

template<typename T>
void ActiveObject<T>::stop() {
    running_ = false;
    thread_.join();
}

template<typename T>
ThreadSafeQueue<T>* ActiveObject<T>::getQueue() {
    return queue_;
}

template<typename T>
void ActiveObject<T>::run() {
    while (running_) {
        T task = queue_->dequeue();
        func_(task);
    }
}

template class ActiveObject<int>;