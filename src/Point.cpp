#include "Point.h"
#include <cmath>

/**
 * @brief Constructs a new Point object.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 */
Point::Point(int x, int y) : x(x), y(y), cost(std::numeric_limits<double>::infinity()) {}

/**
 * @brief Calculates the Euclidean distance to another point.
 * @param other The other point.
 * @return The Euclidean distance.
 */
double Point::distanceTo(const Point& other) const {
    int dx = x - other.x;
    int dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

/**
 * @brief Calculates the hash value for the point.
 * @return The hash value.
 */
 std::size_t Point::hashValue() const {
    return x * 31 + y;
}

