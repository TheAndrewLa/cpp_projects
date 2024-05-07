#include <type_traits>
#include <iostream>
#include <cmath>

using usize = std::size_t;
using isize = std::ptrdiff_t;

template <usize N, usize M = 2>
struct is_prime : std::conditional_t<N == M, std::integral_constant<bool, true>, 
std::conditional_t<N % M == 0, std::integral_constant<bool, false>, is_prime<N, M + 1>>> {};

template <>
struct is_prime<2, 2> : std::integral_constant<bool, true> {};

template <>
struct is_prime<3, 2> : std::integral_constant<bool, true> {};

template <usize N, usize D = 2, usize I = 0>
struct prime : std::conditional_t<is_prime<D>::value,
std::conditional_t<N == I, std::integral_constant<usize, D>, prime<N, D + 1, I + 1>>,
prime<N, D + 1, I>>{};

template <>
struct prime<0, 2, 0> : std::integral_constant<usize, 2> {};

int main(int, char**) {
    static_assert(is_prime<34>{} == false);
    static_assert(is_prime<67>{} == true);
    static_assert(is_prime<19>{} == true);
    static_assert(is_prime<25>{} == false);
    static_assert(is_prime<100>{} == false);
    static_assert(is_prime<7>{} == true);

    static_assert(prime<0>{} == 2);
    static_assert(prime<1>{} == 3);
    static_assert(prime<2>{} == 5);
    static_assert(prime<3>{} == 7);
    static_assert(prime<4>{} == 11);
    static_assert(prime<5>{} == 13);
    static_assert(prime<6>{} == 17);
    static_assert(prime<7>{} == 19);
    static_assert(prime<8>{} == 23);

    std::cout << "All tests passed!" << '\n';

    return 0;
}
