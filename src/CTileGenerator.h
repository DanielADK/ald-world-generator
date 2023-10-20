//
// Created by daniel on 7.10.23.
//

#ifndef SEMESTRAL_CTILEGENERATOR_H
#define SEMESTRAL_CTILEGENERATOR_H

#include <random>
#include <unordered_map>
#include <queue>
#include <vector>
#include "CTileConfig.h"
#include "CMap.h"
#include "CImageConnector.h"

class CTileGenerator {
private:
    std::random_device m_RandomDevice;
    std::mt19937 m_Generator;

    CMap* m_Map;
    CTileConfig* m_Config;
    CImageConnector ic = CImageConnector();
public:
    explicit CTileGenerator(CMap& map, CTileConfig& config);
    
    [[nodiscard]] bool isValidPosition(int row, int col, ETile newTile) const;
    [[nodiscard]] bool isValidPosition(int row, int col) const;
    [[nodiscard]] std::vector<ETile> generatePossibleTiles(int row, int col) const;
    ETile selectRandomTile(const std::vector<ETile>& possibleTiles);
    ETile selectTileBasedOnRules(int row, int col);

    void generateTilesBFS();
    bool generateTilesDFS(const int& row, const int& col, std::vector<std::vector<bool>>& visited);
};


#endif //SEMESTRAL_CTILEGENERATOR_H
