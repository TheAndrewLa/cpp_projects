#include "library/scoped_ptr.hpp"
#include <iostream>

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
    counter = 0;

    {
        ScopedPtrCopy<mock> ptr1{new mock{}};
        ScopedPtrCopy<mock> ptr2 = ptr1;
        ScopedPtrCopy<mock> ptr3 = std::move(ptr1);
        ScopedPtrCopy<mock> ptr4 = ptr2;

        std::cout << counter << " -> ";
    }

    std::cout << counter << std::endl;

    counter = 0;

    {
        ScopedPtrMove<mock> ptr1{new mock{}};
        ScopedPtrMove<mock> ptr2{std::move(ptr1)};
        ScopedPtrMove<mock> ptr3{std::move(ptr2)};

        std::cout << counter << " -> ";
    }

    std::cout << counter << std::endl;

    return 0;
}
