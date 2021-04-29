//
// Created by Cédric Leclercq on 05/03/2021.
//

#include "Figure.h"
#include "../Utilities/Utils.h"

// Scaling
void Figure::scaleTranslateEye(const Vector3D& centerVector, const Vector3D& eye, double scale, double rotateX, double rotateY, double rotateZ) {
    // rotate, scale and translate

    //applyTransformation(figure,translate(centerVector));

    Matrix final = scalefigure(scale) *
                   this->rotateX(rotateX) *
                   this->rotateY(rotateY) *
                   this->rotateZ(rotateZ) *
                   translate(centerVector);


    applyTransformation(*this, final);
    applyTransformation(*this, eyePointTrans(eye));
}
Matrix Figure::scalefigure(const double scale) {
    /**
     * @pre figuur moet rond (0,0,0) gecentreerd zijn!
     *
     */

    Matrix matrix;
    matrix(1,1) = scale;
    matrix(2,2) = scale;
    matrix(3,3) = scale;
    matrix(4,4) = 1;

    return matrix;
}

// Draw figures
void Figure::drawCube() {
    this->figureClass = Cube;


    // Creating all the points
    auto * point1 = new Vector3D;
    auto * point2 = new Vector3D;
    auto * point3 = new Vector3D;
    auto * point4 = new Vector3D;
    auto * point5 = new Vector3D;
    auto * point6 = new Vector3D;
    auto * point7 = new Vector3D;
    auto * point8 = new Vector3D;

    point1->x = 1; point1->y = -1; point1->z = -1;
    point2->x = -1; point2->y = 1; point2->z = -1;
    point3->x = 1; point3->y = 1; point3->z = 1;
    point4->x = -1; point4->y = -1; point4->z = 1;
    point5->x = 1; point5->y = 1; point5->z = -1;
    point6->x = -1; point6->y = -1; point6->z = -1;
    point7->x = 1; point7->y = -1; point7->z = 1;
    point8->x = -1; point8->y = 1; point8->z = 1;

    this->points.push_back(point1);
    this->points.push_back(point2);
    this->points.push_back(point3);
    this->points.push_back(point4);
    this->points.push_back(point5);
    this->points.push_back(point6);
    this->points.push_back(point7);
    this->points.push_back(point8);



    // Creating all the faces
    auto * face1 = new Face({point1,point5,point3,point7});
    auto * face2 = new Face({point5,point2,point8,point3});
    auto * face3 = new Face({point2,point6,point4,point8});
    auto * face4 = new Face({point6,point1,point7,point4});
    auto * face5 = new Face({point7,point3,point8,point4});
    auto * face6 = new Face({point1,point6,point2,point5});


    // And pushing back to the faces vector
    this->faces.push_back(face1);
    this->faces.push_back(face2);
    this->faces.push_back(face3);
    this->faces.push_back(face4);
    this->faces.push_back(face5);
    this->faces.push_back(face6);


    for (auto face: this->faces) {
        this->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
        this->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
        this->lines.emplace_back(face->point_indexes[2],face->point_indexes[3]);
        this->lines.emplace_back(face->point_indexes[3],face->point_indexes[0]);
    }
}
void Figure::drawTetrahedron() {
    this->figureClass = Tetrahedron;

    // Creating the points
    auto * point1 = new Vector3D;
    auto * point2 = new Vector3D;
    auto * point3 = new Vector3D;
    auto * point4 = new Vector3D;

    point1->x = 1; point1->y = -1; point1->z = -1;
    point2->x = -1; point2->y = 1; point2->z = -1;
    point3->x = 1; point3->y = 1; point3->z = 1;
    point4->x = -1; point4->y = -1; point4->z = 1;

    this->points.push_back(point1);
    this->points.push_back(point2);
    this->points.push_back(point3);
    this->points.push_back(point4);

    // Creating the faces
    auto * face1 = new Face({point1,point2,point3});
    auto * face2 = new Face({point2,point4,point3});
    auto * face3 = new Face({point1,point4,point2});
    auto * face4 = new Face({point1,point3,point4});

    this->faces.push_back(face1);
    this->faces.push_back(face2);
    this->faces.push_back(face3);
    this->faces.push_back(face4);

    for (auto face: this->faces) {
        this->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
        this->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
        this->lines.emplace_back(face->point_indexes[2],face->point_indexes[0]);
    }


}
void Figure::drawOctahedron() {
    this->figureClass = Octahedron;

    // Creating all the points
    auto * point1 = new Vector3D;
    auto * point2 = new Vector3D;
    auto * point3 = new Vector3D;
    auto * point4 = new Vector3D;
    auto * point5 = new Vector3D;
    auto * point6 = new Vector3D;

    point1->x = 1; point1->y = 0; point1->z = 0;
    point2->x = 0; point2->y = 1; point2->z = 0;
    point3->x = -1; point3->y = 0; point3->z = 0;
    point4->x = 0; point4->y = -1; point4->z = 0;
    point5->x = 0; point5->y = 0; point5->z = 0;
    point6->x = 0; point6->y = 0; point6->z = 1;

    this->points.push_back(point1);
    this->points.push_back(point2);
    this->points.push_back(point3);
    this->points.push_back(point4);
    this->points.push_back(point5);
    this->points.push_back(point6);

    // Creating all the faces
    auto * face1 = new Face({point1,point2,point6});
    auto * face2 = new Face({point2,point3,point6});
    auto * face3 = new Face({point3,point4,point6});
    auto * face4 = new Face({point4,point1,point6});
    auto * face5 = new Face({point2,point1,point5});
    auto * face6 = new Face({point3,point2,point5});
    auto * face7 = new Face({point4,point3,point5});
    auto * face8 = new Face({point1,point4,point5});

    this->faces.push_back(face1);
    this->faces.push_back(face2);
    this->faces.push_back(face3);
    this->faces.push_back(face4);
    this->faces.push_back(face5);
    this->faces.push_back(face6);
    this->faces.push_back(face7);
    this->faces.push_back(face8);

    for (auto face: this->faces) {
        this->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
        this->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
        this->lines.emplace_back(face->point_indexes[2],face->point_indexes[3]);
        this->lines.emplace_back(face->point_indexes[3],face->point_indexes[0]);
    }

}
void Figure::drawIcosahedron() {
    this->figureClass = Icosahedron;

    // Creating first point
    auto * point1 = new Vector3D;
    auto * point2 = new Vector3D;
    auto * point3 = new Vector3D;
    auto * point4 = new Vector3D;
    auto * point5 = new Vector3D;
    auto * point6 = new Vector3D;
    auto * point7 = new Vector3D;
    auto * point8 = new Vector3D;
    auto * point9 = new Vector3D;
    auto * point10 = new Vector3D;
    auto * point11 = new Vector3D;
    auto * point12 = new Vector3D;

    point1->x = 0; point1->y = 0; point1->z = (sqrt(5)/2);
    point2->x = cos(0); point2->y = sin(0); point2->z = 0.5;
    point3->x = cos(2 * M_PI / 5); point3->y = sin(2 * M_PI / 5); point3->z = 0.5;
    point4->x = cos(4 * M_PI / 5); point4->y = sin(4 * M_PI / 5); point4->z = 0.5;
    point5->x = cos(6 * M_PI / 5); point5->y = sin(6 * M_PI / 5); point5->z = 0.5;
    point6->x = cos(8 * M_PI / 5); point6->y = sin(8 * M_PI / 5); point6->z = 0.5;
    point7->x = cos(M_PI / 5); point7->y = sin(M_PI / 5); point7->z = -0.5;
    point8->x = cos(M_PI / 5 + 2 * M_PI / 5); point8->y = sin(M_PI / 5 + 2 * M_PI / 5); point8->z = -0.5;
    point9->x = cos(M_PI / 5 + 4 * M_PI / 5); point9->y = sin(M_PI / 5 + 4 * M_PI / 5); point9->z = -0.5;
    point10->x = cos(M_PI / 5 + 6 * M_PI / 5); point10->y = sin(M_PI / 5 + 6 * M_PI / 5); point10->z = -0.5;
    point11->x = cos(M_PI / 5 + 8 * M_PI / 5); point11->y = sin(M_PI / 5 + 8 * M_PI / 5); point11->z = -0.5;
    point12->x = 0; point12->y = 0; point12->z = -sqrt(5)/2;

    this->points.push_back(point1);
    this->points.push_back(point2);
    this->points.push_back(point3);
    this->points.push_back(point4);
    this->points.push_back(point5);
    this->points.push_back(point6);
    this->points.push_back(point7);
    this->points.push_back(point8);
    this->points.push_back(point9);
    this->points.push_back(point10);
    this->points.push_back(point11);
    this->points.push_back(point12);

    auto * face1 = new Face({point1,point2,point3});
    auto * face2 = new Face({point1,point3,point4});
    auto * face3 = new Face({point1,point4,point5});
    auto * face4 = new Face({point1,point5,point6});
    auto * face5 = new Face({point1,point6,point2});
    auto * face6 = new Face({point2,point7,point3});
    auto * face7 = new Face({point3,point7,point8});
    auto * face8 = new Face({point3,point8,point4});
    auto * face9 = new Face({point4,point8,point9});
    auto * face10 = new Face({point4,point9,point5});
    auto * face11 = new Face({point5,point9,point10});
    auto * face12 = new Face({point5,point10,point6});
    auto * face13 = new Face({point6,point10,point11});
    auto * face14 = new Face({point6,point11,point2});
    auto * face15 = new Face({point2,point11,point7});
    auto * face16 = new Face({point12,point8,point7});
    auto * face17 = new Face({point12,point9,point8});
    auto * face18 = new Face({point12,point10,point9});
    auto * face19 = new Face({point12,point11,point10});
    auto * face20 = new Face({point12,point7,point11});

    this->faces.push_back(face1);
    this->faces.push_back(face2);
    this->faces.push_back(face3);
    this->faces.push_back(face4);
    this->faces.push_back(face5);
    this->faces.push_back(face6);
    this->faces.push_back(face7);
    this->faces.push_back(face8);
    this->faces.push_back(face9);
    this->faces.push_back(face10);
    this->faces.push_back(face11);
    this->faces.push_back(face12);
    this->faces.push_back(face13);
    this->faces.push_back(face14);
    this->faces.push_back(face15);
    this->faces.push_back(face16);
    this->faces.push_back(face17);
    this->faces.push_back(face18);
    this->faces.push_back(face19);
    this->faces.push_back(face20);

    for (auto face: this->faces) {
        this->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
        this->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
        this->lines.emplace_back(face->point_indexes[2],face->point_indexes[0]);
    }
}
void Figure::drawDodecahedron() {
    this->figureClass = Dodecahedron;

    // Creating iso points
    auto * pointI1 = new Vector3D;
    auto * pointI2 = new Vector3D;
    auto * pointI3 = new Vector3D;
    auto * pointI4 = new Vector3D;
    auto * pointI5 = new Vector3D;
    auto * pointI6 = new Vector3D;
    auto * pointI7 = new Vector3D;
    auto * pointI8 = new Vector3D;
    auto * pointI9 = new Vector3D;
    auto * pointI10 = new Vector3D;
    auto * pointI11 = new Vector3D;
    auto * pointI12 = new Vector3D;

    pointI1->x = 0; pointI1->y = 0; pointI1->z = (sqrt(5)/2);
    pointI2->x = cos(0); pointI2->y = sin(0); pointI2->z = 0.5;
    pointI3->x = cos(2 * M_PI / 5); pointI3->y = sin(2 * M_PI / 5); pointI3->z = 0.5;
    pointI4->x = cos(4 * M_PI / 5); pointI4->y = sin(4 * M_PI / 5); pointI4->z = 0.5;
    pointI5->x = cos(6 * M_PI / 5); pointI5->y = sin(6 * M_PI / 5); pointI5->z = 0.5;
    pointI6->x = cos(8 * M_PI / 5); pointI6->y = sin(8 * M_PI / 5); pointI6->z = 0.5;
    pointI7->x = cos(M_PI / 5); pointI7->y = sin(M_PI / 5); pointI7->z = -0.5;
    pointI8->x = cos(M_PI / 5 + 2 * M_PI / 5); pointI8->y = sin(M_PI / 5 + 2 * M_PI / 5); pointI8->z = -0.5;
    pointI9->x = cos(M_PI / 5 + 4 * M_PI / 5); pointI9->y = sin(M_PI / 5 + 4 * M_PI / 5); pointI9->z = -0.5;
    pointI10->x = cos(M_PI / 5 + 6 * M_PI / 5); pointI10->y = sin(M_PI / 5 + 6 * M_PI / 5); pointI10->z = -0.5;
    pointI11->x = cos(M_PI / 5 + 8 * M_PI / 5); pointI11->y = sin(M_PI / 5 + 8 * M_PI / 5); pointI11->z = -0.5;
    pointI12->x = 0; pointI12->y = 0; pointI12->z = -sqrt(5)/2;

    // Declaring the points
    auto * point1 = new Vector3D;
    auto * point2 = new Vector3D;
    auto * point3 = new Vector3D;
    auto * point4 = new Vector3D;
    auto * point5 = new Vector3D;
    auto * point6 = new Vector3D;
    auto * point7 = new Vector3D;
    auto * point8 = new Vector3D;
    auto * point9 = new Vector3D;
    auto * point10 = new Vector3D;
    auto * point11 = new Vector3D;
    auto * point12 = new Vector3D;
    auto * point13 = new Vector3D;
    auto * point14 = new Vector3D;
    auto * point15 = new Vector3D;
    auto * point16 = new Vector3D;
    auto * point17 = new Vector3D;
    auto * point18 = new Vector3D;
    auto * point19 = new Vector3D;
    auto * point20 = new Vector3D;




    point1->x = (pointI1->x + pointI2->x + pointI3->x) / 3; point1->y = (pointI1->y + pointI2->y + pointI3->y) / 3; point1->z = (pointI1->z + pointI2->z + pointI3->z) / 3;
    point2->x = (pointI1->x + pointI3->x + pointI4->x) / 3; point2->y = (pointI1->y + pointI3->y + pointI4->y) / 3; point2->z = (pointI1->z + pointI3->z + pointI4->z) / 3;
    point3->x = (pointI1->x + pointI4->x + pointI5->x) / 3; point3->y = (pointI1->y + pointI4->y + pointI5->y) / 3; point3->z = (pointI1->z + pointI4->z + pointI5->z) / 3;
    point4->x = (pointI1->x + pointI5->x + pointI6->x) / 3; point4->y = (pointI1->y + pointI5->y + pointI6->y) / 3; point4->z = (pointI1->z + pointI5->z + pointI6->z) / 3;
    point5->x = (pointI1->x + pointI6->x + pointI2->x) / 3; point5->y = (pointI1->y + pointI6->y + pointI2->y) / 3; point5->z = (pointI1->z + pointI6->z + pointI2->z) / 3;
    point6->x = (pointI2->x + pointI7->x + pointI3->x) / 3; point6->y = (pointI2->y + pointI7->y + pointI3->y) / 3; point6->z = (pointI2->z + pointI7->z + pointI3->z) / 3;
    point7->x = (pointI3->x + pointI7->x + pointI8->x) / 3; point7->y = (pointI3->y + pointI7->y + pointI8->y) / 3; point7->z = (pointI3->z + pointI7->z + pointI8->z) / 3;
    point8->x = (pointI3->x + pointI8->x + pointI4->x) / 3; point8->y = (pointI3->y + pointI8->y + pointI4->y) / 3; point8->z = (pointI3->z + pointI8->z + pointI4->z) / 3;
    point9->x = (pointI4->x + pointI8->x + pointI9->x) / 3; point9->y = (pointI4->y + pointI8->y + pointI9->y) / 3; point9->z = (pointI4->z + pointI8->z + pointI9->z) / 3;
    point10->x = (pointI4->x + pointI9->x + pointI5->x) / 3; point10->y = (pointI4->y + pointI9->y + pointI5->y) / 3; point10->z = (pointI4->z + pointI9->z + pointI5->z) / 3;
    point11->x = (pointI5->x + pointI9->x + pointI10->x) / 3; point11->y = (pointI5->y + pointI9->y + pointI10->y) / 3; point11->z = (pointI5->z + pointI9->z + pointI10->z) / 3;
    point12->x = (pointI5->x + pointI6->x + pointI10->x) / 3; point12->y = (pointI5->y + pointI6->y + pointI10->y) / 3; point12->z = (pointI5->z + pointI6->z + pointI10->z) / 3;
    point13->x = (pointI6->x + pointI10->x + pointI11->x) / 3; point13->y = (pointI6->y + pointI10->y + pointI11->y) / 3; point13->z = (pointI6->z + pointI10->z + pointI11->z) / 3;
    point14->x = (pointI6->x + pointI11->x + pointI2->x) / 3; point14->y = (pointI6->y + pointI11->y + pointI2->y) / 3; point14->z = (pointI6->z + pointI11->z + pointI2->z) / 3;
    point15->x = (pointI2->x + pointI11->x + pointI7->x) / 3; point15->y = (pointI2->y + pointI11->y + pointI7->y) / 3; point15->z = (pointI2->z + pointI11->z + pointI7->z) / 3;
    point16->x = (pointI12->x + pointI7->x + pointI8->x) / 3; point16->y = (pointI12->y + pointI7->y + pointI8->y) / 3; point16->z = (pointI12->z + pointI7->z + pointI8->z) / 3;
    point17->x = (pointI12->x + pointI9->x + pointI8->x) / 3; point17->y = (pointI12->y + pointI9->y + pointI8->y) / 3; point17->z = (pointI12->z + pointI9->z + pointI8->z) / 3;
    point18->x = (pointI12->x + pointI10->x + pointI9->x) / 3; point18->y = (pointI12->y + pointI10->y + pointI9->y) / 3; point18->z = (pointI12->z + pointI10->z + pointI9->z) / 3;
    point19->x = (pointI12->x + pointI11->x + pointI10->x) / 3; point19->y = (pointI12->y + pointI11->y + pointI10->y) / 3; point19->z = (pointI12->z + pointI11->z + pointI10->z) / 3;
    point20->x = (pointI12->x + pointI7->x + pointI11->x) / 3; point20->y = (pointI12->y + pointI7->y + pointI11->y) / 3; point20->z = (pointI12->z + pointI7->z + pointI11->z) / 3;

    this->points.push_back(point1);
    this->points.push_back(point2);
    this->points.push_back(point3);
    this->points.push_back(point4);
    this->points.push_back(point5);
    this->points.push_back(point6);
    this->points.push_back(point7);
    this->points.push_back(point8);
    this->points.push_back(point9);
    this->points.push_back(point10);
    this->points.push_back(point11);
    this->points.push_back(point12);
    this->points.push_back(point13);
    this->points.push_back(point14);
    this->points.push_back(point15);
    this->points.push_back(point16);
    this->points.push_back(point17);
    this->points.push_back(point18);
    this->points.push_back(point19);
    this->points.push_back(point20);

    delete pointI1;
    delete pointI2;
    delete pointI3;
    delete pointI4;
    delete pointI5;
    delete pointI6;
    delete pointI7;
    delete pointI8;
    delete pointI9;
    delete pointI10;
    delete pointI11;
    delete pointI12;

    auto * face1 = new Face({point1,point2,point3,point4,point5});
    auto * face2 = new Face({point1,point6,point7,point8,point2});
    auto * face3 = new Face({point2,point8,point9,point10,point3});
    auto * face4 = new Face({point3,point10,point11,point12,point4});
    auto * face5 = new Face({point4,point12,point13,point14,point5});
    auto * face6 = new Face({point5,point14,point15,point6,point1});
    auto * face7 = new Face({point20,point19,point18,point17,point16});
    auto * face8 = new Face({point20,point15,point14,point13,point19});
    auto * face9 = new Face({point19,point13,point12,point11,point18});
    auto * face10 = new Face({point18,point11,point10,point9,point17});
    auto * face11 = new Face({point17,point9,point8,point7,point16});
    auto * face12 = new Face({point16,point7,point6,point15,point20});

    this->faces.push_back(face1);
    this->faces.push_back(face2);
    this->faces.push_back(face3);
    this->faces.push_back(face1);
    this->faces.push_back(face4);
    this->faces.push_back(face5);
    this->faces.push_back(face6);
    this->faces.push_back(face7);
    this->faces.push_back(face8);
    this->faces.push_back(face9);
    this->faces.push_back(face10);
    this->faces.push_back(face11);
    this->faces.push_back(face12);

    for (auto face: this->faces) {
        this->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
        this->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
        this->lines.emplace_back(face->point_indexes[2],face->point_indexes[3]);
        this->lines.emplace_back(face->point_indexes[3],face->point_indexes[4]);
        this->lines.emplace_back(face->point_indexes[4],face->point_indexes[0]);
    }
    /*
    point1->x = (cos(0) + cos(2 * M_PI / 5))/3; point1->y = (sin(0) + sin(2 * M_PI / 5)) /3; point1->z = ((sqrt(5)/2) + 0.5 + 0.5) /3;
    point2->x = (cos(2 * M_PI / 5) + cos(4 * M_PI / 5)) / 3; point2->y = (sin(2 * M_PI / 5)+sin(4 * M_PI / 5))/3; point2->z = ((sqrt(5)/2) + 0.5 + 0.5) /3;
    point3->x = (cos(4 * M_PI / 5) + cos(6 * M_PI / 5)) /3; point3->y = (sin(4 * M_PI / 5) + sin(6 * M_PI / 5)) /3; point3->z = ((sqrt(5)/2) + 0.5 + 0.5) /3;
    point4->x = (cos(6 * M_PI / 5) + cos((8 * M_PI / 5))) /3; point4->y = (sin(6 * M_PI / 5) + sin(8 * M_PI / 5)) /3; point4->z = ((sqrt(5)/2) + 0.5 + 0.5) /3;
    point5->x = (cos(8 * M_PI / 5) + cos(0)) /3; point5->y = (sin(8 * M_PI / 5) + sin(0)) /3; point5->z = ((sqrt(5)/2) + 0.5 + 0.5) /3;
    point6->x = (cos(0) + cos(M_PI / 5) + cos(2 * M_PI / 5)) /3; point6->y = (sin(0) + sin(M_PI / 5) + sin(2 * M_PI / 5)) /3; point6->z = (0.5 + 0.5 - 0.5) /3;

    point7->x = (cos(2 * M_PI / 5) + cos(M_PI / 5) + cos(M_PI / 5 + 2 * M_PI / 5)) /3; point7->y = (sin(2 * M_PI / 5) + sin(M_PI / 5) + sin(M_PI / 5 + 2 * M_PI / 5)) /3; point7->z = (0.5 + 0.5 + 0.5) /3;
    point8->x = (cos(2 * M_PI / 5) + cos(M_PI / 5 + 2 * M_PI / 5) + cos(4 * M_PI / 5)) /3; point8->y = (sin(2 * M_PI / 5) + sin(M_PI / 5 + 2 * M_PI / 5) + sin(4 * M_PI / 5)) /3; point8->z = (0.5 + 0.5 + 0.5) /3;
    point9->x = (cos(4 * M_PI / 5) + cos(M_PI / 5 + 2 * M_PI / 5) + cos(M_PI / 5 + 4 * M_PI / 5)) /3; point9->y = (sin(4 * M_PI / 5) + sin(M_PI / 5 + 2 * M_PI / 5) + sin(M_PI / 5 + 4 * M_PI / 5)) /3; point9->z = (0.5 + 0.5 + 0.5) /3;
    point10->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point10->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point10->z = (0.5 + 0.5 + 0.5) /3;
    point11->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point11->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point11->z = (0.5 + 0.5 + 0.5) /3;
    point12->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point12->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point12->z = (0.5 + 0.5 + 0.5) /3;
    point13->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point13->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point13->z = (0.5 + 0.5 + 0.5) /3;
    point14->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point14->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point14->z = (0.5 + 0.5 + 0.5) /3;
    point15->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point15->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point15->z = (0.5 + 0.5 + 0.5) /3;
    point16->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point16->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point16->z = (0.5 + 0.5 + 0.5) /3;
    point17->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point17->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point17->z = (0.5 + 0.5 + 0.5) /3;
    point18->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point18->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point18->z = (0.5 + 0.5 + 0.5) /3;
    point19->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point19->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point19->z = (0.5 + 0.5 + 0.5) /3;
    point20->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point20->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point20->z = (0.5 + 0.5 + 0.5) /3;
     */
}
void Figure::drawCone(const int n, const double h) {
    this->figureClass = Cone;

    auto * topPoint = new Vector3D;
    topPoint->x = 0; topPoint->y = 0; topPoint->z = h;
    this->points.push_back(topPoint);
    Vector3D * previousPoint = nullptr;
    Vector3D * firstPoint = nullptr;

    for (int i = 0; i < n; i++) {
        auto * newPoint = new Vector3D;
        if ( i == 0) {
            firstPoint = newPoint;
            newPoint->x = cos(0); newPoint->y = sin(0); newPoint->z = 0;
        } else {
            newPoint->x = cos((2*i*M_PI) / n); newPoint->y = sin((2*i*M_PI) / n); newPoint->z = 0;
            auto * newFace = new Face({previousPoint,newPoint,topPoint});
            this->faces.push_back(newFace);
        }

        this->points.push_back(newPoint);
        previousPoint = newPoint;
    }


    auto * newFace = new Face({firstPoint,previousPoint,topPoint});
    this->faces.push_back(newFace);

    for (auto face: this->faces) {
        this->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
        this->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
        this->lines.emplace_back(face->point_indexes[2],face->point_indexes[0]);
    }


}
void Figure::drawCylinder(const int n, const double h) {
    this->figureClass = Cylinder;

    Vector3D * previousPointDown = nullptr;
    Vector3D * previousPointUp = nullptr;
    Vector3D * firstPointDown = nullptr;
    Vector3D * firstPointUp = nullptr;

    vector<Vector3D*> upperPoints;
    vector<Vector3D*> downPoints;
    //auto * faceTop = new Face({});
    //auto * faceBottom = new Face({});
    for (int i = 0; i < n; i++) {
        auto * newPointDown = new Vector3D;
        auto * newPointUp = new Vector3D;
        if ( i == 0) {
            newPointDown->x = cos(0); newPointDown->y = sin(0); newPointDown->z = 0;
            newPointUp->x = cos(0); newPointUp->y = sin(0); newPointUp->z = h;
            firstPointDown = newPointDown;
            firstPointUp = newPointUp;
        } else {
            newPointDown->x = cos((2*i*M_PI) / n); newPointDown->y = sin((2*i*M_PI) / n); newPointDown->z = 0;
            newPointUp->x = cos((2*i*M_PI) / n); newPointUp->y = sin((2*i*M_PI) / n); newPointUp->z = h;
            auto * newFace = new Face({newPointDown,newPointUp,previousPointUp,previousPointDown});
            this->faces.push_back(newFace);
        }

        upperPoints.push_back(newPointUp);
        downPoints.push_back(newPointDown);
        this->points.push_back(newPointUp);
        this->points.push_back(newPointDown);
        previousPointUp = newPointUp;
        previousPointDown = newPointDown;

        //faceTop->point_indexes.push_back(newPointUp);
        //faceBottom->point_indexes.push_back(newPointDown);
    }

    auto * newFace = new Face({previousPointDown,previousPointUp,firstPointUp,firstPointDown});
    auto * upperFace = new Face(upperPoints);
    auto * lowerFace = new Face(downPoints);
    this->faces.push_back(newFace);
    this->faces.push_back(upperFace);
    this->faces.push_back(lowerFace);

    for (auto face: this->faces) {
        this->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
        this->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
        this->lines.emplace_back(face->point_indexes[2],face->point_indexes[3]);
        this->lines.emplace_back(face->point_indexes[3],face->point_indexes[0]);
    }
}
void Figure::drawSphere(const double radius, const int n) {

    this->drawIcosahedron();
    this->figureClass = Sphere;

    if (n != 0) {
        this->lines.clear();
    }

    vector<Face*> newFaces;
    for (int i = 0; i < n; i++) {
        for (auto face: this->faces) {

            auto * point1 = new Vector3D;
            point1->x = ((face->point_indexes[0]->x + face->point_indexes[1]->x) / 2);
            point1->y = ((face->point_indexes[0]->y + face->point_indexes[1]->y) / 2);
            point1->z = ((face->point_indexes[0]->z + face->point_indexes[1]->z) / 2);

            auto * point2 = new Vector3D;
            point2->x = ((face->point_indexes[0]->x + face->point_indexes[2]->x) / 2);
            point2->y = ((face->point_indexes[0]->y + face->point_indexes[2]->y) / 2);
            point2->z = ((face->point_indexes[0]->z + face->point_indexes[2]->z) / 2);

            auto * point3 = new Vector3D;
            point3->x = ((face->point_indexes[1]->x + face->point_indexes[2]->x) / 2);
            point3->y = ((face->point_indexes[1]->y + face->point_indexes[2]->y) / 2);
            point3->z = ((face->point_indexes[1]->z + face->point_indexes[2]->z) / 2);

            auto * newFace1 = new Face({face->point_indexes[0],point1,point2});
            auto * newFace2 = new Face({face->point_indexes[1],point3,point1});
            auto * newFace3 = new Face({face->point_indexes[2],point2,point3});
            auto * newFace4 = new Face({point1,point3,point2});
            this->points.push_back(point1);
            this->points.push_back(point2);
            this->points.push_back(point3);
            newFaces.push_back(newFace1);
            newFaces.push_back(newFace2);
            newFaces.push_back(newFace3);
            newFaces.push_back(newFace4);
        }

        this->faces.clear();

        for (auto face: newFaces) {
            this->faces.push_back(face);
        } newFaces.clear();
    }

    // Scaling all the points
    for (auto & point: this->points) {
        double r = sqrt(pow(point->x, 2) + pow(point->y,2) + pow(point->z,2));
        point->x = point->x / r;
        point->y = point->y / r;
        point->z = point->z / r;
    }

    for (auto face: this->faces) {
        this->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
        this->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
        this->lines.emplace_back(face->point_indexes[2],face->point_indexes[0]);
    }
}
void Figure::drawTorus(const double r, const double R, const int n, const int m) {
    this->figureClass = Torus;

    //vector<pair<Vector3D*,pair<int,int>>> pointTracker = {}; // Vector that keeps all the points and the i and j they are linked to
    vector<pair<Vector3D*,pair<int,int>>> firstCircle = {}; // All pairs that have i = 0;
    vector<pair<Vector3D*,pair<int,int>>> lastCircle = {}; // All pairs that have i = n;
    vector<pair<Vector3D*,pair<int,int>>> underCircle = {}; // All pairs that have j = 0;
    vector<pair<Vector3D*,pair<int,int>>> upperCircle = {}; // All pairs that have j = m;

    vector<vector<Vector3D*>> pointTracker = {};

    for (int i = 0; i < n; i++) {
        vector<Vector3D*> currentIPonts;
        for (int j = 0; j < m; j++) {
            auto *newPoint = new Vector3D;
            if (j == 0 and i == 0) {
                newPoint->x = (R + r * cos(0)) * cos(0);
                newPoint->y = (R + r * cos(0)) * sin(0);
                newPoint->z = r * sin(0);


            } else if (i == 0 and j != 0) {
                newPoint->x = (R + r * cos((2*j*M_PI) / m)) * cos(0);
                newPoint->y = (R + r * cos((2*j*M_PI) / m)) * sin(0);
                newPoint->z = r * sin((2*j*M_PI) / m);

            } else if (j == 0 and i != 0) {
                newPoint->x = (R + r * cos(0)) * cos((2*i*M_PI) / n);
                newPoint->y = (R + r * cos(0)) * sin((2*i*M_PI) / n);
                newPoint->z = r * sin(0);

            } else {
                newPoint->x = (R + r * cos((2*j*M_PI) /m)) * cos((2*i*M_PI) / n);
                newPoint->y = (R + r * cos((2*j*M_PI) /m)) * sin((2*i*M_PI) / n);
                newPoint->z = r * sin((2*j*M_PI) / m);
            }

            if (i == 0) {
                // Collecting all the points on the first circle
                firstCircle.emplace_back(newPoint,make_pair(i,j));
            }
            if (i == n - 1) {
                // Collecting all the points on the last circle
                lastCircle.emplace_back(newPoint,make_pair(i,j));
            }
            if (j == 0) {
                underCircle.emplace_back(newPoint,make_pair(i,j));
            }
            if (j == m - 1) {
                upperCircle.emplace_back(newPoint,make_pair(i,j));
            }
            currentIPonts.push_back(newPoint);
            this->points.push_back(newPoint);
        }
        pointTracker.push_back(currentIPonts);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            auto * newFace = new Face({pointTracker[i][j],pointTracker[(i+1) % n][j],pointTracker[(i+1) % n][(j+1) % m],pointTracker[i][(j+1) % m]});
            this->faces.push_back(newFace);
        }
    }



    for (auto face: this->faces) {
        this->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
        this->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
        this->lines.emplace_back(face->point_indexes[2],face->point_indexes[3]);
        this->lines.emplace_back(face->point_indexes[3],face->point_indexes[0]);
    }
}

// Rotating
Matrix Figure::rotateX(double angle) {

    //angle = angle * M_PI/180;

    Matrix matrix;
    matrix(1,1) = 1;
    matrix(2,2) = cos(angle);
    matrix(2,3) = sin(angle);
    matrix(3,2) = -sin(angle);
    matrix(3,3) = cos (angle);
    matrix(4,4) = 1;

    return matrix;
}
Matrix Figure::rotateY( double angle) {

    //angle = angle * M_PI/180;


    Matrix matrix;
    matrix(1,1) = cos(angle);
    matrix(1,3) = -sin(angle);
    matrix(2,2) = 1;
    matrix(3,1) = sin(angle);
    matrix(3,3) = cos(angle);
    matrix(4,4) = 1;

    return matrix;
}
Matrix Figure::rotateZ( double angle) {

    //angle = angle * M_PI/180;

    Matrix matrix;

    matrix(1,1) = cos(angle);
    matrix(1,2) = sin(angle);
    matrix(2,1) = -sin(angle);
    matrix(2,2) = cos(angle);
    matrix(3,3) = 1;
    matrix(4,4) = 1;

    return matrix;
}

// Translate and transform
Matrix Figure::translate(const Vector3D &vector) {

    Matrix matrix;

    matrix(1,1) = 1;
    matrix(2,2) = 1;
    matrix(3,3) = 1;
    matrix(4,1) = vector.x;
    matrix(4,2) = vector.y;
    matrix(4,3) = vector.z;
    matrix(4,4) = 1;
    return matrix;
}
void Figure::applyTransformation(Figure & figure, const Matrix & matrix) {

    for (auto & point: figure.points) {
        *point = *point * matrix;
    }
}
Matrix Figure::eyePointTrans(const Vector3D &eyepoint) {

    // Declaring the matrix
    Matrix matrix;

    // Declaring the polar coordinates
    double theta, phi, r;


    // Initialising theta, phi and r
    toPolar(eyepoint,theta,phi,r);

    Vector3D test = Vector3D::point(0,0,-r);

    matrix = rotateZ((-M_PI / 2) - theta) * rotateX(phi*(-1.0)) * translate(test);

    return matrix;
}

// Utils
void Figure::toPolar(const Vector3D &point, double &theta, double &phi, double &r) {

    // r
    r = sqrt(pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2));

    // theta

    theta = atan2(point.y, point.x);

    // phi
    phi = acos(point.z/r);
}
void Figure::triangulate(const Face * face) {

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


Point2D Figure::doProjection(const Vector3D * point, const double d) {

    Point2D point2D;
    if (point->z != 0) {
        point2D.x = ((d * point->x) / -point->z);
        point2D.y = ((d * point->y) / -point->z);
    } else {
        point2D.x = 0;
        point2D.y = 0;
    }

    return point2D;
}

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
        while (j < face->point_indexes.size()) {
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

vector<Figure*> Figure::fractalGen(const vector<Figure*>& allFractals, int nr_iterations, const double scale) {
    if (nr_iterations == 0) {
        return allFractals;
    } else {
        nr_iterations -= 1;
        vector<Figure*> currentNew;
        for (auto &figure: allFractals) {
            vector<Figure*> toAdd = figure->generateFract(scale);
            Utils::addToVector(currentNew, toAdd); // = figure->generateFract(scale);
        } return this->fractalGen(currentNew, nr_iterations, scale * 2); // TODO scale moet aangepast worden per iteratie maar ik weet niet hoe, alvast niet * 2
    }
}

vector<Figure*> Figure::generateFract(const double scale) {

    vector<Figure*> fractals; // Vector with all the fractals

    for (auto point: this->points) {
        auto * newFractal = new Figure;
        newFractal->identifyAndDraw(this->figureClass);
        //newFractal->drawCube();
        newFractal->applyTransformation(*newFractal,newFractal->scalefigure(1/scale));
        newFractal->applyTransformation(*newFractal,newFractal->translate(*point));
        fractals.push_back(newFractal);
    }
    return fractals;
}

vector<Figure*> Figure::generateFractal(int nr_iterations, const double scale) {

    return this->fractalGen({this},nr_iterations,scale);

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





