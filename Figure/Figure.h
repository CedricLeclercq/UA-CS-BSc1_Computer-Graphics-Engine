//
// Created by Cédric Leclercq on 05/03/2021.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include "Face.h"
#include "../Lines/vector3d.h"
#include "Color.h"
#include "../Lines/Point2D.h"
#include <list>

enum Class {Cube,Tetrahedron,Octahedron,Dodecahedron,Cone,Cylinder,Sphere,Torus, Icosahedron};

class Figure {
public:
    std::vector<pair<Vector3D*,Vector3D*>> lines; // All lines of a figure
    std::vector<Vector3D*> points; // All points of a figure
    std::vector<Face*> faces; // All faces of a figure
    Color color{}; // The color of a figure
    Class figureClass; // enum class the figure is

    Figure()= default;

    explicit Figure(Figure * figure);


    // All functions that draw a figure
    /**
     * Draws a figure: Cube
     */
    void drawCube();
    /**
     * Draws a figure: Tetrahedron
     */
    void drawTetrahedron();
    /**
     * Draws a figure: Octahedron
     */
    void drawOctahedron();
    /**
     * Draws a figure: Icosahedron
     */
    void drawIcosahedron();
    /**
     * Draws a figure: Dodecahedron
     */
    void drawDodecahedron();
    /**
     * Draws a figure: Cone
     * @param n     Points on the lower face
     * @param h     Height of the cone
     */
    void drawCone(int n, double h);
    /**
     * Draws a figure: Cylinder
     * @param n     Points on the lower and upper face
     * @param h     Height of the cylinder
     */
    void drawCylinder(int n, double h);
    /**
     * Draws a figure: Sphere
     * @param n         Amount of iterations
     */
    void drawSphere(int n);
    // TODO add documentation for Torus
    /**
     * Draws a figure: Torus
     * @param r
     * @param R
     * @param n
     * @param m
     */
    void drawTorus(double r, double R, int n, int m);


    /*
    // Scaling and translating and eye
    void scaleTranslateEye(const Vector3D& centerVector, const Vector3D& eye, double scale, double rotateX, double rotateY, double rotateZ);

    // Matrices
    Point2D doProjection(const Vector3D * point, double d);
    Matrix eyePointTrans(const Vector3D &eyepoint);
    void toPolar(const Vector3D &point, double &theta, double &phi, double &r);
    void applyTransformation(Figure & figure, const Matrix & matrix);
    Matrix translate(const Vector3D & vector);
    Matrix rotateZ ( double angle );
    Matrix rotateY ( double angle );
    Matrix rotateX ( double angle );
    Matrix scalefigure( double scale );
     */

    // Copy constructor



    // Utils
    void triangulate(const Face * face);
    void triangulateAll();

    // Fractals
    vector<Figure*> fractals(int nr_iterations, double scale);
    void identifyAndDraw(enum Class figure);
    vector<Figure *> generateFractals(double scale);
    vector<Figure *> recursiveFractalsGeneration(const vector<Figure *> &allFractals, int nr_iterations, const double scale);

    // View Frustum


};



#endif //ENGINE_FIGURE_H
