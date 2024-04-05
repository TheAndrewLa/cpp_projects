#include "library/scoped_ptr.hpp"
#include <iostream>
#include <assert.h>

int counter;

class mock {
    public:
    mock() = default;
    mock(const mock&) = default;
    mock(mock&&) = default;

    ~mock() {
        counter++;
    }

    mock& operator=(const mock&) = default;
    mock& operator=(mock&&) = default;
};

int main(int, char**) {
    {
        counter = 0;

        ScopedPtrCopy<mock> ptr1{new mock{}};
        ScopedPtrCopy<mock> ptr2 = ptr1;
        ScopedPtrCopy<mock> ptr3 = std::move(ptr1);
        ScopedPtrCopy<mock> ptr4 = ptr2;
    }

    assert(counter == 3);

    {
        counter = 0;
        
        ScopedPtrMove<mock> ptr1{new mock{}};
        ScopedPtrMove<mock> ptr2{std::move(ptr1)};
        ScopedPtrMove<mock> ptr3{std::move(ptr2)};

        // Will not be compiled, copy ctor is deleted
        // ScopedPtrMove<mock> ptr4{ptr3};
    }

    assert(counter == 1);

    return 0;
}
