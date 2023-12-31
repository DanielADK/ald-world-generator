//
// Created by daniel on 1.10.23.
//

#ifndef SEMESTRAL_CTILE_H
#define SEMESTRAL_CTILE_H

#include <string>
#include <unordered_set>

enum class ETile {
    GROUND,
    TREE,
    GRASS,
    CITY,
    CAT,
    PATH_CROSS,
    PATH_UPDOWN,
    PATH_RIGHTLEFT,
    PATH_ENDLEFT,
    PATH_ENDUP,
    PATH_ENDRIGHT,
    PATH_ENDDOWN,
    PATH_LEFTDOWN,
    PATH_RIGHTDOWN,
    PATH_LEFTUP,
    PATH_RIGHTUP,
    ERROR,
    UNDEFINED
};

class CTile {
private:
    ETile m_Type;
    std::string m_Symbol;
    std::string m_ImagePath;
    std::unordered_set<ETile> possibleTilesTop;
    std::unordered_set<ETile> possibleTilesRight;
    std::unordered_set<ETile> possibleTilesBottom;
    std::unordered_set<ETile> possibleTilesLeft;

public:
    CTile() = default;
    explicit CTile(const ETile& type);
    CTile(const ETile& type, std::string imagePath);
    CTile(const ETile& type,
         std::string symbol,
         std::string imagePath,
         std::unordered_set<ETile>& possibleTilesTop,
         std::unordered_set<ETile>& possibleTilesRight,
         std::unordered_set<ETile>& possibleTilesBottom,
         std::unordered_set<ETile>& possibleTilesLeft);

    bool isPossibleTop(ETile tile) const;
    bool isPossibleRight(ETile tile) const;
    bool isPossibleBottom(ETile tile) const;
    bool isPossibleLeft(ETile tile) const;
    std::string getImagePath() const;
};


#endif //SEMESTRAL_CTILE_H
