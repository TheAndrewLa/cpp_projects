#include "lines.h"

Line::Line(const Point& p0, const Point& p1) {
    if (p1 == p0)
        throw std::invalid_argument("Points shouldn't be same");

    this->p0_ = {p0};
    this->dif_ = {p1.x - p0.x, p1.y - p0.y};
}

// I think it's good to put noexcept here (becase this ctor will never break a program)
Line::Line(double tangent, double bias) noexcept : Line({0, bias}, {1, tangent + bias}) {}

Line Line::find_normal(const Point& point) const {
    if (!this->check_point_(point))
        throw std::invalid_argument("Point should be on the line");

    Point normal {point.x + this->dif_.y, point.y - this->dif_.x};
    return {point, normal};
}

Point Line::find_intersection(const Line& other) const {
    // Checking if direction vectors are linear-independend
    // Because if they are, intersection is a whole line or empty
    if (this->dif_.x * other.dif_.y == this->dif_.y * other.dif_.x)
        throw std::invalid_argument("Direction vectors should be linear-independend");

    // Two points on our line (definetly not same)
    Point p1 {this->get_point(0)};
    Point p2 {this->get_point(1)};

    // Two points on given line (definetly not same)
    Point p3 {other.get_point(0)};
    Point p4 {other.get_point(1)};

    // If we accidentally find the intersection we just return point
    if (p1 == p3 || p1 == p4)
        return p1;

    if (p2 == p3 || p2 == p4)
        return p2;

    // Calculation of intersection
    double denom = ((p1.x - p2.x) * (p3.y - p4.y)) - ((p1.y - p2.y) * (p3.x - p4.x));

    // KABOOM!
    // We can't divide by zero
    assert(denom != 0);

    double x = ((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p3.x * p4.y - p3.y * p4.x) * (p1.x - p2.x)) / (denom);
    double y = ((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p3.x * p4.y - p3.y * p4.x) * (p1.y - p2.y)) / (denom);

    // Checking correctness of logic of program
    assert(this->check_point_({x, y}) && other.check_point_({x, y}));

    return {x, y};
}
