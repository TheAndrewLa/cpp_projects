#include <gtest/gtest.h>
#include "library/treap.h"

TEST(Treap, Copy) {
    Treap treap;

    treap.insert({5, 1});
    treap.insert({7, 2});
    treap.insert({6, 3});
    treap.insert({3, 4});
    treap.insert({9, 9});

    Treap treap2(treap);

    // Remove node from initial treap and then try to find it in copied treap
    treap.erase(3);
    EXPECT_EQ(treap2.search(3), (Treap::NodeValue {3, 4}));

    Treap treap3 = treap;

    // Remove node from initial treap and then try to find it in copied treap
    treap.erase(6);
    EXPECT_EQ(treap3.search(6), (Treap::NodeValue {6, 3}));
}

TEST(Treap, Move) {
    Treap treap;

    treap.insert({5, 1});
    treap.insert({7, 2});
    treap.insert({6, 3});
    treap.insert({3, 4});
    treap.insert({9, 9});

    Treap treap2({treap});

    // Remove node from initial treap and then try to find it in copied treap
    treap.erase(3);
    EXPECT_EQ(treap2.search(3), (Treap::NodeValue {3, 4}));

    Treap treap3 = std::move(treap);

    // Remove node from initial treap and then try to find it in copied treap
    treap.erase(6);
    EXPECT_EQ(treap3.search(6), (Treap::NodeValue {6, 3}));
}

TEST(Treap, Insert) {
    Treap treap;
    
    treap.insert({5, 1});
    treap.insert({7, 2});
    treap.insert({6, 3});
    treap.insert({3, 4});
    treap.insert({9, 9});
}

TEST(Treap, Erase) {
    Treap treap;
    
    int k1 = treap.insert(1);
    int k2 = treap.insert(2);
    int k3 = treap.insert(3);
    int k4 = treap.insert(4);
    int k5 = treap.insert(5);

    treap.erase(k1);
    treap.erase(k5);

    EXPECT_EQ(treap.search(k2), (Treap::NodeValue {k2, 2}));
    EXPECT_EQ(treap.search(k3), (Treap::NodeValue {k3, 3}));
    EXPECT_EQ(treap.search(k4), (Treap::NodeValue {k4, 4}));

    EXPECT_EQ(treap.search(k1), (Treap::NodeValue {-1, -1}));
    EXPECT_EQ(treap.search(k5), (Treap::NodeValue {-1, -1}));
}

TEST(Treap, Search) {
    Treap treap;
    
    int k1 = treap.insert(1);
    int k2 = treap.insert(2);
    int k3 = treap.insert(3);
    int k4 = treap.insert(4);
    int k5 = treap.insert(5);

    EXPECT_EQ(treap.search(k1), (Treap::NodeValue {k1, 1}));
    EXPECT_EQ(treap.search(k2), (Treap::NodeValue {k2, 2}));
    EXPECT_EQ(treap.search(k3), (Treap::NodeValue {k3, 3}));
    EXPECT_EQ(treap.search(k4), (Treap::NodeValue {k4, 4}));
    EXPECT_EQ(treap.search(k5), (Treap::NodeValue {k5, 5}));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
