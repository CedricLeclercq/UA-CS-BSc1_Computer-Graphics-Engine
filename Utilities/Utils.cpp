//
// Created by Cédric Leclercq on 25/04/2021.
//

#include "Utils.h"

inline int roundToInt(double d) { return static_cast<int>(round(d)); }

vector<Figure *> Utils::filterOutFigure(const vector<Figure*>& allFigures, Figure * toFilterOut) {
    vector<Figure*> filtered;
    for (auto figure: allFigures) {
        if (figure != toFilterOut) {
            filtered.push_back(figure);
        }
    }
    return filtered;
}

void Utils::addToVector(vector<Figure*>& figures, vector<Figure*>& toAdd) {
    for (auto figure: toAdd) {
        figures.push_back(figure);
    }
}

img::EasyImage Utils::draw2DLines (const Lines2D &lines, const int size, const vector<double>& backgroundColor, bool zBuffering) {

    //Finding xMin, xMax, yMin, yMax
    double xMin = size;
    double xMax = 0;
    double yMin = size;
    double yMax = 0;

    for (auto line: lines) {

        // First point
        if (line.p1.x < xMin) { xMin = line.p1.x; }
        if (line.p1.x > xMax) { xMax = line.p1.x; }
        if (line.p1.y < yMin) { yMin = line.p1.y; }
        if (line.p1.y > yMax) { yMax = line.p1.y; }

        // Second point
        if (line.p2.x < xMin) { xMin = line.p2.x; }
        if (line.p2.x > xMax) { xMax = line.p2.x; }
        if (line.p2.y < yMin) { yMin = line.p2.y; }
        if (line.p2.y > yMax) { yMax = line.p2.y; }
    }
    // Defining xRange and yRange
    double xRange = xMax - xMin;
    double yRange = yMax - yMin;

    // Scaling for the size
    double imageX = size*(xRange/max(xRange,yRange));
    double imageY = size*(yRange/max(xRange,yRange));


    img::EasyImage image(roundToInt(imageX),roundToInt(imageY),img::Color(255 * backgroundColor[0],255 * backgroundColor[1],255 * backgroundColor[2]));

    // Defining scaling factor d
    double scalingFactorD = 0.95*(imageX/xRange);

    // Defining dcX and dcY
    double dcX = scalingFactorD*(xMin+xMax)/2;
    double dcY = scalingFactorD*(yMin+yMax)/2;


    /*

    cout << endl << endl;
    cout << "Values:" << endl;
    cout << endl << "xMin = " << xMin;
    cout << endl << "xMax = " << xMax;
    cout << endl << "yMin = " << yMin;
    cout << endl << "yMax = " << yMax;
    cout << endl << endl << endl;

    cout << endl << "xRange = " << xRange;
    cout << endl << "yRange = " << yRange;
    cout << endl << "imageX = " << imageX;
    cout << endl << "imageY = " << imageY;
    cout << endl << "scaling factor d = " << scalingFactorD;
    cout << endl << "dcX = " << dcX;
    cout << endl << "dcY = " << dcY;
    cout << endl << endl << endl;

     */
    ZBuffer zbuffer(image.get_width(),image.get_height());
    for (auto line: lines) {


        // Before actually drawing, apply the scaling factor d ...
        // ... and fixing the middle point of the image
        line.p1.x = line.p1.x * scalingFactorD + imageX / 2 - dcX;
        line.p1.y = line.p1.y * scalingFactorD + imageY / 2 - dcY;
        line.p2.x = line.p2.x * scalingFactorD + imageX / 2 - dcX;
        line.p2.y = line.p2.y * scalingFactorD + imageY / 2 - dcY;
        if (zBuffering) {

            image.draw_zbuf_line(zbuffer, line.p1.x, line.p1.y, line.z.first, line.p2.x, line.p2.y, line.z.second,
                                 img::Color(line.color.red, line.color.green, line.color.blue));

        } else {
            image.draw_line(roundToInt(line.p1.x), roundToInt(line.p1.y), roundToInt(line.p2.x), roundToInt(line.p2.y),
                            img::Color(line.color.red, line.color.green, line.color.blue));
        }

    }
    return image;
}
