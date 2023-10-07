//
// Created by daniel on 5.10.23.
//

#ifndef SEMESTRAL_POINT_H
#define SEMESTRAL_POINT_H

#include <cmath>
#include <functional>
#include <compare>

/**
 * @class Point
 * @brief A class to represent a 2D point with integer coordinates.
 */
class Point {
public:
    int x;
    int y;
    double cost;

    /**
     * @brief Default constructor.
     */
    Point() = default;

    /**
     * @brief Constructor to initialize point coordinates.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     */
    Point(int x, int y);

    /**
     * @brief Calculates the Euclidean distance to another point.
     * @param other The other point.
     * @return The Euclidean distance.
     */
    double distanceTo(const Point& other) const;

    /**
     * @brief Calculates the hash value for the point.
     * @return The hash value.
     */
    size_t hashValue() const;

    bool operator<(const Point& other) const {
        if (x < other.x) return true;
        if (x > other.x) return false;
        return y < other.y;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

/**
 * @struct hash<Point>
 * @brief Specialization of std::hash for the Point class.
 */
template<> struct std::hash<Point> {
    std::size_t operator()(const Point& point) const {
        return point.hashValue();
    }
};

#endif //SEMESTRAL_POINT_H
