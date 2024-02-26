#include "lines.h"

Line::Line(const Point& p0, const Point& p1) {
    // TODO: throwing exception here is better than c-assert
    assert(p1 != p0 && "Points which form a line sould be the different");

    this->x0_ = p0.x;
    this->y0_ = p0.y;

    this->x_dif_ = p1.x - p0.x;
    this->y_dif_ = p1.y - p0.y;
}

// I think it's good to put noexcept here (becase this ctor will never break a program)
Line::Line(double tangent, double bias) : Line({0, bias}, {1, tangent + bias}) {}

Line Line::find_normal(const Point& point) const {
    assert(this->check_point_(point) && "Point should be on the line");

    Point normal {point.x + this->y_dif_, point.y - this->x_dif_};
    return {point, normal};
}

Point Line::find_intersection(const Line& other) const {
    // Checking if direction vectors are linear-independend
    // Because if they are, intersection is a whole line or empty
    assert((this->x_dif_ * other.y_dif_) - (this->y_dif_ * other.x_dif_) != 0 && "Direction vectors should be linear-independend");

    // Two points on our line (definetly not same)
    Point p1 {this->x0_, this->y0_};
    Point p2 {this->get_point(1)};

    // Two points on given line (definetly not same)
    Point p3 {other.x0_, other.y0_};
    Point p4 {other.get_point(1)};

    // If we accidentally find the intersection we just return point
    if (p1 == p3 || p1 == p4)
        return p1;

    if (p2 == p3 || p2 == p4)
        return p2;

    // Normal calc of intersection
    // Very complicated equations but it works (i think)
    // Divison by zero will not be done, cuz of checkin be4

    double denom = ((p1.x - p2.x) * (p3.y - p4.y)) - ((p1.y - p2.y) * (p3.x - p4.x));

    // assert(denom != 0 && "Denominator can not be zero!");

    double x = ((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p3.x * p4.y - p3.y * p4.x) * (p1.x - p2.x)) / (denom);
    double y = ((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p3.x * p4.y - p3.y * p4.x) * (p1.y - p2.y)) / (denom);

    return {x, y};
}
