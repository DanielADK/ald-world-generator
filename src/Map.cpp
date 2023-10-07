#include <unordered_set>
#include <queue>
#include <memory>
#include "Map.h"
#include "Point.h"

Map::Map(int rows, int cols, Tile defaultTile) : m_Rows(rows), m_Cols(cols) {
    m_Map.resize(rows, std::vector<Tile>(cols, defaultTile));
}

void Map::setTile(const int& x, const int& y, const Tile& tile) {
    if (x >= 0 && x < m_Rows && y >= 0 && y < m_Cols) m_Map[x][y] = tile;
}

void Map::setTile(const Point& point, const Tile& tile) {
    setTile(point.x, point.y, tile);
}

Tile Map::getTile(const int& x, const int& y) const {
    return (x >= 0 && x < m_Rows && y >= 0 && y < m_Cols) ? m_Map[x][y] : Tile::ERROR;
}

Tile Map::getTile(const Point& point) const {
    return getTile(point.x, point.y);
}

int Map::getRows() const {
    return m_Rows;
}

int Map::getCols() const {
    return m_Cols;
}

void Map::printMap() const {
    setlocale(LC_ALL, "");
    for (const auto& row : m_Map) {
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
                case Tile::CITY:
                    std::cout << 'C';
                    break;
            }
        }
        std::cout << std::endl;
    }
}

struct Node {
    Point point;
    int distance;
    Node(Point p, int d) : point(p), distance(d) {}
};

struct CompareNode {
    bool operator()(Node const& n1, Node const& n2) const {
        return n1.distance > n2.distance;
    }
};

void Map::generateRandomPaths(Point& start, Point& end) {
    std::priority_queue<Node, std::vector<Node>, CompareNode> pq;
    std::vector<std::vector<int>> distances(m_Rows, std::vector<int>(m_Cols, INT_MAX));
    std::vector<std::vector<Point>> previous(m_Rows, std::vector<Point>(m_Cols, {-1, -1}));

    pq.emplace(start, 0);
    distances[start.x][start.y] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.point.x == end.x && current.point.y == end.y) {
            break;
        }

        std::vector<Point> neighbors = {
            {current.point.x + 1, current.point.y},
            {current.point.x - 1, current.point.y},
            {current.point.x, current.point.y + 1},
            {current.point.x, current.point.y - 1}
        };

        for (auto& neighbor : neighbors) {
            if (neighbor.x >= 0 && neighbor.x < m_Rows && neighbor.y >= 0 && neighbor.y < m_Cols) {
                int newDist = distances[current.point.x][current.point.y] + 1; // Assuming all edges have weight=1
                if (newDist < distances[neighbor.x][neighbor.y]) {
                    pq.emplace(neighbor, newDist);
                    distances[neighbor.x][neighbor.y] = newDist;
                    previous[neighbor.x][neighbor.y] = current.point;
                }
            }
        }
    }

    // Trace back the path
    Point p = end;
    while (previous[p.x][p.y].x != -1) {
        setTile(p.x, p.y, Tile::PATH_CROSS);
        p = previous[p.x][p.y];
    }
    setTile(start.x, start.y, Tile::PATH_CROSS);
    setTile(end.x, end.y, Tile::PATH_CROSS);
}

void Map::applyCenters(std::vector<Point> centers) {
    for (const Point& point : centers) setTile(point.x, point.y, Tile::CITY);
}
