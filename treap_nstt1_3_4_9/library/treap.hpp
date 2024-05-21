#pragma once
#include <random>
#include <deque>
#include <stdexcept>

template <typename T>
concept KeyType = requires(const std::remove_reference_t<T>& a, const std::remove_reference_t<T>& b) {
    {a < b} -> std::convertible_to<bool>;
    {a > b} -> std::convertible_to<bool>;
    {a == b} -> std::convertible_to<bool>;
    {a != b} -> std::convertible_to<bool>;

    std::movable<T>;
    std::copyable<T>;
    std::destructible<T>;
};

template <KeyType>
class Treap;

template <KeyType T>
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

template <KeyType T>
typename Treap<T>::Node* merge_nodes(typename Treap<T>::Node* t1, typename Treap<T>::Node* t2) noexcept {
    if (t1 == nullptr)
        return t2;
    
    if (t2 == nullptr)
        return t1;

    if (t1->priority < t2->priority) {
        t1->right = merge_nodes<T>(t1->right, t2);
        return t1;
    }
    else {
        t2->left = merge_nodes<T>(t1, t2->left);
        return t2;
    }
}

template <KeyType T>
typename Treap<T>::Node* copy_node(typename Treap<T>::Node* node) noexcept {
    if (node == nullptr)
        return nullptr;

    auto original = new typename Treap<T>::Node(node->key, node->priority);
    original->left = copy_node<T>(node->left);
    original->right = copy_node<T>(node->right);

    return original;
}

template <KeyType T>
void delete_node(typename Treap<T>::Node* node) noexcept {
    if (node == nullptr)
        return;
    
    delete_node<T>(node->left);
    delete_node<T>(node->right);
    delete node;
}

// T is for priority
template <KeyType T>
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
    using Iterator = typename std::deque<Node*>::iterator;

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

        if (root_ == nullptr) {
            root_ = new Node{key, priority};
            nodes_.push_back(root_);
            return;
        }

        // Element with this key is already in treap
        if (find_node(key) != nullptr)
            throw std::invalid_argument{"Element with such key already exist!"};

        Node* t1;
        Node* t2;
        Node* node = new Node{key, priority};

        if (key > root_->key)
            nodes_.push_back(node);
        else
            nodes_.push_front(node);

        split_treap<T>(root_, key, &t1, &t2);
        root_ = merge_nodes<T>(merge_nodes<T>(t1, node), t2);        
    }

    // Insert only by key (priority will be generated randomly and returned)
    int insert(const T& key) {
        std::srand(42);

        int priority = std::rand() % 100;
        insert({key, priority});

        return priority;
    }

    void erase(const T& key) noexcept {
        Node* target = find_node(key);

        if (target == nullptr)
            return;

        nodes_.erase(std::find(nodes_.begin(), nodes_.end(), target));

        Node* left1;
        Node* right1;

        Node* left2;
        Node* right2;

        split_treap<T>(root_, key, &left1, &right1);
        split_treap<T>(root_, key + 1, &left2, &right2);

        root_ = merge_nodes<T>(left1, right2);

        delete target;
    }

    Iterator begin() {
        return nodes_.begin();
    }

    Iterator end() {
        return nodes_.end();
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
    
        Node* node = root_;

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

    std::deque<Node*> nodes_;
};
