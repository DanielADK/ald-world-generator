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

    CTileConfig tileList;

    if (tileList.loadConfig("./tile_config.cfg"))
        std::cout << "Config file loaded successfully." << std::endl;
    else
        throw std::invalid_argument("Failed to load config file.");

    auto map = CMap(11, 11);

    auto generator = TileGenerator(map, tileList);
    generator.generateTilesBFS();
    map.printMap();

    auto ic = CImageConnector();
    ic.processMap(map, tileList.getAllTileConfigs());
    ic.exportResult("./result.png");

    return 0;

    /*
        // Načtení obrázku
    cv::Mat originalImage = cv::imread("../data/img/ground.png");

    // Ověření, zda byl obrázek úspěšně načten
    if (originalImage.empty()) {
        std::cerr << "Nepodařilo se načíst původní obrázek." << std::endl;
        return 1;
    }

    // Vytvoření kopie obrázku
    cv::Mat copiedImage = originalImage.clone();

    // Ověření, zda byla kopie úspěšně vytvořena
    if (copiedImage.empty()) {
        std::cerr << "Nepodařilo se vytvořit kopii obrázku." << std::endl;
        return 1;
    }

    // Uložení kopie obrázku
    if (!cv::imwrite("../a.png", copiedImage)) {
        std::cerr << "Nepodařilo se uložit kopii obrázku." << std::endl;
        return 1;
    }

    std::cout << "Kopie obrázku byla úspěšně uložena." << std::endl;
    return 0;
    */
}
