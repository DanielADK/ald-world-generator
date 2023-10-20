#include <dirent.h>
#include <iostream>
#include "src/CMap.h"
#include "src/CTile.h"
#include "src/CMap.h"
#include "src/CTileConfig.h"
#include "src/TileGenerator.h"
#include "opencv2/opencv.hpp"
#include "src/CImageConnector.h"

int main() {

    CTileConfig tileConfig;

    if (tileConfig.loadConfig("./tile_config.cfg"))
        std::cout << "Config file loaded successfully." << std::endl;
    else
        throw std::invalid_argument("Failed to load config file.");

    tileConfig.printLoadedTiles();

    auto map = CMap(501, 501, tileConfig);

    std::vector<std::vector<bool>> visited(map.getRows(), std::vector<bool>(map.getCols(), false));

    auto generator = TileGenerator(map, tileConfig);

    generator.generateTilesDFS();
    map.printMap();

    auto ic = CImageConnector();
    ic.processMap(map, tileConfig.getAllTileConfig());
    ic.exportResult("./result.png");

    return 0;
}
