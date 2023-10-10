#include "CTile.h"
#include <string>
#include <utility>


CTile::CTile(const ETile& type): m_Type(type) {}

CTile::CTile(const ETile& type, std::string imagePath): m_Type(type), m_ImagePath(std::move(imagePath)) {

}

CTile::CTile(const ETile &type,
             std::string symbol,
             std::string imagePath,
             std::unordered_set<ETile>& possibleTilesTop,
             std::unordered_set<ETile>& possibleTilesRight,
             std::unordered_set<ETile>& possibleTilesBottom,
             std::unordered_set<ETile>& possibleTilesLeft):
                m_Type(type),
                m_Symbol(std::move(symbol)),
                m_ImagePath(std::move(imagePath)),
                possibleTilesTop(std::move(possibleTilesTop)),
                possibleTilesRight(std::move(possibleTilesRight)),
                possibleTilesBottom(std::move(possibleTilesBottom)),
                possibleTilesLeft(std::move(possibleTilesLeft)) {}

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

std::string CTile::getImagePath() const {
    return m_ImagePath;
}
