//
// Created by daniel on 9.10.23.
//

#include "CImageConnector.h"
void CImageConnector::processMap(const CMap& map, const std::unordered_map<ETile, CTile>& tileImages) {
    int rows = map.getRows();
    int cols = map.getCols();

    cv::Mat firstTile = cv::imread(tileImages.begin()->second.getImagePath());
    int tileWidth = firstTile.cols;
    int tileHeight = firstTile.rows;

    cv::Mat result(rows * tileHeight, cols * tileWidth, firstTile.type());

    ETile tileType;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tileType = map.getTile(i, j);

            std::string image_path = tileImages.at(tileType).getImagePath();
            cv::Mat tileImage = cv::imread(image_path);
            if (tileImage.empty())
                throw std::invalid_argument("Failed to load image: " + image_path);

            if (tileImage.rows != tileHeight || tileImage.cols != tileWidth)
                throw std::invalid_argument("Invalid image size: " + tileImages.at(tileType).getImagePath());

            // Copy the tile image to the result image
            tileImage.copyTo(result(cv::Rect(j * tileWidth, i * tileHeight, tileWidth, tileHeight)));
        }
    }

    if (result.empty())
        throw std::invalid_argument("Failed to create result image.");

    m_Result = result;
}

void CImageConnector::exportResult(const std::string &path) {
    cv::imwrite(path, m_Result);
}
