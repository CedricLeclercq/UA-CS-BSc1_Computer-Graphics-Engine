//
// Created by Cédric Leclercq on 05/03/2021.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include "ExtraAndUtils/Face.h"
#include "ExtraAndUtils/Color.h"
#include "../Lines/Point2D.h"
#include <list>

enum Class {Cube,Tetrahedron,Octahedron,Dodecahedron,Cone,Cylinder,Sphere,Torus, Icosahedron};

class Figure {
public:
    std::vector<pair<Vector3D*,Vector3D*>> lines; // All lines of a figure
    std::vector<Vector3D*> points; // All points of a figure
    std::vector<Face*> faces; // All faces of a figure
    Color color{}; // The color of a figure
    Color ambientReflection{};
    Color diffuseReflection{};
    Color specularReflection{};
    Color reflectionCoefficient{};
    Class figureClass{}; // enum class the figure is

    // Constructors
    /**
     * \brief Default constructor
     */
    Figure()= default;

    /**
     * Copy constructor
     * @param figure    Figure to copy
     */
    explicit Figure(Figure * figure);


    // Drawing figures
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


    // zBuffering
    /**
     * \brief Will triangulate one face
     * @param face
     */
    __attribute__((unused)) void triangulate(const Face * face);
    /**
     * \brief Will triangulate all faces of this figure object
     */
    void triangulateAll();


    // fractals
    /**
     * \brief Main function for generating fractals
     * @param nr_iterations     Indicates the amount of iterations
     * @param scale             Indicates how much smaller the fractals get each iteration
     * @return
     */
    vector<Figure*> fractals(int nr_iterations, double scale);
    /**
     * \brief Identifies a figure's type and draws that type on the figure object
     * @param figure
     */
    __attribute__((unused)) void identifyAndDraw(enum Class figure);
    /**
     * \brief Function that will actually make fractals from a figure. This function is being used each time in the recursive
     * chain
     * @param scale
     * @return
     */
    vector<Figure *> generateFractals(double scale);
    /**
     * \brief Recursive function that will create fractals for each iteration
     * @param allFractals
     * @param nr_iterations
     * @param scale
     * @return
     */
    vector<Figure *> recursiveFractalsGeneration(const vector<Figure *> &allFractals, int nr_iterations, double scale);

    // View Frustum
    /**
     * \brief Main function for clipping, calculates most variables and calls the clipSide function
     * @param viewDir
     * @param dNear
     * @param dFar
     * @param hFov
     * @param aspectRatio
     */
     // TODO maybe move the clipping function to its own .h file and give the vector with all the figures with this function.
     // TODO then create a loop over all those figure after everything is calculated and then do the clipping
    void clipping(const vector<double>& viewDir, double dNear, double dFar, double hFov, double aspectRatio);
    /**
     * Will clip all
     * @param dNear
     */
    void clipSide(double T);


};



#endif //ENGINE_FIGURE_H
