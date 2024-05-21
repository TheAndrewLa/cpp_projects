#include <functional>
#include <stdexcept>

#include <cstddef>
#include <cstring>

#include <iostream>
#include <string>
#include <tuple>

using uint8 = uint8_t;

using usize = std::size_t;
using isize = std::ptrdiff_t;

template <usize Size, std::copyable... Args>
void allocate(void* memory, const Args&... args) {   
    if (memory == nullptr)
        throw std::invalid_argument{"Invalid pointer!\n"};

    if constexpr ((... + sizeof(Args)) > Size) {
        throw std::invalid_argument{"Not enough memory!\n"};
    }
    else {
        uint8* ptr = reinterpret_cast<uint8*>(memory);
        ((new (ptr) Args{args}, ptr += sizeof(args)), ...);
    }
}

template <typename... Types>
class Tuple {
    public:
    Tuple() = delete;

    template <typename... Args> // Use perfect forwarding here
    Tuple(Args&&... args) {
        static_assert(sizeof...(Args) == sizeof...(Types));
        static_assert((... && std::same_as<std::remove_reference_t<Args>, Types>));

        memory_ = new uint8[(... + sizeof(Types))];
        uint8* ptr = memory_;

        ((new (ptr) Types{std::forward<Args>(args)}, ptr += sizeof(Types)), ...);
    }

    Tuple(const Tuple& tuple) requires(... && std::copyable<Types>) {
        usize size = (... + sizeof(Types));

        memory_ = new uint8[size];
        std::memcpy(memory_, tuple.memory_, size);

        /// @todo copy elements with copy ctor
    }

    Tuple(Tuple&& tuple) {
        memory_ = tuple.memory_;
        tuple.memory_ = nullptr;
    }

    ~Tuple() {
        delete [] memory_;
    }

    Tuple& operator=(const Tuple& tuple) {
        delete [] memory_;

        usize size = (... + sizeof(Types));

        memory_ = new uint8[size];
        std::memcpy(memory_, tuple.memory_, size);

        return *this;
    }

    Tuple& operator=(Tuple&& tuple) {
        delete [] memory_;

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

    uint8* get_arg(usize index) {
        uint8* found;
        uint8* ptr = memory_;

        usize i = 0;
        (((found = ptr), ptr += sizeof(Types) * static_cast<usize>(i < index), i += 1), ...);

        return found;
    }

    uint8* memory_{nullptr};
};

int main(int, char**) {
    int* args = new int[5];
    allocate<20>(args, 12, 14, 16, 18, 20);
    
    for (usize i = 0; i < 5; i++)
        std::cout << args[i] << "\n";

    delete [] args;

    Tuple<int, int, std::string, int> tuple{12, 13, std::string{"Hello World!"}, 14};

    std::cout << tuple.Get<int>(0) << ' ' << tuple.Get<int>(1) << ' ' << tuple.Get<std::string>(2) << '\n';

    return 0;
}
