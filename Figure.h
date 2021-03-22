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
    std::vector<Vector3D*> points;
    std::vector<Face*> faces;
    Color color;

    // Drawing
    void drawCube();
    void drawTetrahedron();
    void drawOctahedron();
    void drawIcosahedron();
    void drawDodecahedron();
    void drawCone(const int n, const double h);
    void drawCylinder(const int n, const double h);
    void drawSphere(const double radius, const int n);
    void drawTorus(const double r, const double R, const int n, const int m);


    // Scaling and translating and eye
    void scaleTranslateEye(Vector3D centerVector, Vector3D eye, double scale, double rotateX, double rotateY, double rotateZ);

    // Matrices
    Point2D doProjection(const Vector3D * point, const double d);
    Matrix eyePointTrans(const Vector3D &eyepoint);
    void toPolar(const Vector3D &point, double &theta, double &phi, double &r);
    void applyTransformation(Figure & figure, const Matrix & matrix);
    Matrix translate(const Vector3D & vector);
    Matrix rotateZ ( double angle );
    Matrix rotateY ( double angle );
    Matrix rotateX ( double angle );
    Matrix scalefigure( const double scale);


};

typedef std::list<Figure> Figures3D;




#endif //ENGINE_FIGURE_H
