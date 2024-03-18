#pragma once
#include <random>

class Treap {
public:
    struct Node {
        int key, priority;
        Node* left;
        Node* right;

        Node() = delete;
        Node(int key, int priority);
    };

    using NodeValue = std::pair<int, int>;

    Treap();
    Treap(NodeValue root);

    Treap(const Treap& treap);
    Treap(Treap&& treap);

    ~Treap();

    Treap& operator=(const Treap& other);
    Treap& operator=(Treap&& other);

    // Insert by key & priority
    void insert(const NodeValue& value);

    // Insert only by priority (key will be generated randomly and returned)
    int insert(int priority);

    void erase(int key);
    NodeValue search(int key) const;

    NodeValue min() const;
    NodeValue max() const;

    void clear();

private:
    Node* root_;
    Node* find_node_(int key) const;
};
