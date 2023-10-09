//
// Created by daniel on 9.10.23.
//

#ifndef SEMESTRAL_CIMAGECONNECTOR_H
#define SEMESTRAL_CIMAGECONNECTOR_H

#include "opencv2/opencv.hpp"
#include "CTile.h"
#include "CMap.h"

class CImageConnector {
private:
    cv::Mat m_Result;

public:
    void processMap(const CMap& map, const std::unordered_map<ETile, CTile>& tileImages);
    void exportResult(const std::string& path);


};


#endif //SEMESTRAL_CIMAGECONNECTOR_H
