//
// Created by Cédric Leclercq on 05/03/2021.
//

#include "Figure.h"
#include "../Utilities/Utils.h"
#include "FigureDrawer.h"

// Scaling


void Figure::triangulateAll() {

    vector<Face*> newFaces;

    for (auto face: this->faces) {

        // Variables for accessing the point_indexes
        int i = 1;
        int j = 2;

        // Can't triangulate a triangle
        if (face->point_indexes.size() <= 3) {
            return;
        }

        // Doing the triangulation proces
        while (j < (int)face->point_indexes.size()) {
            auto * face1 = new Face({face->point_indexes[0], face->point_indexes[i],face->point_indexes[j]});
            newFaces.push_back(face1);
            i++;
            j++;
        }
    }

    this->faces.clear();
    for (auto face: newFaces) {
        this->faces.push_back(face);
    }
}

vector<Figure*> Figure::recursiveFractalsGeneration(const vector<Figure*>& allFractals, int nr_iterations, const double scale) {
    if (nr_iterations == 0) {
        return allFractals;
    } else {
        nr_iterations -= 1;
        vector<Figure*> currentNew;
        for (auto &figure: allFractals) {
            vector<Figure*> toAdd = figure->generateFractals(scale);
            Utils::addToVector(currentNew, toAdd); // = figure->generateFract(scale);
        } return this->recursiveFractalsGeneration(currentNew, nr_iterations, scale); // TODO scale moet aangepast worden per iteratie maar ik weet niet hoe, alvast niet * 2
    }
}

vector<Figure*> Figure::generateFractals(const double scale) {

    vector<Figure*> fractals; // Vector with all the fractals

    for (auto point: this->points) {
        auto * newFractal = new Figure(this);
        //newFractal->identifyAndDraw(this->figureClass);
        //newFractal->drawCube();
        FigureUtils::applyTransformation(*newFractal,FigureUtils::scalefigure(1/scale));
        FigureUtils::applyTransformation(*newFractal,FigureUtils::translate(*point));
        fractals.push_back(newFractal);
    }
    return fractals;
}

vector<Figure*> Figure::fractals(int nr_iterations, const double scale) {


    return this->recursiveFractalsGeneration({this}, nr_iterations, scale);

    /*
    vector<Figure*> fractals; // Vector with all the fractals


    for (int i = 0; i < nr_iterations; i++) {
        if (i == 0) {
            for (auto &point: this->points) {
                auto * newFractal = new Figure;
                newFractal->identifyAndDraw(this->figureClass);
                //newFractal->drawCube();
                newFractal->applyTransformation(*newFractal,newFractal->scalefigure(1/scale));
                newFractal->applyTransformation(*newFractal,newFractal->translate(*point));
                fractals.push_back(newFractal);
            }
        } else {
            vector<Figure*> newFractals;
            for (auto fractal: fractals) {
                for (const auto &point: fractal->points) {
                    auto * newFractal = new Figure;
                    //newFractal->drawCube();
                    newFractal->identifyAndDraw(fractal->figureClass);
                    newFractal->applyTransformation(*newFractal,newFractal->scalefigure(1/scale));
                    newFractal->applyTransformation(*newFractal,newFractal->translate(*point));
                    newFractals.push_back(newFractal);
                }
            }
            fractals.clear();
            for (auto &fractal: newFractals) {
                fractals.push_back(fractal);
            } newFractals.clear();

            //fractals = newFractals;
        }
    }


     return fractals;
     */
}
// enum Class {Cube,Tetrahedron,Octahedron,Dodecahedron,Cone,Cylinder,Sphere,Torus, Icosahedron};
void Figure::identifyAndDraw(enum Class figure) {
    if (figure == Cube) {
        this->drawCube();
    } else if (figure == Tetrahedron) {
        this->drawTetrahedron();
    } else if (figure == Octahedron) {
        this->drawOctahedron();
    } else if (figure == Dodecahedron) {
        this->drawDodecahedron();
    } else if (figure == Icosahedron) {
        this->drawIcosahedron();
    }
}

Figure::Figure(Figure *figure) {
    this->color = figure->color; // Setting the new color
    this->figureClass = figure->figureClass; // Setting the figure class

    vector<Face*> nFaces = figure->faces;
    vector<Vector3D*> nPoints = figure->points;
    vector<pair<Vector3D*,Vector3D*>> nLines = figure->lines; // All lines of a figure


    // Looping over every point
    for (auto point: figure->points) {
        auto * newPoint = new Vector3D; // Creating a new point
        newPoint->x = point->x;
        newPoint->y = point->y;
        newPoint->z = point->z;

        // Searching for this point in faces and replacing it with its new pointer
        for (auto &face: nFaces) {
            if (Utils::contains(face->point_indexes,point)) {
                Utils::replace(face->point_indexes,point,newPoint);
            }
        }

        // Searching for this point in lines and replacing it with its new pointer
        for (auto &line: nLines) {
            if (line.first == point) {
                line.first = newPoint;
            }
            if (line.second == point) {
                line.second = newPoint;
            }
        }

        this->faces = nFaces;
        this->lines = nLines;
        this->points.push_back(newPoint);
    }
}

void Figure::drawCube() {
    FigureDrawer::drawCube(this);
}

void Figure::drawTetrahedron() {
    FigureDrawer::drawTetrahedron(this);
}

void Figure::drawOctahedron() {
    FigureDrawer::drawOctahedron(this);
}

void Figure::drawIcosahedron() {
    FigureDrawer::drawIcosahedron(this);
}

void Figure::drawDodecahedron() {
    FigureDrawer::drawDodecahedron(this);
}

void Figure::drawCone(int n, double h) {
    FigureDrawer::drawCone(this,n,h);
}

void Figure::drawCylinder(int n, double h) {
    FigureDrawer::drawCylinder(this,n,h);
}

void Figure::drawSphere(int n) {
    FigureDrawer::drawSphere(this,n);
}

void Figure::drawTorus(double r, double R, int n, int m) {
    FigureDrawer::drawTorus(this,r,R,n,m);
}

void Figure::triangulate(const Face *face) {
    {
        // Variables for accessing the point_indexes
        int i = 1;
        int j = 2;

        // Make the new face vector except with the face that was given to this function
        vector<Face*> newFaces = {};
        for (auto oldFace: this->faces) {
            if (oldFace != face) {
                newFaces.push_back(oldFace);
            }
        }

        // Can't triangulate a triangle
        if (face->point_indexes.size() <= 3) {
            return;
        }

        // Doing the triangulation proces
        while (j < face->point_indexes.size()) {
            auto * face1 = new Face({face->point_indexes[0], face->point_indexes[i],face->point_indexes[j]});
            newFaces.push_back(face1);
            i++;
            j++;
        }

        // Fixing this->faces
        this->faces.clear();
        for (auto newFace: newFaces) {
            this->faces.push_back(newFace);
        }
    }
}













