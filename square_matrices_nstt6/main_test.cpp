#include <gtest/gtest.h>
#include <vector>
#include "library/matrix.h"

TEST(SquareMatrices, Ctors) {
    SqMatrix mat1{5};
    SqMatrix mat2;

    SqMatrix mat3{std::vector<float>{1, 2, 3, 4, 5}};

    EXPECT_EQ(mat1.size(), 5);
    EXPECT_EQ(mat2.size(), 4);
    EXPECT_EQ(mat3.size(), 5);
    
    EXPECT_EQ(mat3[0][0], 1);
    EXPECT_EQ(mat3[1][1], 2);
    EXPECT_EQ(mat3[2][2], 3);
    EXPECT_EQ(mat3[3][3], 4);
    EXPECT_EQ(mat3[4][4], 5);

    EXPECT_EQ(mat3[1][0], 0);
    EXPECT_EQ(mat3[0][1], 0);
}

TEST(SquareMatrices, Copy) {
    SqMatrix mat1{std::vector<float>{1, 2, 3}};
    SqMatrix mat2{mat1};

    EXPECT_EQ(mat1.size(), 3);
    EXPECT_EQ(mat2.size(), 3);
}

TEST(SquareMatrices, Move) {
    SqMatrix mat1{std::vector<float>{1, 2, 3}};
    SqMatrix mat2{std::move(mat1)};

    EXPECT_EQ(mat1.size(), 3);
    EXPECT_EQ(mat2.size(), 3);

    mat2 = SqMatrix{std::vector<float>{3, 4, 5, 6}};

    EXPECT_EQ(mat2.size(), 4);
}

TEST(SquareMatrices, Equality) {
    SqMatrix mat1{std::vector<float>{1, 2, 3}};
    SqMatrix mat2{std::vector<float>{1, 2, 3}};

    EXPECT_EQ(mat1 == mat2, true);
    EXPECT_EQ(mat1 != mat2, false);
}

TEST(SquareMatrices, Addition) {}
TEST(SquareMatrices, Multiplication) {}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
