#include <type_traits>
#include <iostream>
#include <cmath>

using usize = std::size_t;
using isize = std::ptrdiff_t;

template <usize N, usize M = 2>
struct is_prime : std::conditional_t<(N < M * M), std::true_type, 
std::conditional_t<N % M == 0, std::false_type, is_prime<N, M + 1>>> {};

template <usize N, usize D = 2, usize I = 0>
struct prime : std::conditional_t<is_prime<D>::value,
std::conditional_t<N == I, std::integral_constant<usize, D>, prime<N, D + 1, I + 1>>,
prime<N, D + 1, I>> {};

int main(int, char**) {
<<<<<<< HEAD
    std::cout << prime<90>{} << '\n';
    std::cout << prime<91>{} << '\n';
    std::cout << prime<92>{} << '\n';
    std::cout << prime<93>{} << '\n';

    std::cout << "All tests passed!" << '\n';
=======
    std::cout << prime<15>{} << '\n';
    std::cout << prime<30>{} << '\n';
    std::cout << prime<60>{} << '\n';
    std::cout << prime<120>{} << '\n';
>>>>>>> e78672b (hmmmm)

    return 0;
}
