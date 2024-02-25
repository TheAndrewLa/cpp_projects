#include "treap.h"

static void split_treap(Treap::Node* root, int key, Treap::Node** left, Treap::Node** right) {
    if (root == nullptr) {
        *left = nullptr;
        *right = nullptr;
        return;
    }

    Treap::Node* node_left;
    Treap::Node* node_right;

    if (key > root->key) {
        split_treap(root->right, key, &node_left, &node_right);
        root->right = node_left;
        
        *left = root;
        *right = node_right;
    }
    else {
        split_treap(root->left, key, &node_left, &node_right);
        root->left = node_right;

        *left = node_left;
        *right = root;
    }
}

Treap::Node* merge_nodes(Treap::Node* t1, Treap::Node* t2) {
    if (t1 == nullptr)
        return t2;
    
    if (t2 == nullptr)
        return t1;

    if (t1->priority < t2->priority) {
        t1->right = merge_nodes(t1->right, t2);
        return t1;
    }
    else {
        t2->left = merge_nodes(t1, t2->left);
        return t2;
    }
}

void delete_node(Treap::Node* node) {
    if (node == nullptr)
        return;
    
    delete_node(node->left);
    delete_node(node->right);
    delete node;
}

Treap::Node::Node(int key, int priority) : key(key), priority(priority), left(nullptr), right(nullptr) {}

Treap::Treap() : root_(nullptr) {}
Treap::Treap(NodeValue value) : root_(new Node(value.first, value.second)) {}

Treap::~Treap() {
    delete_node(this->root_);
}

Treap::Node* Treap::find_node_(int key) const {
    Node* node = this->root_;

    while (node != nullptr && node->key != key) {
        if (node->key > key)
            node = node->left;
        else
            node = node->right;
    }

    return node;
}

void Treap::insert(int key, int priority) {
    if (this->root_ == nullptr) {
        this->root_ = new Node(key, priority);
        return;
    }

    // Element with this key is already in treap
    if (this->find_node_(key) != nullptr)
        return;

    Node* t1;
    Node* t2;
    Node* node = new Node(key, priority);

    split_treap(this->root_, key, &t1, &t2);
    this->root_ = merge_nodes(merge_nodes(t1, node), t2);
}

void Treap::erase(int key) {
    Node* target = this->find_node_(key);
    
    // Nothing to erase
    if (target == nullptr)
        return;

    Node* left1;
    Node* right1;

    Node* left2;
    Node* right2;

    split_treap(this->root_, key - 1, &left1, &right1);
    split_treap(this->root_, key + 1, &left2, &right2);

    this->root_ = merge_nodes(left1, right2);

    delete target;
}

Treap::NodeValue Treap::search(int key) const {
    Node* node = this->find_node_(key);

    if (node == nullptr)
        return {-1, -1};
    
    return {node->key, node->priority};
}

Treap::NodeValue Treap::min() const {
    if (this->root_ == nullptr)
        return {-1, -1};

    Node* node = this->root_;

    while (node->left != nullptr)
        node = node->left;

    return {node->key, node->priority};
}

Treap::NodeValue Treap::max() const {
    if (this->root_ == nullptr)
        return {-1, -1};
    
    Node* node = this->root_;

    while (node->right != nullptr)
        node = node->right;

    return {node->key, node->priority};
}

void Treap::clear() {
    delete_node(this->root_);
}
