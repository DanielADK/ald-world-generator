//
// Created by daniel on 6.10.23.
//

#include <random>
#include "Map.h"

/**
 * @class CityGenerator
 * @brief A class for generating Voronoi diagrams to simulate city layouts on a map.
 */
class CityGenerator {
private:
    Map& m_Map;
    std::vector<Point> m_Cities;


    /**
     * @brief Computes the centroid of a set of points.
     * @param points The set of points.
     * @return The centroid point.
     */
    static Point computeCentroid(const std::vector<Point>& points);
public:

    /**
     * @brief Constructor that initializes the CityGenerator with a reference to a Map object.
     * @param map A reference to a Map object.
     */
    explicit CityGenerator(Map& map);

    /**
     * @brief Generates random centers on the map.
     * @param num
     */
    void generateRandomPoints(int num);

    /**
     * @brief Returns the generated cities.
     * @return vector of points of cities.
     */
    [[nodiscard]] std::vector<Point> getCities() const;

    /**
     * @brief Applies Lloyd's algorithm for point relaxation.
     * @param iterations The number of iterations to perform.
     */
    void applyLloydRelaxation(int iterations);

    /**
     * @brief Applies city icons to the map.
     */
    void applyCityIcons();
};

