//
// Created by Cédric Leclercq on 05/03/2021.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include "Face.h"
#include "vector3d.h"
#include "vector3d.cc"
#include "Color.h"
#include <list>


class Figure {
public:
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    Color color;

};

typedef std::list<Figure> Figures3D;




#endif //ENGINE_FIGURE_H
