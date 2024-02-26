#include <gtest/gtest.h>
#include "library/treap.h"

TEST(Treap, Copy) {
    Treap treap;

    treap.insert(5, 1);
    treap.insert(7, 2);
    treap.insert(6, 3);
    treap.insert(3, 4);
    treap.insert(9, 9);

    Treap treap2(treap);

    EXPECT_EQ(treap.search(3), treap2.search(3));
    EXPECT_EQ(treap.min(), treap2.min());

    Treap treap3 = treap;

    EXPECT_EQ(treap.max(), treap3.max());
    EXPECT_EQ(treap.search(6), treap3.search(6));
}

TEST(Treap, Insert) {
    Treap treap;
    
    treap.insert(5, 1);
    treap.insert(7, 2);
    treap.insert(6, 3);
    treap.insert(3, 4);
    treap.insert(9, 9);

    EXPECT_EQ(treap.max(), (Treap::NodeValue {9, 9}));
    EXPECT_EQ(treap.min(), (Treap::NodeValue {3, 4}));
}

TEST(Treap, Erase) {
    Treap treap;
    
    treap.insert(5, 1);
    treap.insert(7, 2);
    treap.insert(6, 3);
    treap.insert(3, 4);
    treap.insert(9, 9);

    treap.erase(9);
    treap.erase(3);

    EXPECT_EQ(treap.max(), (Treap::NodeValue {7, 2}));
    EXPECT_EQ(treap.min(), (Treap::NodeValue {5, 1}));

    treap.erase(5);

    EXPECT_EQ(treap.min(), (Treap::NodeValue {6, 3}));
    EXPECT_EQ(treap.max(), (Treap::NodeValue {7, 2}));
}

TEST(Treap, Search) {
    Treap treap;
    
    treap.insert(5, 1);
    treap.insert(7, 2);
    treap.insert(6, 3);
    treap.insert(3, 4);
    treap.insert(9, 9);

    EXPECT_EQ(treap.search(7), (Treap::NodeValue {7, 2}));
    EXPECT_EQ(treap.search(6), (Treap::NodeValue {6, 3}));
    EXPECT_EQ(treap.search(5), (Treap::NodeValue {5, 1}));
    EXPECT_EQ(treap.search(3), (Treap::NodeValue {3, 4}));
    EXPECT_EQ(treap.search(9), (Treap::NodeValue {9, 9}));
    EXPECT_EQ(treap.search(4), (Treap::NodeValue {-1, -1}));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
