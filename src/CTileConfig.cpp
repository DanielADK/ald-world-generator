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
    std::ifstream configFile(path);
    if (!configFile.is_open()) {
        std::cerr << "Could not open config file: " << path << std::endl;
        return false;
    }

    std::string line;
    ETile currentType = ETile::ERROR;
    std::string imagePath;
    std::vector<ETile> top;
    std::vector<ETile> right;
    std::vector<ETile> bottom;
    std::vector<ETile> left;

    while (std::getline(configFile, line)) {
        if (line.empty()) {
            if (currentType != ETile::ERROR) {
                m_TileConfigs[currentType] = CTile(currentType, imagePath, top, right, bottom, left);
            }
            continue;
        }

        std::istringstream iss(line);
        std::string key;
        std::string value;
        std::getline(iss, key, ':');
        std::getline(iss, value);

        if (key == "name") {
            currentType = stringToETile(value);
        } else if (key == "image") {
            imagePath = value;
        } else if (key == "top") {
            top = stringToETileVector(value);
        } else if (key == "right") {
            right = stringToETileVector(value);
        } else if (key == "bottom") {
            bottom = stringToETileVector(value);
        } else if (key == "left") {
            left = stringToETileVector(value);
        }
    }

    // Add the last tile configuration if it exists
    if (currentType != ETile::ERROR) {
        m_TileConfigs[currentType] = CTile(currentType, imagePath, top, right, bottom, left);
    }

    configFile.close();
    return true;
}

CTile CTileConfig::getTileConfig(ETile tileType) const {
    if (auto it = m_TileConfigs.find(tileType); it != m_TileConfigs.end()) {
        return it->second;
    }
    return CTile(ETile::ERROR);
}

ETile CTileConfig::stringToETile(const std::string& str) {
    std::string trimmed = trimWhitespace(str);
    static const std::unordered_map<std::string, ETile> map = {
        {"GROUND", ETile::GROUND},
        {"TREE", ETile::TREE},
        {"GRASS", ETile::GRASS},
        {"CITY", ETile::CITY},
        {"CAT", ETile::CAT},
        {"PATH_CROSS", ETile::PATH_CROSS},
        {"PATH_UPDOWN", ETile::PATH_UPDOWN},
        {"PATH_RIGHTLEFT", ETile::PATH_RIGHTLEFT},
        {"PATH_ENDLEFT", ETile::PATH_ENDLEFT},
        {"PATH_ENDUP", ETile::PATH_ENDUP},
        {"PATH_ENDRIGHT", ETile::PATH_ENDRIGHT},
        {"PATH_ENDDOWN", ETile::PATH_ENDDOWN},
        {"PATH_LEFTDOWN", ETile::PATH_LEFTDOWN},
        {"PATH_RIGHTDOWN", ETile::PATH_RIGHTDOWN},
        {"PATH_LEFTUP", ETile::PATH_LEFTUP},
        {"PATH_RIGHTUP", ETile::PATH_RIGHTUP}
    };

    if (auto it = map.find(trimmed); it != map.end()) {
        return it->second;
    }
    return ETile::ERROR;
}

std::vector<ETile> CTileConfig::stringToETileVector(const std::string& str) {
    std::vector<ETile> result;
    std::istringstream iss(str);
    std::string token;

    while (iss >> token) {
        ETile tile = CTileConfig::stringToETile(token);
        if (tile != ETile::ERROR)
            result.push_back(tile);
    }

    return result;
}

std::string CTileConfig::trimWhitespace(std::string_view str) {
    std::string trimmed;
    std::ranges::copy_if(str.begin(), str.end(), std::back_inserter(trimmed), [](unsigned char c) {
        return !std::isspace(c);
    });
    return trimmed;
}

