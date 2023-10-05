//
// Created by daniel on 1.10.23.
//

#ifndef SEMESTRAL_MAP_H
#define SEMESTRAL_MAP_H

#include <vector>
#include <iostream>
#include <random>
#include "Tile.h"

class Map {
private:
    struct Point() {
        int x, y;
        Point(int x, int y): x(x), y(y) {}
        bool operator == (const Point& other) const {
            return x == other.x && y == other.y;
        }
    }
    struct PointHash {
        std::size_t operator()(const Point& point) const {
            return point.x *31 + point.y;
        }
    };
    std::vector<std::vector<Tile>> m_Grid;
    int m_Rows;
    int m_Cols;

    std::mt19937 gen;
    std::vector<Point> m_Cities;
    std::unordered_map<Point, Point, PointHash> dijskra(const Point& start);
public:
    Map(int rows, int cols, Tile defaultTile = Tile::GROUND);
    void setTile(int x, int y, Tile tile);
    Tile getTile(int x, int y) const;

    void printMap() const;
    void generateCities(int numCities);
    void generatePaths();

};

#endif //SEMESTRAL_MAP_H
