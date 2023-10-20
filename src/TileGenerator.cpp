//
// Created by daniel on 7.10.23.
//

#include "TileGenerator.h"

#include <utility>
#include <stack>
#include "CMap.h"
#include "CPoint.h"
#include "CImageConnector.h"

TileGenerator::TileGenerator(CMap& map, CTileConfig& config) : m_Generator(m_RandomDevice()), m_Map(&map), m_Config(&config) {
}

bool TileGenerator::isValidPosition(int row, int col, ETile newTile) const {
    // Check for corner tiles
    if ((row == 0 && col == 0) ||
        (row == 0 && col == m_Map->getCols() - 1) ||
        (row == m_Map->getRows() - 1 && col == 0) ||
        (row == m_Map->getRows() - 1 && col == m_Map->getCols() - 1)) {
        return true;
    }

    // Is out of bounds
    if (row < 0 || row >= m_Map->getRows() || col < 0 || col >= m_Map->getCols())
        return false;

    // Get the existing tile at this position
    ETile existingTile = m_Map->getTile(row, col);

    // Retrieve the tile configurations for both existing and new tiles
    CTile existingTileConfig = m_Config->getTileConfig(existingTile);

    // Check if the new tile can be placed next to the existing tile based on their configurations
    if (CTile newTileConfig = m_Config->getTileConfig(newTile);
        existingTileConfig.isPossibleRight(newTile) && newTileConfig.isPossibleLeft(existingTile) &&
        existingTileConfig.isPossibleTop(newTile) && newTileConfig.isPossibleBottom(existingTile) &&
        existingTileConfig.isPossibleBottom(newTile) && newTileConfig.isPossibleTop(existingTile) &&
        existingTileConfig.isPossibleLeft(newTile) && newTileConfig.isPossibleRight(existingTile)) {
        return true;
    }

    return false;
}

bool TileGenerator::isValidPosition(int x, int y) const {
    return isValidPosition(x, y, m_Map->getTile(x, y));
}

std::vector<ETile> TileGenerator::generatePossibleTiles(int row, int col) const {
    std::vector<ETile> possibleTiles;
    auto topPoint = CPoint(row - 1, col);
    auto rightPoint = CPoint(row, col + 1);
    auto bottomPoint = CPoint(row + 1, col);
    auto leftPoint = CPoint(row, col - 1);

    for (const auto& [tileType, tileConfig] : m_Config->getPathTileConfig()) {
        if ((tileConfig.isPossibleTop(m_Map->getTile(topPoint))) &&
            (tileConfig.isPossibleRight(m_Map->getTile(rightPoint))) &&
            (tileConfig.isPossibleBottom(m_Map->getTile(bottomPoint))) &&
            (tileConfig.isPossibleLeft(m_Map->getTile(leftPoint)))) {
            possibleTiles.push_back(tileType);
        }
    }

    return possibleTiles;
}

ETile TileGenerator::selectRandomTile(const std::vector<ETile>& possibleTiles) {
    if (possibleTiles.empty()) return ETile::ERROR;

    // Shortcut for only one possible tile
    if (possibleTiles.size() == 1) return possibleTiles[0];

    std::uniform_int_distribution<int> distribution(0, possibleTiles.size() - 1);
    return possibleTiles[distribution(m_Generator)];
}

ETile TileGenerator::selectTileBasedOnRules(int row, int col) {
    std::vector<ETile> possibleTiles = generatePossibleTiles(row, col);
    return selectRandomTile(possibleTiles);
}

void TileGenerator::generateTilesBFS() {
    std::queue<std::pair<int, int>> bfsQueue;
    std::vector<std::vector<bool>> visited(m_Map->getRows(), std::vector<bool>(m_Map->getCols(), false));

    bfsQueue.emplace(0, 0);
    visited[0][0] = true;

    while (!bfsQueue.empty()) {
        auto [row, col] = bfsQueue.front();
        bfsQueue.pop();

        if (m_Map->getTile(row, col) == ETile::UNDEFINED) {
            std::queue<ETile> tileQueue;
            std::vector<ETile> possibleTiles = generatePossibleTiles(row, col);
            std::shuffle(possibleTiles.begin(), possibleTiles.end(), m_Generator);
            for (const auto& tile : possibleTiles) tileQueue.push(tile);

            if (!tileQueue.empty()) {
                ETile selectedTile = tileQueue.front();
                tileQueue.pop();
                m_Map->setTile(row, col, selectedTile);
            }
        }

        std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (auto [dx, dy] : directions) {
            int newRow = row + dx, newCol = col + dy;
            if (newRow >= 0 && newRow < m_Map->getRows() && newCol >= 0 && newCol < m_Map->getCols() && !visited[newRow][newCol]) {
                bfsQueue.emplace(newRow, newCol);
                visited[newRow][newCol] = true;
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

void TileGenerator::generateTilesDFS() {
    std::stack<std::pair<int, int>> dfsStack;
    std::vector<std::vector<bool>> visited(m_Map->getRows(), std::vector<bool>(m_Map->getCols(), false));

    dfsStack.emplace(0, 0);
    visited[0][0] = true;

    while (!dfsStack.empty()) {
        auto [row, col] = dfsStack.top();
        dfsStack.pop();

        if (m_Map->getTile(row, col) == ETile::UNDEFINED) {
            std::queue<ETile> tileQueue;
            std::vector<ETile> possibleTiles = generatePossibleTiles(row, col);
            std::shuffle(possibleTiles.begin(), possibleTiles.end(), m_Generator);
            for (const auto& tile : possibleTiles) tileQueue.push(tile);

            if (!tileQueue.empty()) {
                ETile selectedTile = tileQueue.front();
                tileQueue.pop();
                m_Map->setTile(row, col, selectedTile);
            }
        }

        std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (auto [dx, dy] : directions) {
            int newRow = row + dx, newCol = col + dy;
            if (newRow >= 0 && newRow < m_Map->getRows() && newCol >= 0 && newCol < m_Map->getCols() && !visited[newRow][newCol]) {
                dfsStack.emplace(newRow, newCol);
                visited[newRow][newCol] = true;
            }
        }
    }
}



