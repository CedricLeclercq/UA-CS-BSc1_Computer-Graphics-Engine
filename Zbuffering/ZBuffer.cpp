//
// Created by Cédric Leclercq on 28/03/2021.
//

#include "ZBuffer.h"


ZBuffer::ZBuffer(const int width, const int height) {
    for (int i = 0; i < width; i++) {
        vector<double> newVector;
        for (int j = 0; j < height; j++) {
            newVector.push_back(std::numeric_limits<double>::infinity());
        }
        this->push_back(newVector);
    }
}
