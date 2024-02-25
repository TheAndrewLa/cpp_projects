#pragma once
#include <vector>

using std::vector;
using std::pair;

class Treap {
    public:
    struct Node {
        int key, priority;
        Node* left;
        Node* right;

        Node() = delete;
        Node(int key, int priority);
    };

    using NodeValue = pair<int, int>;

    private:
    Node* root_;
    Node* find_node_(int key) const;

    public:
    Treap();
    Treap(NodeValue root);
    ~Treap();

    void insert(int key, int priority);
    void erase(int key);
    NodeValue search(int key) const;

    NodeValue min() const;
    NodeValue max() const;

    void clear();

    inline Node* root() const {
        return this->root_;
    }
};
