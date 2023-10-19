//
// Created by daniel on 7.10.23.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include "CTileConfig.h"

bool CTileConfig::loadConfig(const std::string &path) {
    std::ifstream file(path);

    // Is file available?
    if (!file.is_open())
        throw std::invalid_argument("Can't open config file at: " + path);

    ETile currentType = ETile::ERROR;
    std::string imagePath;
    std::unordered_set<ETile> top;
    std::unordered_set<ETile>right;
    std::unordered_set<ETile> bottom;
    std::unordered_set<ETile> left;

    std::string line;
    std::string symbol;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        std::string value;
        std::getline(iss, key, ':');
        std::getline(iss, value);

        if (key == "name")
            currentType = stringToETile(value);
        else if (key == "symbol")
            symbol = trimWhitespace(value);
        else if (key == "image")
            imagePath = trimWhitespace(value);
        else if (key == "top")
            top = stringToETileVector(value);
        else if (key == "right")
            right = stringToETileVector(value);
        else if (key == "bottom")
            bottom = stringToETileVector(value);
        else if (key == "left")
            left = stringToETileVector(value);

        if (line.empty()) {
            if (currentType == ETile::ERROR ||
                    imagePath.empty() ||
                    symbol.empty() ||
                    !verifyPath(imagePath))
                std::cerr << "Unsuccessful tile loading at:" << imagePath << " SYMBOL:" << symbol << " PŘESKAKUJI";
            else
                m_TileConfigs.try_emplace(currentType, currentType, symbol, imagePath, top, right, bottom, left);

            currentType = ETile::ERROR;
            imagePath = "";
            symbol = "";
        }

    }
    file.close();

    // Pick path tiles
    m_PathTiles = filterPathTiles();
    return true;
}

CTile CTileConfig::getTileConfig(ETile tileType) const {
    if (auto it = m_TileConfigs.find(tileType); it != m_TileConfigs.end()) {
        return it->second;
    }
    return CTile(ETile::ERROR);
}

const std::unordered_map<ETile, CTile>& CTileConfig::getAllTileConfig() const {
    return m_TileConfigs;
}

const std::unordered_map<ETile, CTile>& CTileConfig::getPathTileConfig() const {
    return m_PathTiles;
}

void CTileConfig::printLoadedTiles() const {
    std::cout << "Načtené dlaždice:\n";
    for (const auto& [enum_type, tile] : m_TileConfigs)
        std::cout << "  " << tile.getImagePath() << std::endl;
}

std::unordered_map<ETile, CTile> CTileConfig::filterPathTiles() const {
    std::unordered_map<ETile, CTile> result;
    for (const auto& [enum_type, tile] : m_TileConfigs) {
        if (tile.getImagePath().find("path") != std::string::npos)
            result.try_emplace(enum_type, tile);
    }
    return result;
}

ETile CTileConfig::stringToETile(const std::string& str) {
    using enum ETile;
    std::string trimmed = trimWhitespace(str);
    static const std::unordered_map<std::string_view, ETile, StringHash, std::equal_to<>> map = {
        {"GROUND", GROUND},
        {"TREE", TREE},
        {"GRASS", GRASS},
        {"CITY", CITY},
        {"CAT", CAT},
        {"PATH_CROSS", PATH_CROSS},
        {"PATH_UPDOWN", PATH_UPDOWN},
        {"PATH_RIGHTLEFT", PATH_RIGHTLEFT},
        {"PATH_ENDLEFT", PATH_ENDLEFT},
        {"PATH_ENDUP", PATH_ENDUP},
        {"PATH_ENDRIGHT", PATH_ENDRIGHT},
        {"PATH_ENDDOWN", PATH_ENDDOWN},
        {"PATH_LEFTDOWN", PATH_LEFTDOWN},
        {"PATH_RIGHTDOWN", PATH_RIGHTDOWN},
        {"PATH_LEFTUP", PATH_LEFTUP},
        {"PATH_RIGHTUP", PATH_RIGHTUP},
        {"ERROR", ERROR},
        {"UNDEFINED", UNDEFINED}
    };

    if (auto it = map.find(trimmed); it != map.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid tile type: " + str);
}

std::unordered_set<ETile> CTileConfig::stringToETileVector(const std::string& str) {
    std::unordered_set<ETile> result;
    std::istringstream iss(str);
    std::string token;

    while (iss >> token) {
        ETile tile = CTileConfig::stringToETile(token);
        if (tile != ETile::ERROR)
            result.insert(tile);
    }

    return result;
}

std::string CTileConfig::trimWhitespace(std::string str) {
    std::erase(str, ' ');
    return str;
}

bool CTileConfig::verifyPath(const std::string& path) {
    if (std::ifstream file(path); file.rdstate() == std::ios_base::goodbit)
        return true;
    else if (file.rdstate() & std::ios_base::badbit)
        std::cerr << "Critical I/O error while verifying path: " << path << "\n";
    else if (file.rdstate() & std::ios_base::failbit)
        std::cerr << "Non-critical I/O error while verifying path: " << path << "\n";
    else if (file.rdstate() & std::ios_base::eofbit)
        std::cerr << "EOFBIT error. Corrupted file while verifying path: " << path << "\n";
    else
        std::cerr << "Undefined error while verifying path: " << path << "\n";
    return false;
}

