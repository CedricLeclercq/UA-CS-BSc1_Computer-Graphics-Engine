//
// Created by Cédric Leclercq on 29/04/2021.
//

#ifndef README_MD_FIGUREUTILS_H
#define README_MD_FIGUREUTILS_H
class Figure;

class FigureUtils {
public:
    static void scaleTranslateEye(Figure * figure, const Vector3D& centerVector, const Vector3D& eye, double scale, double rotateX, double rotateY, double rotateZ) {
        // rotate, scale and translate

        //applyTransformation(figure,translate(centerVector));

        Matrix final = scalefigure(scale) *
                       FigureUtils::rotateX(rotateX) *
                       FigureUtils::rotateY(rotateY) *
                       FigureUtils::rotateZ(rotateZ) *
                       translate(centerVector);


        applyTransformation(*figure, final);
        applyTransformation(*figure, eyePointTrans(eye));
    }

    static Matrix scalefigure(const double scale) {

        Matrix matrix;
        matrix(1,1) = scale;
        matrix(2,2) = scale;
        matrix(3,3) = scale;
        matrix(4,4) = 1;

        return matrix;
    }

// Rotating
    static Matrix rotateX(double angle) {

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

    static Matrix rotateY( double angle) {

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

    static Matrix rotateZ( double angle) {

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
    static Matrix translate(const Vector3D &vector) {

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

    static void applyTransformation(Figure & figure, const Matrix & matrix) {

        for (auto & point: figure.points) {
            *point = *point * matrix;
        }
    }

    static Matrix eyePointTrans(const Vector3D &eyepoint) {

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
    static void toPolar(const Vector3D &point, double &theta, double &phi, double &r) {

        // r
        r = sqrt(pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2));

        // theta

        theta = atan2(point.y, point.x);

        // phi
        phi = acos(point.z/r);
    }


    static Point2D doProjection(const Vector3D * point, const double d) {

        Point2D point2D;
        point2D.x = ((d * point->x) / -point->z);
        point2D.y = ((d * point->y) / -point->z);
        return point2D;
    }
};

#endif //README_MD_FIGUREUTILS_H
