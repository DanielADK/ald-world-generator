#include "CTile.h"
#include <string>
#include <utility>


CTile::CTile(const ETile& type): m_Type(type) {}

CTile::CTile(const ETile& type, std::string imagePath): m_Type(type), m_ImagePath(std::move(imagePath)) {

}

CTile::CTile(const ETile &type, std::string  imagePath, std::unordered_set<ETile> &possibleTilesTop,
             std::unordered_set<ETile> &possibleTilesRight, std::unordered_set<ETile> &possibleTilesBottom,
             std::unordered_set<ETile> &possibleTilesLeft): m_Type(type), m_ImagePath(std::move(imagePath)),
                                                    possibleTilesTop(possibleTilesTop),
                                                    possibleTilesRight(possibleTilesRight),
                                                    possibleTilesBottom(possibleTilesBottom),
                                                    possibleTilesLeft(possibleTilesLeft) {}

bool CTile::isPossibleTop(ETile tile) const {
    return possibleTilesTop.contains(tile);
}

bool CTile::isPossibleRight(ETile tile) const {
    return possibleTilesRight.contains(tile);
}

bool CTile::isPossibleBottom(ETile tile) const {
    return possibleTilesBottom.contains(tile);
}

bool CTile::isPossibleLeft(ETile tile) const {
    return possibleTilesLeft.contains(tile);
}