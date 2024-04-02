#include "library/scoped_ptr.hpp"
#include <iostream>

class A {
    public:
    int pi = 3;
    
    A() = default;

    ~A() {
        std::cout << "Hello World!" << '\n';
    }
};

int main(int, char**) {
    ScopedPtrCopy<A> a{new A()};
    (*a).pi = 34;
}
