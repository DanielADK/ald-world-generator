//
// Created by daniel on 7.10.23.
//

#ifndef SEMESTRAL_CTILECONFIG_H
#define SEMESTRAL_CTILECONFIG_H

#include <unordered_map>
#include <unordered_set>
#include "CTile.h"

class CTileConfig {
private:
    std::unordered_map<ETile, CTile> m_TileConfigs;
    std::unordered_map<ETile, CTile> m_PathTiles;

public:
    bool loadConfig(const std::string& path);
    CTile getTileConfig(ETile tileType) const;
    const std::unordered_map<ETile, CTile>& getAllTileConfig() const;
    const std::unordered_map<ETile, CTile>& getPathTileConfig() const;
    void printLoadedTiles() const;
    std::unordered_map<ETile, CTile> filterPathTiles() const;


    static ETile stringToETile(const std::string& str);
    static std::unordered_set<ETile> stringToETileVector(const std::string& str);
    static std::string trimWhitespace(std::string str);
    static bool verifyPath(const std::string& path);

    struct StringHash {
        std::size_t operator()(const std::string& str) const {
            return std::hash<std::string_view>()(str);
        }
        std::size_t operator()(const std::string_view& str) const {
            return std::hash<std::string_view>()(str);
        }
    };;
};


#endif //SEMESTRAL_CTILECONFIG_H
