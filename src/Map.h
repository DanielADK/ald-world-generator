//
// Created by daniel on 1.10.23.
//

#ifndef SEMESTRAL_MAP_H
#define SEMESTRAL_MAP_H

#include <vector>
#include <iostream>
#include "Tile.h"

class Map {
private:
    std::vector<std::vector<Tile>> grid;
    int rows;
    int cols;
public:
    Map(int rows, int cols, Tile defaultTile = Tile::GROUND);
    void setTile(int x, int y, Tile tile);
    Tile getTile(int x, int y) const;
    void printMap() const;
};

#endif //SEMESTRAL_MAP_H
