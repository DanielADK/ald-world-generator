#include "CTile.h"
#include <string>
#include <utility>


CTile::CTile(const ETile& type): m_Type(type) {}

CTile::CTile(const ETile& type, std::string imagePath): m_Type(type), m_ImagePath(std::move(imagePath)) {

}

CTile::CTile(const ETile &type, std::string  imagePath, std::vector<ETile> &possibleTilesTop,
             std::vector<ETile> &possibleTilesRight, std::vector<ETile> &possibleTilesBottom,
             std::vector<ETile> &possibleTilesLeft): m_Type(type), m_ImagePath(std::move(imagePath)),
                                                    possibleTilesTop(possibleTilesTop),
                                                    possibleTilesRight(possibleTilesRight),
                                                    possibleTilesBottom(possibleTilesBottom),
                                                    possibleTilesLeft(possibleTilesLeft) {

}

