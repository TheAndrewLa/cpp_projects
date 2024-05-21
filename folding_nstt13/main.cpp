#include <stdexcept>
#include <functional>
#include <iostream>
#include <bitset>

using usize = std::size_t;
using isize = std::ptrdiff_t;

// THIS SOLUTION IS WAY BETTER!!!

//   template <typename Check>
//   usize checkArg(usize index, const Check& checker) {
//       throw std::invalid_argument{"No arguments provided!\n"};
//   }
//   
//   template <typename Check, typename Arg, typename... Args>
//   usize checkArg(usize index, const Check& checker, const Arg& first, const Args&... others) {
//       if (static_cast<bool>(checker(first)))
//           return index;
//       else
//           return checkArg(index + 1, checker, others...);
//   }
//   
//   template <typename Check, typename... Args>
//   usize getIndexOfFirstMatch(const Check& checker, const Args&... args) {
//       return checkArg(0, checker, args...);
//   }
//   
//   template <typename Check, typename Dummy = void>
//   usize getIndexOfFirstMatch(const Check& checker) {
//       throw std::invalid_argument{"No arguments provided!\n"};
//   }

template <typename CheckFunc, typename... Args>
usize getIndexOfFirstMatch(const CheckFunc& checker, Args&&... args) {
    isize found = -1;
    usize current = 0;

    auto func = [&] <typename T> (T&& i) {
        if (found != -1)
            return true;

        bool result = static_cast<bool>(checker(std::forward<T>(i)));

        if (result) found = current;
        current++;

        return result;
    };

    bool result = (... || func<Args>(args));

    if (!result)
        throw std::invalid_argument{"No arguments with true result!"};

    return found;
}

bool is_positive(int a);
bool is_negative(int a);
bool is_zero(int a);

bool is_palindrome(const std::string& str);

int main() {
    usize positive = getIndexOfFirstMatch(is_positive, 0, -2, 4, 5, -6, 7);
    usize negative = getIndexOfFirstMatch(is_negative, 0, 2, 4, 5, -6, 7);
    usize zero = getIndexOfFirstMatch(is_zero, -2, 4, 0, -6, 7);

    std::string sweden_band = "ABBA";
    std::string italian_band = "Maneskin";

    usize palindrome = getIndexOfFirstMatch(is_palindrome, italian_band, "ABC", sweden_band, "Hello", "World");
    
    std::cout << positive << std::endl;
    std::cout << negative << std::endl;
    std::cout << zero << std::endl;

    std::cout << palindrome << std::endl;

    return 0;
}

bool is_positive(int a) {
    return a > 0;
}

bool is_negative(int a) {
    return a < 0;
}

bool is_zero(int a) {
    return a == 0;
}

bool is_palindrome(const std::string& str) {
    usize len = str.size();

    for (usize i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1])
            return false;
    }

    return true;
}
