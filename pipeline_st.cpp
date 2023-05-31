#include "isPrime.hpp"
#include "ThreadSafeQueue.hpp"
#include "ActiveObject.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

void generateNumbers(ThreadSafeQueue<int>* queue, int n);

void checkPrimeAndAdd11(ThreadSafeQueue<int>* inputQueue, ThreadSafeQueue<int>* outputQueue);

void checkPrimeAndSubtract13(ThreadSafeQueue<int>* inputQueue, ThreadSafeQueue<int>* outputQueue);

void printAndAdd2(ThreadSafeQueue<int>* queue);

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " N [seed]" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);

    std::srand(argc > 2 ? std::atoi(argv[2]) : std::time(nullptr));

    ThreadSafeQueue<int> queue1;
    ThreadSafeQueue<int> queue2;
    ThreadSafeQueue<int> queue3;
    ThreadSafeQueue<int> queue4;

    ActiveObject<int> ao1(&queue1, [&queue1, &queue2, n](int) { generateNumbers(&queue1, n); });
    //ActiveObject<int> ao2(&queue1, &queue2, [&queue1, &queue2](ThreadSafeQueue<int>* inputQueue, ThreadSafeQueue<int>* outputQueue) { checkPrimeAndAdd11(inputQueue, outputQueue); });
ActiveObject<int> ao2(&queue2, [&queue1, &queue2](int) { checkPrimeAndAdd11(&queue1, &queue2); });

// ActiveObject<int> ao3(&queue3, [&queue3,&queue2](ThreadSafeQueue<int>* in) { checkPrimeAndSubtract13(in, &queue3); });
std::function<void(int)> func = [&queue3,&queue2](ThreadSafeQueue<int>* in) { checkPrimeAndSubtract13(in, &queue3); };
ActiveObject<int> ao3(&queue3, func);

std::function<void(int)> func1 = [](ThreadSafeQueue<int>* queue) { printAndAdd2(queue); };
ActiveObject<int> ao4(&queue3, func1);

// void checkPrimeAndSubtract13_wrapper(ThreadSafeQueue<int>* in, ThreadSafeQueue<int>* out) {
//     checkPrimeAndSubtract13(in, out);
// }

// ActiveObject<int, decltype(checkPrimeAndSubtract13_wrapper)*> ao3(&queue3, checkPrimeAndSubtract13_wrapper);

// void printAndAdd2_wrapper(ThreadSafeQueue<int>* queue) {
//     printAndAdd2(queue);
// }

// ActiveObject<int, decltype(printAndAdd2_wrapper)*> ao4(&queue3, printAndAdd2_wrapper);

    ao1.start();
    ao2.start();
    ao3.start();
    ao4.start();

    ao1.getQueue()->enqueue(n);

    ao1.stop();
    ao2.stop();
    ao3.stop();
    ao4.stop();

    return 0;
}

void generateNumbers(ThreadSafeQueue<int>* queue, int n) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < n; i++) {
        int number = std::rand() % 1000000;
        queue->enqueue(number);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void checkPrimeAndAdd11(ThreadSafeQueue<int>* inputQueue, ThreadSafeQueue<int>* outputQueue) {
    while (true) {
        int number = inputQueue->dequeue();
        std::cout << number << std::endl;
        bool prime = isPrime(number);
        std::cout << std::boolalpha << prime << std::endl;
        int newNumber = number + 11;
        outputQueue->enqueue(newNumber);
    }
}

void checkPrimeAndSubtract13(ThreadSafeQueue<int>* inputQueue, ThreadSafeQueue<int>* outputQueue) {
    while (true) {
        int number = inputQueue->dequeue();
        std::cout << number << std::endl;
        bool prime = isPrime(number);
        std::cout << std::boolalpha << prime << std::endl;
        int newNumber = number - 13;
        outputQueue->enqueue(newNumber);
    }
}

void printAndAdd2(ThreadSafeQueue<int>* queue) {
    while (true) {
        int number = queue->dequeue();
        std::cout << number << std::endl;
        number += 2;
        std::cout << number << std::endl;
    }
}