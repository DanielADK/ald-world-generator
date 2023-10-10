//
// Created by daniel on 1.10.23.
//

#ifndef SEMESTRAL_CMAP_H
#define SEMESTRAL_CMAP_H

#include <vector>
#include <iostream>
#include <random>
#include "CTile.h"
#include "CPoint.h"
#include "CTileConfig.h"

class CMap {
private:
    std::vector<std::vector<ETile>> m_Grid;
    CTileConfig* m_Config;
    int m_Rows;
    int m_Cols;

public:
    CMap(int rows, int cols, CTileConfig& tileConfig, ETile defaultTile = ETile::UNDEFINED);
    int getRows() const;
    int getCols() const;
    void setTile(int x, int y, const ETile tile);
    void setTile(const CPoint& point, ETile tile);
    [[nodiscard]] ETile getTile(int x, int y) const;
    [[nodiscard]] ETile getTile(const CPoint& point) const;


    void printMap() const;
};

#endif //SEMESTRAL_CMAP_H
