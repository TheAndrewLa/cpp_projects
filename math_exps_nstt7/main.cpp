#include "library/expressions.hpp"
#include <iostream>

int main() {
    auto exp = new Add{new Mul{new Value{5}, new Variable{'x'}}, new Variable{'y'}};
    std::cout << exp->to_string() << '\n';

    auto diff_x = exp->to_differentiated('x');
    auto diff_y = exp->to_differentiated('y');

    std::cout << "df/dx = " << diff_x->to_string() << '\n';
    std::cout << "df/dy = " << diff_y->to_string() << '\n';

    delete exp;
    delete diff_x;
    delete diff_y;

    return 0;
}
