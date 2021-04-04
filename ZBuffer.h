//
// Created by Cédric Leclercq on 28/03/2021.
//

#ifndef README_MD_ZBUFFER_H
#define README_MD_ZBUFFER_H
#include <limits>


class ZBuffer: public std::vector<std::vector<double>> {
public:
    /**
     * \brief Constructs the ZBuffer. Initialises all the values on +inf
     * \param width     integer for the width of [x][y]
     * \param height    integer for the height of [x][y]
     */
    ZBuffer(const int width, const int height);


};


#endif //README_MD_ZBUFFER_H
