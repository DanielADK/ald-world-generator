//
// Created by daniel on 6.10.23.
//

#include "CityGenerator.h"

CityGenerator::CityGenerator(Map &map): m_Map(map) {}

std::vector<Point> CityGenerator::getCities() const { return m_Cities; }
/**
 * @brief Generates random centers on the map.
 * @param num
 */
void CityGenerator::generateRandomPoints(int num) {    // Initialize random engine and distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rowDist(0, m_Map.getRows() - 1);
    std::uniform_int_distribution<> colDist(0, m_Map.getCols() - 1);

    for (int i = 0; i < num; ++i) {
        int x = rowDist(gen);
        int y = colDist(gen);
        m_Cities.emplace_back(x, y);
    }
}

/**
 * @brief Computes the centroid of a set of points.
 * @param points The set of points.
 * @return The centroid point.
 */
Point CityGenerator::computeCentroid(const std::vector<Point>& points) {
    int sumX = 0;
    int sumY = 0;
    for (const auto& point : points) {
        sumX += point.x;
        sumY += point.y;
    }
    return { int(sumX / points.size()), int(sumY / points.size()) };
}

/**
 * @brief Applies Lloyd's algorithm for point relaxation.
 * @param centers The initial set of points (centers).
 * @param map The map on which to apply the algorithm.
 * @param iterations The number of iterations to perform.
 */
void CityGenerator::applyLloydRelaxation(int iterations) {
    for (int k = 0; k < iterations; ++k) {
        // Create a 2D array to hold the closest center for each point on the map
        std::vector<std::vector<Point>> closestCenters(m_Map.getRows(), std::vector<Point>(m_Map.getCols()));

        // Step 1: Assign each point on the map to the nearest center
        for (int i = 0; i < m_Map.getRows(); ++i) {
            for (int j = 0; j < m_Map.getCols(); ++j) {
                Point point = { i, j };
                Point closestCenter = m_Cities[0];
                double minDist = point.distanceTo(closestCenter);

                for (const auto& center : m_Cities) {
                    double dist = point.distanceTo(center);
                    if (dist < minDist) {
                        closestCenter = center;
                        minDist = dist;
                    }
                }

                closestCenters[i][j] = closestCenter;
            }
        }

        // Step 2: Move each center to the centroid of its Voronoi cell
        std::unordered_map<Point, std::vector<Point>> voronoiCells;
        for (int i = 0; i < m_Map.getRows(); ++i)
            for (int j = 0; j < m_Map.getCols(); ++j)
                voronoiCells[closestCenters[i][j]].emplace_back(i, j);

        for (auto& center : m_Cities)
            if (voronoiCells.contains(center))
                center = computeCentroid(voronoiCells[center]);
    }
}

/**
 * @brief Applies city icons to the map
 */
 void CityGenerator::applyCityIcons() {
    for (const auto& point : m_Cities)
        m_Map.setTile(point, Tile::CITY);
 }
