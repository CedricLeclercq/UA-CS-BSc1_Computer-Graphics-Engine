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
    std::vector<pair<Vector3D*,Vector3D*>> lines;
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    Color color;

    void drawCube();
    void drawTetrahedron();
    void drawOctahedron();
    void drawIcosahedron();
    void drawDodecahedron();
    void drawCone();
    void drawCylinder();
    void drawSphere();
    void drawTores();

    void scaleTranslateEye();

};

typedef std::list<Figure> Figures3D;




#endif //ENGINE_FIGURE_H
