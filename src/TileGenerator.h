//
// Created by daniel on 7.10.23.
//

#ifndef SEMESTRAL_TILEGENERATOR_H
#define SEMESTRAL_TILEGENERATOR_H

#include <random>
#include <unordered_map>
#include <queue>
#include <vector>
#include "CTileConfig.h"
#include "CMap.h"

class TileGenerator {
private:
    std::random_device m_RandomDevice;
    std::mt19937 m_Generator;

    CMap* m_Map;
    CTileConfig* m_Config;
public:
    explicit TileGenerator(CMap& map, CTileConfig& config);
    
    ETile selectTileBasedOnRules(int row, int col);
    bool isValidPosition(int row, int col, ETile newTile) const;
    bool isValidPosition(int row, int col) const;
    void generateTilesBFS();
    void generateTilesSequentially();
};


#endif //SEMESTRAL_TILEGENERATOR_H
