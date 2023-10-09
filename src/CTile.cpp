#include "CTile.h"
#include <string>
#include <utility>


CTile::CTile(const ETile& type): m_Type(type) {}

CTile::CTile(const ETile& type, std::string imagePath): m_Type(type), m_ImagePath(std::move(imagePath)) {

}

CTile::CTile(const ETile &type, std::string  imagePath, const std::unordered_set<ETile> &possibleTilesTop,
             const std::unordered_set<ETile> &possibleTilesRight, const std::unordered_set<ETile> &possibleTilesBottom,
             const std::unordered_set<ETile> &possibleTilesLeft): m_Type(type), m_ImagePath(std::move(imagePath)),
                                                    possibleTilesTop(possibleTilesTop),
                                                    possibleTilesRight(possibleTilesRight),
                                                    possibleTilesBottom(possibleTilesBottom),
                                                    possibleTilesLeft(possibleTilesLeft) {}

bool CTile::isPossibleTop(ETile tile) const {
    return possibleTilesTop.contains(tile) || tile == ETile::UNDEFINED;
}

bool CTile::isPossibleRight(ETile tile) const {
    return possibleTilesRight.contains(tile) || tile == ETile::UNDEFINED;
}

bool CTile::isPossibleBottom(ETile tile) const {
    return possibleTilesBottom.contains(tile) || tile == ETile::UNDEFINED;
}

bool CTile::isPossibleLeft(ETile tile) const {
    return possibleTilesLeft.contains(tile) || tile == ETile::UNDEFINED;
}