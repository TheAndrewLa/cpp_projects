#pragma once

#include <cassert>
#include <stdexcept>

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
    using Vector = Point;

    Point p0_;
    Vector dif_;

    // Function checks if points is on line
    // Just geometry...
    inline bool check_point_(const Point& point) const {
        return (this->dif_.x * (point.y - this->p0_.y)) == (this->dif_.y * (point.x - this->p0_.x));
    }

    public:
    // No default constructor becuase line {0, 0, 0, 0} (default params) seems to be weird and making no sense
    // Copy ctor should be default
    Line() = delete;
    Line(const Line& line) = default;

    // Some ctors
    Line(const Point& p1, const Point& p2);      // line by two points in 2D space
    Line(double tangent, double bias = 0) noexcept;       // line by equation: y = kx + b (or y = kx)

    // Dtor should be default
    ~Line() = default;

    // Some geomerty functions
    Line find_normal(const Point& point) const;
    Point find_intersection(const Line& line) const;

    inline Point get_point(double param = 0) const {
        return {this->p0_.x + param * this->dif_.x, this->p0_.y + param * this->dif_.y};
    }
};
