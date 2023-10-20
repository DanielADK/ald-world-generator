#include <dirent.h>
#include <iostream>
#include "src/CMap.h"
#include "src/CTile.h"
#include "src/CMap.h"
#include "src/CTileConfig.h"
#include "src/CTileGenerator.h"
#include "opencv2/opencv.hpp"
#include "src/CImageConnector.h"

#define CONFIG "./tile_config_without_ends.cfg"

int main() {

    CTileConfig tileConfig;

    std::cout << "Loading config from..." << CONFIG << std::endl << std::endl;
    if (tileConfig.loadConfig(CONFIG))
        std::cout << "Config file loaded successfully." << std::endl;
    else
        throw std::invalid_argument("Failed to load config file.");

    tileConfig.printLoadedTiles();

    auto map = CMap(51, 51, tileConfig);

    std::vector<std::vector<bool>> visited(map.getRows(), std::vector<bool>(map.getCols(), false));
    auto generator = CTileGenerator(map, tileConfig);

    generator.generateTilesDFS(0,0, visited);
    //generator.generateTilesBFS();

    std::cout << "Generating image..." << std::endl;
    auto ic = CImageConnector();
    ic.processMap(map, tileConfig.getAllTileConfig());
    ic.exportResult("./result.png");

    return 0;
}
