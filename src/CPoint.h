//
// Created by daniel on 5.10.23.
//

#ifndef SEMESTRAL_CPOINT_H
#define SEMESTRAL_CPOINT_H

#include <cmath>
#include <functional>

/**
 * @class CPoint
 * @brief A class to represent a 2D point with integer coordinates.
 */
class CPoint {
private:
    int x;
    int y;
public:

    /**
     * @brief Constructor to initialize point coordinates.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     */
    CPoint(int x, int y);

    int getX() const;
    int getY() const;

    /**
     * @brief Calculates the Euclidean distance to another point.
     * @param other The other point.
     * @return The Euclidean distance.
     */
    double distanceTo(const CPoint& other) const;

    /**
     * @brief Calculates the hash value for the point.
     * @return The hash value.
     */
    size_t hashValue() const;

    /**
     * @brief Overloaded equality operator.
     * @param other The other point to compare with.
     * @return True if both points have the same coordinates, false otherwise.
     */
    bool operator==(const CPoint& other) const = default;
};

/**
 * @brief Hash function to enable the use of CPoint in some STL containers.
 */
template <> struct std::hash<CPoint> {
    std::size_t operator()(const CPoint& point) const;
};



#endif //SEMESTRAL_CPOINT_H
