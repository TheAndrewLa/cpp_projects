#pragma once

#include <string>
#include <iostream>

class MockObject {
    public:
    MockObject() = delete;
    MockObject(int a) : x_(a) {}

    MockObject(const MockObject& ref) : x_(ref.x_) {
        std::cout << "Copy ctor!" << '\n';
    }

    MockObject(MockObject&& ref) : x_(ref.x_) {
        std::cout << "Move ctor!" << '\n';
    }

    ~MockObject() {
        std::cout << "Dtor!" << '\n';
    }

    int x() const {
        return x_;
    }

    private:
    int x_;
};
