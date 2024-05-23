#include "tree.hpp"
#include <iostream>

int main(int, char**) {
    Tree<int> tree;

    tree.insert(23);
    tree.insert(12);
    tree.insert(67);
    tree.insert(89);
    tree.insert(2);

    auto end = tree.end();

    for (auto i = tree.begin(); i < end; ++i) {
        std::cout << *i << "; ";
    }

    for (auto i : tree) {
        std::cout << i << "; ";
    }

    return 0;
}
