#pragma once
#include <iostream>

class Point {
private:
    double x, y;

public:
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

    double getx() const { return x; }
    double gety() const { return y; }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    bool operator<(const Point& other) const {
        double cross = this->crossProduct(other);
        if (std::abs(cross) > 1e-9) { //проверка на коллинеарность
            return cross > 0; //если нет - сортировка по углу
        }
        return this->distanceSquared() < other.distanceSquared();
    }

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    double crossProduct(const Point& other) const {
        return x * other.y - y * other.x;
    }

    double distanceSquared() const {
        return x * x + y * y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }
};