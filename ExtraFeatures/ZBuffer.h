//
// Created by Cédric Leclercq on 28/03/2021.
//

#ifndef README_MD_ZBUFFER_H
#define README_MD_ZBUFFER_H
#include <limits>
#include <vector>


class ZBuffer: public std::vector<std::vector<double>> {
public:
    /**
     * \brief Constructs the ZBuffer. Initialises all the values on +inf
     * \param width     integer for the width of [x][y]
     * \param height    integer for the height of [x][y]
     */
    ZBuffer(const int width, const int height) {
        for (int i = 0; i < width; i++) {
            vector<double> newVector;
            newVector.reserve(height);
            for (int j = 0; j < height; j++) {
                newVector.push_back(std::numeric_limits<double>::infinity());
            }
            this->push_back(newVector);
        }
    }
};


#endif //README_MD_ZBUFFER_H
