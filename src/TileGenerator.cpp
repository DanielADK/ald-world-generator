//
// Created by daniel on 7.10.23.
//

#include "TileGenerator.h"

#include <utility>
#include "CMap.h"
#include "CPoint.h"
#include "CImageConnector.h"

TileGenerator::TileGenerator(CMap& map, CTileConfig& config) : m_Generator(m_RandomDevice()), m_Map(&map), m_Config(&config) {}

bool TileGenerator::isValidPosition(int row, int col, ETile newTile) const {
    // Is out of bounds
    if (row < 0 || row >= m_Map->getRows() || col < 0 || col >= m_Map->getCols())
        return false;

    // Get the existing tile at this position
    ETile existingTile = m_Map->getTile(row, col);

    // Retrieve the tile configurations for both existing and new tiles
    CTile existingTileConfig = m_Config->getTileConfig(existingTile);
    CTile newTileConfig = m_Config->getTileConfig(newTile);

    // Check if the new tile can be placed next to the existing tile based on their configurations
    if (existingTileConfig.isPossibleRight(newTile) && newTileConfig.isPossibleLeft(existingTile)) {
        return true;
    }

    return false;
}

bool TileGenerator::isValidPosition(int x, int y) const {
    return isValidPosition(x, y, m_Map->getTile(x, y));
}

ETile TileGenerator::selectTileBasedOnRules(int row, int col) {
    // Získání sousedních dlaždic
    auto topPoint = CPoint(row - 1, col);
    auto rightPoint = CPoint(row, col + 1);
    auto bottomPoint = CPoint(row+1, col);
    auto leftPoint = CPoint(row, col - 1);

    // Vytvoření seznamu možných dlaždic na základě pravidel
    std::vector<ETile> possibleTiles;
    for (const auto& [tileType, tileConfig] : m_Config->getAllTileConfigs()) {
        if ((tileConfig.isPossibleTop(m_Map->getTile(topPoint))) &&
            (tileConfig.isPossibleRight(m_Map->getTile(rightPoint))) &&
            (tileConfig.isPossibleBottom(m_Map->getTile(bottomPoint))) &&
            (tileConfig.isPossibleLeft(m_Map->getTile(leftPoint)))) {
            possibleTiles.push_back(tileType);
        }
    }

    // Náhodný výběr z možných dlaždic
    if (!possibleTiles.empty()) {
        std::uniform_int_distribution<int> distribution(0, possibleTiles.size() - 1);
        return possibleTiles[distribution(m_Generator)];
    }

    return ETile::ERROR;
}


void TileGenerator::generateTilesBFS() {
    std::queue<std::pair<int, int>> bfsQueue;
    std::vector<std::vector<bool>> visited(m_Map->getRows(), std::vector<bool>(m_Map->getCols(), false));

    int startRow = m_Map->getRows() / 2;
    int startCol = m_Map->getCols() / 2;

    bfsQueue.emplace(startRow, startCol);
    m_Map->setTile(startRow, startCol, ETile::PATH_CROSS);
    visited[startRow][startCol] = true;

    std::vector<std::pair<int, int>> neighbors = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    CImageConnector ic;
    while (!bfsQueue.empty()) {

        auto [row, col] = bfsQueue.front();
        bfsQueue.pop();

        for (auto [dx, dy] : neighbors) {
            int newRow = row + dx;
            int newCol = col + dy;

            if (isValidPosition(newRow, newCol) && (!visited[newRow][newCol] || m_Map->getTile(newRow, newCol) == ETile::UNDEFINED)) {
                ETile selectedTile = selectTileBasedOnRules(newRow, newCol);
                if (selectedTile != ETile::ERROR) {
                    m_Map->setTile(newRow, newCol, selectedTile);
                    visited[newRow][newCol] = true;
                    bfsQueue.emplace(newRow, newCol);

                }
            }
        }
    }
}

void TileGenerator::generateTilesSequentially() {
    int maxRow = m_Map->getRows();
    int maxCol = m_Map->getCols();
    std::vector<std::vector<bool>> visited(maxRow, std::vector<bool>(maxCol, false));

    // Nastavit výchozí dlaždici
    m_Map->setTile(0, 0, ETile::GROUND);
    visited[0][0] = true;

    CImageConnector ic;

    for (int row = 0; row < maxRow; ++row) {
        for (int col = 0; col < maxCol; ++col) {
            if (!visited[row][col] || m_Map->getTile(row, col) == ETile::UNDEFINED) {
                ETile selectedTile = selectTileBasedOnRules(row, col);
                if (selectedTile != ETile::ERROR) {
                    m_Map->setTile(row, col, selectedTile);
                    visited[row][col] = true;
                }
            }
        }
    }
}



