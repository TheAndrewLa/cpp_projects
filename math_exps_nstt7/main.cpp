#include "library/expressions.hpp"
#include <iostream>

int main() {
    auto exp = new Add{new Mul{new Value{5}, new Variable{'x'}}, new Variable{'y'}};
    std::cout << exp->to_string() << '\n';

    auto diff_x = exp->differentiate('x');
    auto diff_y = exp->differentiate('y');

    std::cout << diff_x->to_string() << '\n' << diff_y->to_string() << '\n';

    delete exp;
    delete diff_x;
    delete diff_y;

    return 0;
}
