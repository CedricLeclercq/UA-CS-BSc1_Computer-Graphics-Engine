//
// Created by Cédric Leclercq on 14/03/2021.
//

#ifndef ENGINE_WIREFRAME_H
#define ENGINE_WIREFRAME_H
#include "Figure.h"


class wireframe {
public:
    double size;
    int nrFigures;
    vector<double> eye;
    vector<double> backgroundColor;

    vector<Figure*> figures;

    wireframe(int size, int nrFigures, vector<double> eye, vector<double> backgroundColor, vector<Figure*> figures) {
        wireframe::size = size;
        wireframe::nrFigures = nrFigures;
        wireframe::eye = eye;
        wireframe::backgroundColor = backgroundColor;
        wireframe::figures = figures;
    }
};


#endif //ENGINE_WIREFRAME_H
