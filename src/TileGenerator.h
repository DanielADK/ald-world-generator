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
#include "CImageConnector.h"

class TileGenerator {
private:
    std::random_device m_RandomDevice;
    std::mt19937 m_Generator;

    CMap* m_Map;
    CTileConfig* m_Config;
    int img_num = 0;
    CImageConnector ic = CImageConnector();
public:
    explicit TileGenerator(CMap& map, CTileConfig& config);
    
    bool isValidPosition(int row, int col, ETile newTile) const;
    bool isValidPosition(int row, int col) const;
    std::vector<ETile> generatePossibleTiles(int row, int col) const;
    ETile selectRandomTile(const std::vector<ETile>& possibleTiles);
    ETile selectTileBasedOnRules(int row, int col);

    void generateTilesBFS();
    void generateTilesSequentially();
    void generateTilesDFS();
};


#endif //SEMESTRAL_TILEGENERATOR_H
