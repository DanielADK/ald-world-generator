//
// Created by daniel on 1.10.23.
//

#ifndef SEMESTRAL_CTILE_H
#define SEMESTRAL_CTILE_H

#include <string>
#include <vector>

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
    ERROR = 'E'
};

class CTile {
private:
    ETile m_Type;
    std::string m_ImagePath;
    std::vector<ETile> possibleTilesTop;
    std::vector<ETile> possibleTilesRight;
    std::vector<ETile> possibleTilesBottom;
    std::vector<ETile> possibleTilesLeft;

public:
    CTile() = default;
    explicit CTile(const ETile& type);
    CTile(const ETile& type, std::string imagePath);
    CTile(const ETile& type, std::string  imagePath, std::vector<ETile>& possibleTilesTop,
          std::vector<ETile>& possibleTilesRight, std::vector<ETile>& possibleTilesBottom,
          std::vector<ETile>& possibleTilesLeft);
};


#endif //SEMESTRAL_CTILE_H
