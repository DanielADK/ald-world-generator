#include <queue>
#include <unordered_map>
#include <map>
#include <set>
#include "Map.h"

Map::Map(int rows, int cols, Tile defaultTile) : m_Rows(rows), m_Cols(cols) {
    m_Grid.resize(rows, std::vector<Tile>(cols, defaultTile));

    // Random device generator
    std::random_device rd;
    gen = std::mt19937(rd());
}

void Map::setTile(int x, int y, Tile tile) {
    if (x >= 0 && x < m_Rows && y >= 0 && y < m_Cols) m_Grid[x][y] = tile;
}

Tile Map::getTile(int x, int y) const {
    return (x >= 0 && x < m_Rows && y >= 0 && y < m_Cols) ? m_Grid[x][y] : Tile::ERROR;
}

void Map::printMap() const {
    for (const auto& row : m_Grid) {
        for (const auto& tile : row) {
            switch (tile) {
                case Tile::GROUND:
                    std::cout << ' ';
                    break;
                case Tile::TREE:
                    std::cout << '#';
                    break;
                case Tile::GRASS:
                    std::cout << '.';
                    break;
                case Tile::PATH_CROSS:
                    std::cout << "█";
                    break;
                case Tile::PATH_ENDDOWN:
                    std::cout << 'V';
                    break;
                case Tile::PATH_ENDLEFT:
                    std::cout << '>';
                    break;
                case Tile::PATH_ENDRIGHT:
                    std::cout << '<';
                    break;
                case Tile::PATH_ENDUP:
                    std::cout << '^';
                    break;
                case Tile::PATH_UPDOWN:
                    std::cout << '|';
                    break;
                case Tile::PATH_RIGHTLEFT:
                    std::cout << '-';
                    break;
                case Tile::CITY:
                    std::cout << 'H';
                    break;
            }
        }
        std::cout << std::endl;
    }
}

