//
// Created by Cédric Leclercq on 05/03/2021.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include "Face.h"
#include "../3Dobjects/vector3d.h"
#include "../Utilities/Color.h"
#include "../2Dobjects/Point2D.h"
#include <list>

enum Class {Cube,Tetrahedron,Octahedron,Dodecahedron,Cone,Cylinder,Sphere,Torus, Icosahedron};

class Figure {
public:
    std::vector<pair<Vector3D*,Vector3D*>> lines;
    std::vector<Vector3D*> points;
    std::vector<Face*> faces;
    Color color;
    Class figureClass;


    // Drawing
    void drawCube();
    void drawTetrahedron();
    void drawOctahedron();
    void drawIcosahedron();
    void drawDodecahedron();
    void drawCone(int n, double h);
    void drawCylinder(int n, double h);
    void drawSphere(double radius,  int n);
    void drawTorus(double r, double R, int n, int m);


    // Scaling and translating and eye
    void scaleTranslateEye(const Vector3D& centerVector, const Vector3D& eye, double scale, double rotateX, double rotateY, double rotateZ);

    // Matrices
    Point2D doProjection(const Vector3D * point, const double d);
    Matrix eyePointTrans(const Vector3D &eyepoint);
    void toPolar(const Vector3D &point, double &theta, double &phi, double &r);
    void applyTransformation(Figure & figure, const Matrix & matrix);
    Matrix translate(const Vector3D & vector);
    Matrix rotateZ ( double angle );
    Matrix rotateY ( double angle );
    Matrix rotateX ( double angle );
    Matrix scalefigure( double scale );

    // Utils
    void triangulate(const Face * face);
    void triangulateAll();
    vector<Figure*> generateFractal( int nr_iterations, double scale);
    void identifyAndDraw(enum Class figure);


    vector<Figure *> fractals(const vector<Figure*>& allFigures, const double scale);

    vector<Figure *> fractals(const vector<Figure *> &allFigures, const double scale, int nr_of_iterations);

    vector<Figure *> generateFract(const double scale);

    vector<Figure *> fractalGen(const vector<Figure *> &allFractals, int nr_iterations, const double scale);
};

typedef std::list<Figure> Figures3D;




#endif //ENGINE_FIGURE_H
