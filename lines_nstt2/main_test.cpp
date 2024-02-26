#include <gtest/gtest.h>
#include "library/lines.h"

/*
    Using well-known testing concept: arrange -> act -> assert
*/

TEST(Points, Equality) {
    // arrange
    Point p1 {0, 0};
    Point p2 {1, 1};
    Point p3 {0, 0};

    // no act :(

    // assert
    EXPECT_EQ(p1 == p2, false);
    EXPECT_EQ(p3 == p1, true);

    EXPECT_EQ(p1 != p2, true);
    EXPECT_EQ(p3 != p1, false);
}

TEST(Lines, PointsIn) {
    // arrange
    Line line1 {2};
    Line line2 {4};
    Line line3 {1, 1};

    // act
    Point p_zero = line1.get_point();
    Point p1 = line1.get_point(1);
    Point p2 = line2.get_point(1);

    Point p3_1 = line3.get_point();
    Point p3_2 = line3.get_point(1);

    // assert
    EXPECT_EQ(p_zero, (Point {}));
    EXPECT_EQ(p1, (Point {1, 2}));
    EXPECT_EQ(p2, (Point {1, 4}));

    EXPECT_EQ(p3_1, (Point {0, 1}));
    EXPECT_EQ(p3_2, (Point {1, 2}));
}

TEST(Lines, Intersection) {
    // arrange
    Line line1 {{-10, 0}, {10, 0}};
    Line line2 {{0, -10}, {0, 10}};

    Line line3 {1};
    Line line4 {{2, 0}, {0, 2}};

    // act
    Point p_zero1 = line1.find_intersection(line2);
    Point p_zero2 = line2.find_intersection(line1);

    Point p_one1 = line3.find_intersection(line4);
    Point p_one2 = line4.find_intersection(line3);

    // assert
    EXPECT_EQ(p_zero1, (Point {}));
    EXPECT_EQ(p_zero1, p_zero2);

    EXPECT_EQ(p_one1, (Point {1, 1}));
    EXPECT_EQ(p_one1, p_one2);
}

TEST(Lines, Normal) {
    // arrange
    Line line1 {{0, -10}, {0, 10}};
    Line line2 {{2, 0}, {0, 2}};

    // act
    Line normal_line1 = line1.find_normal({0, 1});
    Point point1 = normal_line1.find_intersection({1});

    Line normal_line2 = line2.find_normal({1, 1});
    Point point2 = normal_line2.find_intersection({0});

    // assert
    EXPECT_EQ(point1, (Point {1, 1}));
    EXPECT_EQ(point2, (Point {}));
}

int main(int argc, char ** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
