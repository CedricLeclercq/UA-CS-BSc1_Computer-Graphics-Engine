//
// Created by Cédric Leclercq on 22/02/2021.
//

#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H
#include "Point2D.h"
#include "Color.h"
#include <limits>
#include <utility>
using namespace std;


class Line2D {
public:
    Point2D p1{},p2{};
    Color color{};

    pair<double,double> z = make_pair(numeric_limits<double>::infinity(),-numeric_limits<double>::infinity());

    Line2D()=default;
    Line2D(Point2D point1, Point2D point2, Color color) {
        Line2D::p1 = point1;
        Line2D::p2 = point2;
        Line2D::color = color;
    }
};


#endif //ENGINE_LINE2D_H
