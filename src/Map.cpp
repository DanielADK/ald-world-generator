#include <queue>
#include <unordered_map>
#include <map>
#include <set>
#include "Map.h"

Map::Map(int rows, int cols, CTile defaultTile) : m_Rows(rows), m_Cols(cols) {
    m_Grid.resize(rows, std::vector<CTile>(cols, defaultTile));
}

void Map::setTile(int x, int y, CTile& tile) {
    if (x >= 0 && x < m_Rows && y >= 0 && y < m_Cols) m_Grid[x][y] = tile;
}

CTile Map::getTile(int x, int y) const {
    return (x >= 0 && x < m_Rows && y >= 0 && y < m_Cols) ? m_Grid[x][y] : CTile(ETile::ERROR, "data/img/error.png");
}

/*
void Map::printMap() const {
    for (const auto& row : m_Grid) {
        for (const auto& tile : row) {
            switch (tile) {
                case ETile::GROUND:
                    std::cout << ' ';
                    break;
                case ETile::TREE:
                    std::cout << '#';
                    break;
                case ETile::GRASS:
                    std::cout << '.';
                    break;
                case ETile::PATH_CROSS:
                    std::cout << "█";
                    break;
                case ETile::PATH_ENDDOWN:
                    std::cout << 'V';
                    break;
                case ETile::PATH_ENDLEFT:
                    std::cout << '>';
                    break;
                case ETile::PATH_ENDRIGHT:
                    std::cout << '<';
                    break;
                case ETile::PATH_ENDUP:
                    std::cout << '^';
                    break;
                case ETile::PATH_UPDOWN:
                    std::cout << '|';
                    break;
                case ETile::PATH_RIGHTLEFT:
                    std::cout << '-';
                    break;
                case ETile::CITY:
                    std::cout << 'H';
                    break;
            }
        }
        std::cout << std::endl;
    }
}
 */

