//
// Created by Cédric Leclercq on 05/03/2021.
//

#include "Figure.h"


void Figure::scaleTranslateEye(Vector3D centerVector, Vector3D eye, double scale, double rotateX, double rotateY, double rotateZ) {
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


void Figure::drawCube() {


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

}

void Figure::drawCone(const int n, const double h) {

}

void Figure::drawCylinder(const int n, const double h) {

}

void Figure::drawSphere(const double radius, const int n) {

}

void Figure::drawTorus(const double r, const double R, const int n, const int m) {

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
    matrix.print(cout);
    for (auto & point: figure.points) {
        *point = *point * matrix;
    }
}

void Figure::toPolar(const Vector3D &point, double &theta, double &phi, double &r) {

    // r
    r = sqrt(pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2));

    // theta

    theta = atan2(point.y, point.x);

    // phi
    phi = acos(point.z/r);
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


