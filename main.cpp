#include "src/Map.h"
#include "src/Tile.h"
#include "src/Map.h"

int main() {
    Map myMap(20, 20, Tile::GROUND);
    myMap.generateCities(5);
    myMap.generatePaths();
    myMap.printMap();
    return 0;
}
