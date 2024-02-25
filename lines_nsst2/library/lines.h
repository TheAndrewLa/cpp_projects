#pragma once

#include <cmath>
#include <cassert>

struct Point {
    double x;
    double y;

    Point() = default;
    Point(const Point&) = default;
    ~Point() = default;

    inline bool operator==(const Point& other) const {
        return (this->x == other.x && this->y == other.y);
    }

    inline bool operator!=(const Point& other) const {
        return (this->x != other.x || this->y != other.y);
    }
};

class Line {
    // Initial point
    double x0_;
    double y0_;

    // Direction vector
    double x_dif_;
    double y_dif_;

    // Function checks if points is on line
    // Just geometry...
    inline bool check_point_(const Point& point) const {
        return (this->x_dif_ * (point.y - this->y0_)) == (this->y_dif_ * (point.x - this->x0_));
    }

    public:
    // No default constructor becuase line {0, 0, 0, 0} (default params) seems to be weird and making no sense
    // Copy ctor should be default
    Line() = delete;
    Line(const Line& line) = default;

    // Some ctors
    Line(const Point& p1, const Point& p2);      // line by two points in 2D space
    Line(double tangent, double bias = 0);       // line by equation: y = kx + b (or y = kx)

    // Dtor should be default
    ~Line() = default;

    // Some geomerty functions
    Line find_normal(const Point& point) const;
    Point find_intersection(const Line& line) const;

    inline Point get_point(double param = 0) const {
        return {this->x0_ + param * this->x_dif_, this->y0_ + param * this->y_dif_};
    }
};
