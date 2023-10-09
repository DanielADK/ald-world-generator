//
// Created by daniel on 1.10.23.
//

#ifndef SEMESTRAL_MAP_H
#define SEMESTRAL_MAP_H

#include <vector>
#include <iostream>
#include <random>
#include "CTile.h"
#include "Point.h"

class Map {
private:
    std::vector<std::vector<ETile>> m_Grid;
    int m_Rows;
    int m_Cols;

public:
    Map(int rows, int cols, ETile defaultTile = ETile::UNDEFINED);
    int getRows() const;
    int getCols() const;
    void setTile(int x, int y, const ETile tile);
    void setTile(const Point& point, ETile tile);
    [[nodiscard]] ETile getTile(int x, int y) const;
    [[nodiscard]] ETile getTile(const Point& point) const;


    void printMap() const;
};

#endif //SEMESTRAL_MAP_H
