#include <iostream>
#include <exception>
#include <assert.h>

using usize = std::size_t;

template <typename T, usize MAX>
class ObjectLimit {
    public:
    static usize count;

    ObjectLimit() {
        if (count == MAX) {
            throw std::runtime_error{"Number of maximum amount of objects is reached! Terminating..."};
        }

        count++;
    }

    ObjectLimit(const ObjectLimit&) {
        if (count == MAX) {
            throw std::runtime_error{"Number of maximum amount of objects is reached! Terminating..."};
        }

        count++;
    }

    ~ObjectLimit() {
        count--;
    }
};

class A : ObjectLimit<A, 5> {
    public:
    A() {
        std::cout << "Object created" << std::endl;
    }

    A(const A&) {
        std::cout << "object copied from ....." << std::endl;
    }
};

// Declaring static variable
template <typename T, usize N>
usize ObjectLimit<T, N>::count;

int main() try {
    A a1;
    A a2;
    A a4;
    A a5;
    A a6{a5};

    A a7;
} catch (...) {}
