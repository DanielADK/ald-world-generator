#include "src/CMap.h"
#include "src/CTile.h"
#include "src/CMap.h"
#include "src/CTileConfig.h"
#include "src/TileGenerator.h"

int main() {
    CTileConfig tileList;

    if (tileList.loadConfig("../tile_config.cfg")) {
        std::cout << "Config file loaded successfully." << std::endl;

    } else {
        std::cerr << "Failed to load config file." << std::endl;
    }
    CMap map = CMap(10, 10);

    TileGenerator generator = TileGenerator(map, tileList);
    generator.generateTilesBFS();

    return 0;
}
