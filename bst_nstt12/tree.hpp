#pragma once
#include <stdexcept>
#include <cassert>
#include <iostream>

// This is looks like std containers conventions
// Object has to have only dtor to be able to be stored in collection

template <typename T>
concept KeyType = requires(const std::remove_reference_t<T>& a, const std::remove_reference_t<T>& b) {
    {a < b} -> std::convertible_to<bool>;
    {a > b} -> std::convertible_to<bool>;
    {a == b} -> std::convertible_to<bool>;
    {a != b} -> std::convertible_to<bool>;
    std::destructible<T>;
};

template <KeyType T>
class Tree;

template <KeyType T>
typename Tree<T>::Node* search_node(const T& value, typename Tree<T>::Node* node) {
    if (node == nullptr)
        throw std::invalid_argument{"Node with such value doesn't exist!"};

    if (value > node->value)
        return search_node<T>(value, node->right);
    else if (value < node->value)
        return search_node<T>(value, node->left);

    return node;
}

template <KeyType T>
typename Tree<T>::Node* insert_node(typename Tree<T>::Node* node, typename Tree<T>::Node* root, typename Tree<T>::Node* parent = nullptr) {
    if (root == nullptr) {
        node->parent = parent;
        return node;
    }

    if (node->value > root->value)
        root->right = insert_node<T>(node, root->right, root);
    else if (node->value < root->value)
        root->left = insert_node<T>(node, root->left, root);
    else
        std::invalid_argument{"Values have to be unique!\n"};

    node->parent = parent;
    return root;
}

template <KeyType T>
typename Tree<T>::Node* find_min(typename Tree<T>::Node* node) {
    if (node == nullptr)
        throw std::invalid_argument{"Invalid node!\n"};

    typename Tree<T>::Node* current = node;
    while (current->right != nullptr)
        current = current->right;

    return current;
}

template <KeyType T>
typename Tree<T>::Node* find_max(typename Tree<T>::Node* node) {
    if (node == nullptr)
        throw std::invalid_argument{"Invalid node!\n"};
    
    typename Tree<T>::Node* current = node;
    while (current->left != nullptr)
        current = current->left;

    return current;
}

template <KeyType T>
void release_node(typename Tree<T>::Node* node) {
    if (node != nullptr) return;

    release_node<T>(node->left);
    release_node<T>(node->right);
    delete node;
}

template <KeyType T>
void print_node(typename Tree<T>::Node* node) {
    if (node == nullptr) return;

    print_node<T>(node->left);
    std::cout << node->value << ' ';
    print_node<T>(node->right);
}

template <KeyType T>
class Tree {
    public:
    struct Node {
        T value;

        Node* left;
        Node* right;

        Node* parent;

        Node() = delete;

        template <typename... Args>
        Node(Args&&... args) : value(std::forward<Args>(args)...), left(nullptr), right(nullptr), parent(nullptr) {}

        Node(const T& val) requires(std::copyable<T>) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
        Node(T&& val) requires(std::movable<T>) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}

        Node(const Node&) = delete;
        Node(Node&&) = delete;

        ~Node() = default;
    };

    class ForwardIterator {
        // Only const, because we can break our tree, modifying values
        public:

        friend class Tree<T>;

        const T& operator*() const {
            return current_->value;
        }

        ForwardIterator& operator++() {
            assert(current_->parent != nullptr);

            if (up_) {
                current_ = current_->parent;
                up_ = false;
            }
            else {
                if (current_->left == nullptr) {
                    current_ = current_->parent;
                    up_ = false;
                }
                else {
                    current_ = find_min<T>(current_->left);
                    up_ = true;
                }
            }

            return *this;
        }

        inline bool operator==(const ForwardIterator& iter) const {
            assert(current_ != nullptr);
            return current_->value == iter.current_->value;
        }

        inline bool operator!=(const ForwardIterator& iter) const {
            assert(current_ != nullptr);
            return current_->value == iter.current_->value;
        }

        inline bool operator<(const ForwardIterator& iter) const {
            assert(current_ != nullptr);
            return current_->value < iter.current_->value;
        }

        inline bool operator>(const ForwardIterator& iter) const {
            assert(current_ != nullptr);
            return current_->value > iter.current_->value;
        }

        private:
        Node* current_{nullptr};
        bool up_{false};
    };

    Tree() = default;

    ~Tree() {
        release_node<T>(root_);
    }

    // JUST LIKE IN STL (emplace & insert)

    template <typename... Args>
    void emplace(Args&&... args) {
        if (root_ == nullptr)
            root_ = new Node{std::forward<Args>(args)...};
        else
            root_ = insert_node<T>(new Node{std::forward<Args>(args)...}, root_);
    }

    void insert(const T& value) requires(std::copyable<T>) {
        if (root_ == nullptr)
            root_ = new Node{value};
        else
            root_ = insert_node<T>(new Node{value}, root_);
    }

    void insert(T&& value) requires(std::movable<T>) {
        if (root_ == nullptr)
            root_ = new Node{value};
        else
            root_ = insert_node<T>(new Node{value}, root_);
    }

    void search(const T& key) {}

    void print_all() {
        print_node<T>(root_);
    }

    ForwardIterator begin() const {
        ForwardIterator iter;
        iter.current_ = find_min<T>(root_);
        
        return iter;
    }

    ForwardIterator end() const {
        ForwardIterator iter;
        iter.current_ = find_max<T>(root_);

        return iter;
    }

    private:
    Node* root_{nullptr};
};
