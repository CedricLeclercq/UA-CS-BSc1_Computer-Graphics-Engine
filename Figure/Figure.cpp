//
// Created by Cédric Leclercq on 05/03/2021.
//

#include "Figure.h"
#include "../Utilities/Utils.h"
#include "ExtraAndUtils/FigureDrawer.h"
#include "../ExtraFeatures/Lsystems//l_parser.h"
#include "../Figure/ExtraAndUtils/FigureUtils.h"

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

}
// enum Class {Cube,Tetrahedron,Octahedron,Dodecahedron,Cone,Cylinder,Sphere,Torus, Icosahedron};
__attribute__((unused)) void Figure::identifyAndDraw(enum Class figure) {
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
    this->specularReflection = figure->specularReflection;
    this->ambientReflection = figure->ambientReflection;
    this->diffuseReflection = figure->diffuseReflection;
    this->reflectionCoefficient = figure->reflectionCoefficient;

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

__attribute__((unused)) void Figure::triangulate(const Face *face) {
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
        while (j < (int)face->point_indexes.size()) {
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

void Figure::clipping(const vector<double>& viewDir, double dNear, double dFar, double hFov, double aspectRatio) {

}

void Figure::clipSide(double T) {

    vector<Face*> temp; // Result vector, all faces that are clipped or are untouched will be stored here
    // Looping over all the triangles (this function assumes triangulation has already been done)
    for (auto &face: this->faces) {
        // 1st case - this face falls in the T value - it can keep on existing
        if (face->point_indexes[0]->z >= T and face->point_indexes[1]->z >= T and face->point_indexes[2]->z >= T) {
            temp.push_back(face); // This face can stay, push back to results vector
        }
        // 2th case - point A and B fall out, point C doesn't - we become a new triangle
        else if ((face->point_indexes[0]->z < T and face->point_indexes[1]->z < T and face->point_indexes[2]->z >= T)
             or (face->point_indexes[0]->z < T and face->point_indexes[1]->z >= T and face->point_indexes[2]->z < T)
             or (face->point_indexes[0]->z >= T and face->point_indexes[1]->z < T and face->point_indexes[2]->z < T)) {

            // TODO case 1.1/1.2 of clipping
        }
        // 3th case - point A and B don't fall out, point C does - create a four-pointed figure and triangulate it
        else if ((face->point_indexes[0]->z < T and face->point_indexes[1]->z >= T and face->point_indexes[2]->z >= T)
             or (face->point_indexes[0]->z >= T and face->point_indexes[1]->z >= T and face->point_indexes[2]->z < T)
             or (face->point_indexes[0]->z >= T and face->point_indexes[1]->z < T and face->point_indexes[2]->z >= T)) {

            // TODO case 1.2/1.2 of clipping
        }
        // 4th case - the face falls out of the view frustum, just leave it out
    }

    this->faces = temp; // Setting the new faces with the obsolete ones left out
}
















