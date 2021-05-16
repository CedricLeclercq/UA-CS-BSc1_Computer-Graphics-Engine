//
// Created by Cédric Leclercq on 25/04/2021.
//

#include "Utils.h"
#include "../Figure/Figure.h"
#include "../ExtraFeatures/Lsystems//l_parser.h"
#include "../ExtraFeatures/Lsystems/LSystemUtils.h"
#include "../Figure/ExtraAndUtils/FigureUtils.h"
#include "../ExtraFeatures/InfPointLight.h"


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

void Utils::convert3D(Figure &figure, Lines2D &lines2D, vector<double> color) {
    for (auto &line3D: figure.lines) {
        Line2D line2D;
        line2D.p1 = FigureUtils::doProjection(line3D.first, 1);
        line2D.p2 = FigureUtils::doProjection(line3D.second, 1);
        line2D.z = make_pair(line3D.first->z,line3D.second->z);
        line2D.color.red = color[0] * 255;
        line2D.color.green = color[1] * 255;
        line2D.color.blue = color[2] * 255;
        lines2D.push_back(line2D);
    }
}


vector<Light *> Utils::getLights(const ini::Configuration &config) {
    // Eye point transformation
    vector<double> eye = config["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye3D;
    eye3D.x = eye[0];
    eye3D.y = eye[1];
    eye3D.z = eye[2];
    vector<Light*> result;
    int nrOfLights = config["General"]["nrLights"].as_int_or_default(0); // Getting the amount of lights
    for (int it = 0; it < nrOfLights; it++) {
        string lightName = "Light" + to_string(it);
        bool infty = config[lightName]["infinity"].as_bool_or_default(true); // TODO check this
        vector<double> ambientLightV = config[lightName]["ambientLight"].as_double_tuple_or_default({1,1,1});
        vector<double> diffuseLightV = config[lightName]["diffuseLight"].as_double_tuple_or_default({0,0,0});
        vector<double> specularLightV = config[lightName]["specularLight"].as_double_tuple_or_default({0,0,0});
        Color ambientLight(ambientLightV[0],ambientLightV[1],ambientLightV[2]);
        Color diffuseLight(diffuseLightV[0],diffuseLightV[1],diffuseLightV[2]);
        Color specularLight(specularLightV[0],specularLightV[1],specularLightV[2]);
        if (not infty) {
            vector<double> locationV = config[lightName]["location"].as_double_tuple_or_default({1,1,1});
            Vector3D location = Vector3D::point(locationV[0],locationV[1],locationV[2]);
            FigureUtils::applyTransformationVector3D(location, FigureUtils::eyePointTrans(eye3D));
            double spotAngle = config[lightName]["spotAngle"].as_double_or_default(90);

            auto * newLight = new PointLight(location,spotAngle * M_PI/180,ambientLight,diffuseLight,specularLight);
            double size = config[lightName]["shadowMask"].as_double_or_default(0);
            newLight->shadowMask = ZBuffer((int)size,(int)size);
            result.push_back(newLight);
        } else {
            vector<double> directionV = config[lightName]["direction"].as_double_tuple_or_default({1,1,1});
            Vector3D dir = Vector3D::vector(directionV[0],directionV[1],directionV[2]);
            FigureUtils::applyTransformationVector3D(dir,FigureUtils::eyePointTrans(eye3D));
            //dir.x = directionV[0]; dir.y = directionV[1]; dir.z = directionV[2];
            auto * newLight = new InfLight(dir,ambientLight,diffuseLight,specularLight);
            result.push_back(newLight);
        }
    }
    return result;
}


