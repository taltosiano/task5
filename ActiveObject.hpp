#ifndef ACTIVE_OBJECT_HPP
#define ACTIVE_OBJECT_HPP

#include "ThreadSafeQueue.hpp"
#include <thread>
#include <functional>

template<typename T>
class ActiveObject {
public:
    ActiveObject(ThreadSafeQueue<T>* queue, std::function<void(T)> func);

    void start();

    void stop();

    ThreadSafeQueue<T>* getQueue();

private:
    ThreadSafeQueue<T>* queue_;
    std::function<void(T)> func_;
    bool running_;
    std::thread thread_;

    void run();
};

#endif