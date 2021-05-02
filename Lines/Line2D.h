//
// Created by Cédric Leclercq on 22/02/2021.
//

#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H
#include "Point2D.h"
#include "../Figure/ExtraAndUtils/Color.h"
#include <limits>
#include <utility>
using namespace std;


class Line2D {
public:
    Point2D p1{},p2{}; // The two points where a line is being drawn between
    Color color{}; // Color of the line
    // ZValue of this line
    pair<double,double> z = make_pair(numeric_limits<double>::infinity(),-numeric_limits<double>::infinity());

    /**
     * \brief Default constructor
     */
    Line2D()=default;
    /**
     * \brief Constructor that receives a two points to draw a line between and the color the line should be -
     * will initialise all the values.
     * @param point1
     * @param point2
     * @param color
     */
    Line2D(Point2D point1, Point2D point2, Color color) {
        Line2D::p1 = point1;
        Line2D::p2 = point2;
        Line2D::color = color;
    }
};


#endif //ENGINE_LINE2D_H
