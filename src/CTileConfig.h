//
// Created by daniel on 7.10.23.
//

#ifndef SEMESTRAL_CTILECONFIG_H
#define SEMESTRAL_CTILECONFIG_H

#include <unordered_map>
#include <string>
#include "CTile.h"

class CTileConfig {
private:
    std::unordered_map<ETile, CTile> m_TileConfigs;

public:
    bool loadConfig(const std::string& path);
    CTile getTileConfig(ETile tileType) const;

    static ETile stringToETile(const std::string& str);
    static std::vector<ETile> stringToETileVector(const std::string& str);
    static std::string trimWhitespace(std::string_view str);
};


#endif //SEMESTRAL_CTILECONFIG_H
