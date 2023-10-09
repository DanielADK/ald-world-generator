#include <queue>
#include <unordered_map>
#include <map>
#include <set>
#include "Map.h"
#include "Point.h"

Map::Map(int rows, int cols, ETile defaultTile) : m_Rows(rows), m_Cols(cols) {
    m_Grid.resize(rows, std::vector<ETile>(cols, defaultTile));
}

void Map::setTile(int x, int y, ETile tile) {
    if (x >= 0 && x < m_Rows && y >= 0 && y < m_Cols) m_Grid[x][y] = tile;
}

void Map::setTile(const Point& point, const ETile tile) {
    setTile(point.getX(), point.getY(), tile);
}

ETile Map::getTile(int x, int y) const {
    return (x >= 0 && x < m_Rows && y >= 0 && y < m_Cols) ? m_Grid[x][y] : ETile::ERROR;
}

ETile Map::getTile(const Point& point) const {
    return getTile(point.getX(), point.getY());
}

int Map::getRows() const { return m_Rows; }
int Map::getCols() const { return m_Cols; }


void Map::printMap() const {
    using enum ETile;
    for (const std::vector<ETile>& row : m_Grid) {
        for (const ETile& tile : row) {
            switch (tile) {
                case GROUND:
                    std::cout << ' ';
                    break;
                case TREE:
                    std::cout << 'T';
                    break;
                case GRASS:
                    std::cout << '.';
                    break;
                case PATH_CROSS:
                    std::cout << "+";
                    break;
                case PATH_ENDDOWN:
                    std::cout << '^';
                    break;
                case PATH_ENDLEFT:
                    std::cout << '>';
                    break;
                case PATH_ENDRIGHT:
                    std::cout << '<';
                    break;
                case PATH_ENDUP:
                    std::cout << 'V';
                    break;
                case PATH_UPDOWN:
                    std::cout << '|';
                    break;
                case PATH_RIGHTLEFT:
                    std::cout << '-';
                    break;
                case CITY:
                    std::cout << 'C';
                    break;
                case ERROR:
                    std::cout << 'E';
                    break;
                case UNDEFINED:
                    std::cout << 'U';
                    break;
            }
        }
        std::cout << std::endl;
    }
}


