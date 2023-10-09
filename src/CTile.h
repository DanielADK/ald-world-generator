//
// Created by daniel on 1.10.23.
//

#ifndef SEMESTRAL_CTILE_H
#define SEMESTRAL_CTILE_H

#include <string>
#include <unordered_set>

enum class ETile {
    GROUND = ' ',
    TREE = 'T',
    GRASS = 'G',
    CITY = 'C',
    CAT = 'K',
    PATH_CROSS = '+',
    PATH_UPDOWN = '|',
    PATH_RIGHTLEFT = '-',
    PATH_ENDLEFT = '<',
    PATH_ENDUP = '^',
    PATH_ENDRIGHT = '>',
    PATH_ENDDOWN = 'V',
    PATH_LEFTDOWN = '\\',
    PATH_RIGHTDOWN = '/',
    PATH_LEFTUP = '/',
    PATH_RIGHTUP = '\\',
    ERROR = 'E',
    UNDEFINED = 'U'
};

class CTile {
private:
    ETile m_Type;
    std::string m_ImagePath;
    std::unordered_set<ETile> possibleTilesTop;
    std::unordered_set<ETile> possibleTilesRight;
    std::unordered_set<ETile> possibleTilesBottom;
    std::unordered_set<ETile> possibleTilesLeft;

public:
    CTile() = default;
    explicit CTile(const ETile& type);
    CTile(const ETile& type, std::string imagePath);
    CTile(const ETile& type, std::string imagePath, const std::unordered_set<ETile>& possibleTilesTop,
          const std::unordered_set<ETile>& possibleTilesRight, const std::unordered_set<ETile>& possibleTilesBottom,
          const std::unordered_set<ETile>& possibleTilesLeft);

    bool isPossibleTop(ETile tile) const;
    bool isPossibleRight(ETile tile) const;
    bool isPossibleBottom(ETile tile) const;
    bool isPossibleLeft(ETile tile) const;
};


#endif //SEMESTRAL_CTILE_H
