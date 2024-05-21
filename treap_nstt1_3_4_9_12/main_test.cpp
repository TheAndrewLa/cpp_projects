#include <gtest/gtest.h>
#include "library/treap.hpp"

TEST(Treap, Copy) {
    Treap<int> treap;
    
    treap.insert({6, 9});
    treap.insert({7, 6});

    treap.insert({1, 3});
    treap.insert({2, 4});
    treap.insert({3, 5});
    treap.insert({4, 10});
    treap.insert({5, 12});

    Treap<int> treap2 = treap;
    Treap<int> treap3 {treap};

    treap3.erase(6);

    EXPECT_EQ(treap.search(6), (typename Treap<int>::NodeValue {6, 9}));
}

TEST(Treap, Move) {
    Treap<int> treap;
    
    treap.insert({6, 9});
    treap.insert({7, 6});

    int k1 = treap.insert(1);
    int k2 = treap.insert(2);

    Treap<int> treap2({treap});
    Treap<int> treap3 = std::move(treap);

    EXPECT_EQ(treap.search(6), (typename Treap<int>::NodeValue {-1, -1}));
    EXPECT_EQ(treap.search(7), (typename Treap<int>::NodeValue {-1, -1}));
    EXPECT_EQ(treap.search(k1), (typename Treap<int>::NodeValue {-1, -1}));
    EXPECT_EQ(treap.search(k2), (typename Treap<int>::NodeValue {-1, -1}));

    EXPECT_EQ(treap2.search(6), (typename Treap<int>::NodeValue {6, 9}));
    EXPECT_EQ(treap2.search(7), (typename Treap<int>::NodeValue {7, 6}));
    EXPECT_EQ(treap2.search(k1), (typename Treap<int>::NodeValue {k1, 1}));
    EXPECT_EQ(treap2.search(k2), (typename Treap<int>::NodeValue {k2, 2}));

    EXPECT_EQ(treap3.search(6), (typename Treap<int>::NodeValue {6, 9}));
    EXPECT_EQ(treap3.search(7), (typename Treap<int>::NodeValue {7, 6}));
    EXPECT_EQ(treap3.search(k1), (typename Treap<int>::NodeValue {k1, 1}));
    EXPECT_EQ(treap3.search(k2), (typename Treap<int>::NodeValue {k2, 2}));
}

TEST(Treap, Insert) {
    Treap<int> treap;
    
    treap.insert({5, 1});
    treap.insert({7, 2});
    treap.insert({6, 3});
    int k1 = treap.insert(6);
    int k2 = treap.insert(5);
    int k3 = treap.insert(4);

    EXPECT_EQ(treap.search(5), (typename Treap<int>::NodeValue {5, 1}));
    EXPECT_EQ(treap.search(7), (typename Treap<int>::NodeValue {7, 2}));
    EXPECT_EQ(treap.search(6), (typename Treap<int>::NodeValue {6, 3}));
    EXPECT_EQ(treap.search(k1), (typename Treap<int>::NodeValue {k1, 6}));
    EXPECT_EQ(treap.search(k2), (typename Treap<int>::NodeValue {k2, 5}));
    EXPECT_EQ(treap.search(k3), (typename Treap<int>::NodeValue {k3, 4}));
}

TEST(Treap, Erase) {
    Treap<int> treap;

    treap.insert({6, 9});
    treap.insert({7, 6});

    int k1 = treap.insert(1);
    int k2 = treap.insert(2);
    int k3 = treap.insert(3);
    int k4 = treap.insert(4);
    int k5 = treap.insert(5);

    treap.erase(k1);
    treap.erase(k5);
    treap.erase(7);

    EXPECT_EQ(treap.search(k2), (typename Treap<int>::NodeValue {k2, 2}));
    EXPECT_EQ(treap.search(k3), (typename Treap<int>::NodeValue {k3, 3}));
    EXPECT_EQ(treap.search(k4), (typename Treap<int>::NodeValue {k4, 4}));
    EXPECT_EQ(treap.search(6), (Treap<int>::NodeValue {6, 9}));

    EXPECT_EQ(treap.search(k1), (typename Treap<int>::NodeValue {-1, -1}));
    EXPECT_EQ(treap.search(k5), (typename Treap<int>::NodeValue {-1, -1}));
    EXPECT_EQ(treap.search(7), (typename Treap<int>::NodeValue {-1, -1}));
}

TEST(Treap, Search) {
    Treap<int> treap;
    
    int k1 = treap.insert(1);
    int k2 = treap.insert(2);
    int k3 = treap.insert(3);
    int k4 = treap.insert(4);
    int k5 = treap.insert(5);

    EXPECT_EQ(treap.search(k1), (typename Treap<int>::NodeValue {k1, 1}));
    EXPECT_EQ(treap.search(k2), (typename Treap<int>::NodeValue {k2, 2}));
    EXPECT_EQ(treap.search(k3), (typename Treap<int>::NodeValue {k3, 3}));
    EXPECT_EQ(treap.search(k4), (typename Treap<int>::NodeValue {k4, 4}));
    EXPECT_EQ(treap.search(k5), (typename Treap<int>::NodeValue {k5, 5}));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
