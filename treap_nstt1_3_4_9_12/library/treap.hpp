#pragma once
#include <random>
#include <exception>

template <typename T>
concept key_type = requires(const std::remove_reference_t<T>& a, const std::remove_reference_t<T>& b) {
    {a < b} -> std::convertible_to<bool>;
    {a > b} -> std::convertible_to<bool>;
    {a == b} -> std::convertible_to<bool>;
    {a != b} -> std::convertible_to<bool>;

    std::movable<T>;
    std::copyable<T>;
    std::destructible<T>;
};

template <key_type>
class Treap;

template <key_type T>
void split_treap(typename Treap<T>::Node* root, const T& key, typename Treap<T>::Node** left, typename Treap<T>::Node** right) noexcept {
    if (root == nullptr) {
        *left = nullptr;
        *right = nullptr;
        return;
    }

    typename Treap<T>::Node* node_left;
    typename Treap<T>::Node* node_right;

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

template <key_type T>
typename Treap<T>::Node* merge_nodes(typename Treap<T>::Node* t1, typename Treap<T>::Node* t2) noexcept {
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

template <key_type T>
typename Treap<T>::Node* copy_node(typename Treap<T>::Node* node) noexcept {
    if (node == nullptr)
        return nullptr;

    auto original = new typename Treap<T>::Node(node->key, node->priority);
    original->left = copy_node(node->left);
    original->right = copy_node(node->right);

    return original;
}

template <key_type T>
void delete_node(typename Treap<T>::Node* node) noexcept {
    if (node == nullptr)
        return;
    
    delete_node(node->left);
    delete_node(node->right);
    delete node;
}

// T is for priority
template <key_type T>
class Treap {
public:
    struct Node {
        T key;
        int priority;

        Node* left;
        Node* right;

        Node() = delete;
        Node(const T& key, int priority) : key(key), priority(priority), left(nullptr), right(nullptr) {}
    };

    using NodeValue = std::pair<const T&, int>;

    Treap() noexcept : root_(nullptr) {}
    Treap(NodeValue root) noexcept : root_(new Node(root.first, root.second)) {}

    Treap(const Treap& treap) noexcept : root_(copy_node<T>(treap.root_)) {}

    Treap(Treap&& treap) noexcept {
        root_ = treap.root_;
        treap.root_ = nullptr;
    }

    ~Treap() {
        clear();
    }

    Treap<T>& operator=(const Treap<T>& other) {
        delete_node<T>(root_);
        root_ = copy_node<T>(other.root_);

        return *this;
    }

    Treap<T>& operator=(Treap<T>&& other) {
        delete_node<T>(root_);
        root_ = other.root_;
        other.root_ = nullptr;

        return *this;
    }

    // Insert by key & priority
    void insert(const NodeValue& value) {
        int key = value.first;
        T priority = value.second;

        if (this->root_ == nullptr) {
            this->root_ = new Node(key, priority);
            return;
        }

        // Element with this key is already in treap
        if (this->find_node(key) != nullptr)
            return;

        Node* t1;
        Node* t2;
        Node* node = new Node(key, priority);

        split_treap<T>(root_, key, &t1, &t2);
        root_ = merge_nodes<T>(merge_nodes<T>(t1, node), t2);        
    }

    // Insert only by key (priority will be generated randomly and returned)
    int insert(const T& key) noexcept {
        std::srand(42);

        int priority = std::rand() % 100;
        insert({key, priority});

        return priority;
    }

    void erase(const T& key) noexcept {
        Node* target = this->find_node(key);

        if (target == nullptr)
            return;

        Node* left1;
        Node* right1;

        Node* left2;
        Node* right2;

        split_treap<T>(this->root_, key, &left1, &right1);
        split_treap<T>(this->root_, key + 1, &left2, &right2);

        root_ = merge_nodes<T>(left1, right2);

        delete target;
    }

    NodeValue search(const T& key) const {
        Node* node = find_node(key);

        if (node == nullptr)
            throw std::invalid_argument("Node not found!");

        return {node->key, node->priority};
    }

    NodeValue min() const {
        if (root_ == nullptr)
            throw std::logic_error("Can't peek min from empty heap!");
        
        Node* node = root_;

        while (node->left != nullptr)
            node = node->left;

        return {node->key, node->priority};
    }

    NodeValue max() const {
        if (root_ == nullptr)
            throw std::logic_error("Can't peek max from empty heap!");
    
        Node* node = this->root_;

        while (node->right != nullptr)
            node = node->right;

        return {node->key, node->priority};
    }

    void clear() noexcept {
        delete_node<T>(root_);
    }

private:
    Node* root_;

    Node* find_node(const T& key) const {
        Node* node = root_;

        while (node != nullptr && node->key != key) {
            if (node->key > key)
                node = node->left;
            else
                node = node->right;
        }

        return node;
    }
};
