#include <functional>
#include <stdexcept>

#include <cstddef>
#include <cstdint>
#include <cstring>

#include <iostream>
#include <string>
#include <tuple>

#include "mock.hpp"

using uint8 = uint8_t;

using usize = std::size_t;
using isize = std::ptrdiff_t;

using std::string;

template <usize Size, std::copyable... Args>
void allocate(void* memory, const Args&... args) requires((... + sizeof(Args)) <= Size) {   
    if (memory == nullptr)
        throw std::invalid_argument{"Invalid pointer!\n"};

    uint8* ptr = reinterpret_cast<uint8*>(memory);
    ((new (ptr) Args{args}, ptr += sizeof(args)), ...);
}

template <std::destructible... Types>
class Tuple {
    public:
    Tuple() = delete;

    template <typename... Args>
    Tuple(Args&&... args) requires((sizeof...(Args) == sizeof...(Types))) {
        memory_ = &arr_[0];
        uint8* ptr = memory_;

        ((new (ptr) Types{std::forward<Args>(args)}, ptr += sizeof(Types)), ...);
    }

    Tuple(const Tuple& tuple) requires((... && std::is_copy_constructible_v<Types>)) {
        usize i = 0;

        memory_ = &arr_[0];
        uint8* ptr = memory_;

        ((new (ptr) Types{tuple.Get<Types>(i)}, ptr += sizeof(Types), i++), ...);
    }

    Tuple(Tuple&& tuple) {
        // Just grabbing memory withou calling move ctor
        memory_ = tuple.memory_;
        tuple.memory_ = nullptr;
    }

    ~Tuple() {
        uint8* ptr = memory_;
        ((((*reinterpret_cast<Types*>(ptr)).~Types()), ptr += sizeof(Types)), ...);
    }

    Tuple& operator=(const Tuple& tuple) requires((... && std::is_copy_constructible_v<Types>)) {
        usize i = 0;
        (((delete (reinterpret_cast<Types*>(i))), i++), ...);

        usize size = (... + sizeof(Types));
        i = 0;

        memory_ = new uint8[size];
        uint8* ptr = memory_;

        ((new (ptr) Types{tuple.Get<Types>(i)}, ptr += sizeof(Types), i++), ...);

        return *this;
    }

    Tuple& operator=(Tuple&& tuple) {
        uint8* ptr = memory_;
        ((((*reinterpret_cast<Types*>(ptr)).~Types()), ptr += sizeof(Types)), ...);

        // Just grabbing memory without calling move ctor
        memory_ = tuple.memory_;
        tuple.memory_ = nullptr;

        return *this;
    }

    template <typename T>
    T& Get(usize index) {
        return *reinterpret_cast<T*>(get_arg(index));
    }

    template <typename T>
    const T& Get(usize index) const {
        return *reinterpret_cast<const T*>(get_arg(index));
    }

    private:

    uint8* get_arg(usize index) const {
        uint8* found;
        uint8* ptr = memory_;

        usize i = 0;
        (((found = ptr), ptr += sizeof(Types) * static_cast<usize>(i < index), i += 1), ...);

        return found;
    }

    uint8 arr_[(... + sizeof(Types))];
    uint8* memory_{nullptr};
};

int main(int, char**) {

#if 1
    int* args = new int[5];
    allocate<20>(args, 12, 14, 16, 18, 20);
    
    for (usize i = 0; i < 5; i++)
        std::cout << args[i] << "\n";

    delete [] args;
#endif

#if 1
    MockObject a{12};
    MockObject b{13};
    MockObject c{14};

    std::cout << "\nCREATING OF TUPLE BELOW!\n";

    Tuple<MockObject, MockObject, MockObject, MockObject, MockObject>
    tuple{MockObject{11}, a, std::move(b), c, MockObject{15}};

    std::cout << tuple.Get<MockObject>(0).x() << ' ';
    std::cout << tuple.Get<MockObject>(1).x() << ' ';
    std::cout << tuple.Get<MockObject>(2).x() << ' ';
    std::cout << tuple.Get<MockObject>(3).x() << ' ';
    std::cout << tuple.Get<MockObject>(4).x() << ' ';

    //std::cout << "\nCOPYING OF TUPLE BELOW!\n";
//
    //Tuple<MockObject, MockObject, MockObject, MockObject, MockObject>
    //tuple2{tuple};
//
    //std::cout << tuple2.Get<MockObject>(0).x() << ' ';
    //std::cout << tuple2.Get<MockObject>(1).x() << ' ';
    //std::cout << tuple2.Get<MockObject>(2).x() << ' ';
    //std::cout << tuple2.Get<MockObject>(3).x() << ' ';
    //std::cout << tuple2.Get<MockObject>(4).x() << ' ';

#endif

#if 0
    string world{"world"};
    Tuple<int, int, string, string> tuple{12, 13, "Hello", world};

    std::cout << tuple.Get<int>(0) << ' ';
    std::cout << tuple.Get<int>(1) << ' ';
    std::cout << tuple.Get<string>(2) << ' ';
    std::cout << tuple.Get<string>(3) << ' ';

#endif

    return 0;
}
