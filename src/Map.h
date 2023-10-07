//
// Created by daniel on 1.10.23.
//

#ifndef SEMESTRAL_MAP_H
#define SEMESTRAL_MAP_H

#include <iostream>
#include <vector>
#include <cmath>
#include "Tile.h"
#include "Point.h"

class Map {
private:
    std::vector<std::vector<Tile>> m_Map;
    int m_Rows;
    int m_Cols;
public:

    /**
     * @brief Constructor of map
     * @param rows
     * @param cols
     * @param defaultTile
     */
    Map(int rows, int cols, Tile defaultTile = Tile::GROUND);
    void setTile(const int& x, const int& y, const Tile& tile);
    void setTile(const Point& point, const Tile& tile);
    [[nodiscard]] Tile getTile(const int& x, const int& y) const;
    [[nodiscard]] Tile getTile(const Point& point) const;
    int getRows() const;
    int getCols() const;
    void printMap() const;

    void generateRandomPaths(Point& start, Point& end);
    void applyCenters(std::vector<Point> centers);

};

#endif //SEMESTRAL_MAP_H
