#include "CPoint.h"
#include <cmath>

/**
 * @brief Constructs a new CPoint object.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 */
CPoint::CPoint(int x, int y) : x(x), y(y) {}

int CPoint::getX() const { return x; }

int CPoint::getY() const { return y; }

/**
 * @brief Calculates the Euclidean distance to another point.
 * @param other The other point.
 * @return The Euclidean distance.
 */
double CPoint::distanceTo(const CPoint& other) const {
    int dx = x - other.x;
    int dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

/**
 * @brief Calculates the hash value for the point.
 * @return The hash value.
 */
 std::size_t CPoint::hashValue() const {
    return x * 31 + y;
}

std::size_t std::hash<CPoint>::operator()(const CPoint& point) const {
    return point.hashValue();
}

