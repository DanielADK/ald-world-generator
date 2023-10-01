#include "Map.h"

Map::Map(int rows, int cols, Tile defaultTile) : rows(rows), cols(cols) {
    grid.resize(rows, std::vector<Tile>(cols, defaultTile));
}

void Map::setTile(int x, int y, Tile tile) {
    if (x >= 0 && x < rows && y >= 0 && y < cols) grid[x][y] = tile;
}

Tile Map::getTile(int x, int y) const {
    return (x >= 0 && x < rows && y >= 0 && y < cols) ? grid[x][y] : Tile::ERROR;
}

void Map::printMap() const {
    for (const auto& row : grid) {
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
                    std::cout << '+';
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
            }
        }
        std::cout << std::endl;
    }
}
