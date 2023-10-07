//
// Created by daniel on 1.10.23.
//

#ifndef SEMESTRAL_MAP_H
#define SEMESTRAL_MAP_H

#include <vector>
#include <iostream>
#include <random>
#include "CTile.h"

class Map {
private:
    std::vector<std::vector<CTile>> m_Grid;
    int m_Rows;
    int m_Cols;

public:
    Map(int rows, int cols, CTile defaultTile = CTile(ETile::GROUND, "data/img/ground.png"));
    void setTile(int x, int y, CTile& tile);
    CTile getTile(int x, int y) const;

    void printMap() const;
};

#endif //SEMESTRAL_MAP_H
