#include "Utilities/easy_image.h"
#include "Utilities/ini_configuration.h"
#include "2Dobjects/Line2D.h"
#include "Lsystems/l_parser.h"
#include "Lsystems/l_parser.cc"
#include "Figure/Figure.h"
#include "Figure/Figure.cpp"
#include "Zbuffering/ZBuffer.h"
#include "Zbuffering/ZBuffer.cpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <list>
#include <cmath>
#include <utility>
#include <stack>
using namespace std;
using Lines2D = std::list<Line2D>;


inline int roundToInt(double d) { return static_cast<int>(round(d)); }

LParser::LSystem2D createLSystem2D(const string& inputfile) {

    LParser::LSystem2D l_system;
    ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();
    return l_system;
}

LParser::LSystem3D createLSystem3D(const string& inputfile) {

    LParser::LSystem3D l_system;
    ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();
    return l_system;
}

void convert3D(Figure & figure, Lines2D  & lines2D, vector<double> color) {

    for (auto &line3D: figure.lines) {
        Line2D line2D;
        line2D.p1 = figure.doProjection(line3D.first, 1);
        line2D.p2 = figure.doProjection(line3D.second, 1);
        line2D.z = make_pair(line3D.first->z,line3D.second->z);
        line2D.color.red = color[0] * 255;
        line2D.color.green = color[1] * 255;
        line2D.color.blue = color[2] * 255;
        lines2D.push_back(line2D);
    }

    // TODO add garbage collection after turning the object in 2D
}



img::EasyImage draw2DLines (const Lines2D &lines, const int size, const vector<double>& backgroundColor, bool zBuffering) {

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

string recursiveInitiator(const LParser::LSystem2D& sys, const string& initiator, unsigned int nrOfIterations) {

    string result;

    for (char k: initiator) {
        if (k != '-' and k != '+' and k != '(' and k != ')') {
            if (nrOfIterations != 0) {
                const string& newString = sys.get_replacement(k);
                result += newString;
            }
        } else if (k == '-') { result += '-';}
          else if (k == '+') { result += '+';}
          else if (k == '(') { result += '(';}
          else { result += ')';}
    } nrOfIterations -= 1; cout << endl << endl << result << endl << endl;

    if (nrOfIterations != 0) {
        result = recursiveInitiator(sys,result,nrOfIterations);
    }

    return result;
}

string recursiveInitiator3D(const LParser::LSystem3D& sys, const string& initiator, unsigned int nrOfIterations) {
    string result;

    for (char k: initiator) {
        if (k != '-' and k != '+' and k != '(' and k != ')' and k != '/' and k != '\\' and k != '&' and k != '|' and k != '^') {
            if (nrOfIterations != 0) {
                const string& newString = sys.get_replacement(k);
                result += newString;
            }
        } else if (k == '-') { result += '-';}
        else if (k == '+') { result += '+';}
        else if (k == '(') { result += '(';}
        else if (k == ')') { result += ')';}
        else if (k == '/') { result += '/';}
        else if (k == '\\') { result += '\\';}
        else if (k == '&') { result += '&'; }
        else if (k == '|') { result += '|'; }
        else { result += '^'; }
    } nrOfIterations -= 1; cout << endl << endl << result << endl << endl;

    if (nrOfIterations != 0) {
        result = recursiveInitiator3D(sys,result,nrOfIterations);
    }

    return result;
}

img::EasyImage LSystem2D(const LParser::LSystem2D&  sys, const vector<double>& backgroundColor, int size, vector<double> lineColor) {
    double currentAngle = sys.get_starting_angle() * M_PI / 180;
    const string& initiator = sys.get_initiator();

    // Then creating a Lines2D object to draw later
    Lines2D lines;

    //cout << endl << initiator[0] << endl;
    //string test = sys.get_replacement(initiator[0]);

    //cout << endl << recursiveInitiator(sys,test,sys.get_nr_iterations()) << endl;
    string fullString = recursiveInitiator(sys,initiator,sys.get_nr_iterations());
    cout << fullString << endl;
    double currentX = 0;
    double currentY = 0;
    stack<pair<pair<double,double>,double>> stack; // ((x,y),angle)

    // Looping over the initiator and seeing what to do
    for (char letter: fullString) {

        if (letter == '(') {
            stack.push(make_pair(make_pair(currentX,currentY),currentAngle));
        } else if (letter == ')') {
            currentX = stack.top().first.first;
            currentY = stack.top().first.second;
            currentAngle = stack.top().second;
            stack.pop();

        } else if (letter == '+') {
                currentAngle += sys.get_angle() * M_PI / 180;

        } else if (letter == '-') {
            currentAngle -= sys.get_angle() * M_PI / 180;

        } else {
            Line2D line{};
            bool lengthDraw = sys.draw(letter);
            if (lengthDraw) {
                line.p1.x = currentX;
                line.p1.y = currentY;
                line.p2.x = currentX + cos(currentAngle);
                line.p2.y = currentY + sin(currentAngle);
                currentX = line.p2.x;
                currentY = line.p2.y;
                line.color.red = roundToInt(255 * lineColor[0]);
                line.color.green = roundToInt(255 * lineColor[1]);
                line.color.blue = roundToInt(255 * lineColor[2]);
                lines.push_back(line);
            }
        }
    }
    img::EasyImage image = draw2DLines(lines,size, backgroundColor, false);
    return image;
}


// TODO afwerken
img::EasyImage LSystem3D(const LParser::LSystem3D& sys, const vector<double>& backgroundColor, int size, vector<double> lineColor) {
    double currentAngle = sys.get_angle() * M_PI / 180;
    const string& initiator = sys.get_initiator();

    string fullString = recursiveInitiator3D(sys,initiator,sys.get_nr_iterations());

    auto * currentXYZ = new Vector3D;
    currentXYZ->x = 0; currentXYZ->y = 0; currentXYZ->z = 0;
    stack<pair<Vector3D*,double>> stack;

    for (char letter: fullString) {
        if (letter == '(') {
            stack.push(make_pair(currentXYZ,currentAngle));

        } else if (letter == ')') {
            currentXYZ = stack.top().first;
            currentAngle = stack.top().second;
            stack.pop();

        } else if (letter == '|') {


        } else if (letter == '^') {
            

        } else if (letter == '&') {

        } else if (letter == '/') {

        } else if (letter == '\\') {

        } else {

        }
    }


}

img::EasyImage generate_image(const ini::Configuration &configuration) {

    string typeString = configuration["General"]["type"].as_string_or_die();


    /*
     * Reading a 2DLSystem
     */
    if (typeString == "2DLSystem") {
        const string inputfile = configuration["2DLSystem"]["inputfile"].as_string_or_die();
        vector<double> color = configuration["2DLSystem"]["color"].as_double_tuple_or_die();
        vector<double> backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
        const int size = configuration["General"]["size"].as_int_or_die();
        ifstream input_stream(inputfile);
        LParser::LSystem2D lSystem2D = createLSystem2D(inputfile); // Creating the lSystem here from the input file
        return LSystem2D(lSystem2D,backgroundColor, size, color);
    }

    /*
     * Reading a Wireframe
     */
    else if (typeString == "Wireframe" or typeString == "ZBufferedWireframe" or typeString == "ZBuffering") {
        Lines2D lines2D;

        int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
        int figureIterator = 0;
        string figureName;

        vector<Figure> allFigures;

        while (figureIterator < nrFigures) {


            // Getting all the data for this figure
            figureName = "Figure" + to_string(figureIterator);
            vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();
            vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
            Vector3D centerVector;
            //centerVector.x = 0; centerVector.y = 0; centerVector.z = 0;
            centerVector.x = center[0];
            centerVector.y = center[1];
            centerVector.z = center[2];
            double scale = configuration[figureName]["scale"].as_double_or_die();
            double rotateX = M_PI / 180 * configuration[figureName]["rotateX"].as_double_or_die();
            double rotateY = M_PI / 180 * configuration[figureName]["rotateY"].as_double_or_die();
            double rotateZ = M_PI / 180 * configuration[figureName]["rotateZ"].as_double_or_die();
            // Eye point transformation
            vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();
            Vector3D eye3D;
            eye3D.x = eye[0];
            eye3D.y = eye[1];
            eye3D.z = eye[2];
            // All data has been read here


            // Line drawing
            if (configuration[figureName]["type"].as_string_or_die() == "LineDrawing") {


                int nrPoints = configuration[figureName]["nrPoints"].as_int_or_die();
                int nrLines = configuration[figureName]["nrLines"].as_int_or_die();


                Figure figure;
                int iterator = 0;
                string point;
                while (iterator < nrPoints) {
                    point = "point";
                    point += to_string(iterator);
                    vector<double> points = configuration[figureName][point].as_double_tuple_or_die();
                    auto * createdPoint = new Vector3D;
                    createdPoint->x = points[0];
                    createdPoint->y = points[1];
                    createdPoint->z = points[2];
                    figure.points.push_back(createdPoint);
                    iterator++;
                }
                iterator = 0;
                string line;
                //vector<pair<Vector3D *, Vector3D *>> lines;
                while (iterator < nrLines) {
                    line = "line";
                    line += to_string(iterator);
                    vector<int> newLines = configuration[figureName][line].as_int_tuple_or_die();
                    Vector3D *vector = figure.points[newLines[0]];
                    Vector3D *vectorB = figure.points[newLines[1]];

                    figure.lines.emplace_back(vector, vectorB);

                    iterator++;
                }
                figure.scaleTranslateEye(centerVector,eye3D,scale,rotateX,rotateY,rotateZ);
                convert3D(figure,lines2D,color);
            }

            // The figure that will be written on
            Figure figure;
            // Drawing a cube
            if (configuration[figureName]["type"].as_string_or_die() == "Cube") {
                figure.drawCube();
            }

            // Drawing a Tetrahedron
            if (configuration[figureName]["type"].as_string_or_die() == "Tetrahedron") {
                figure.drawTetrahedron();
            }

            // Drawing a Octahedron
            if (configuration[figureName]["type"].as_string_or_die() == "Octahedron") {
                figure.drawOctahedron();
            }

            // Drawing a Icosahedron
            if (configuration[figureName]["type"].as_string_or_die() == "Icosahedron") {
                figure.drawIcosahedron();
            }

            // Drawing a Dodecahedron
            if (configuration[figureName]["type"].as_string_or_die() == "Dodecahedron") {
                figure.drawDodecahedron();
            }

            // Drawing a Cone
            if (configuration[figureName]["type"].as_string_or_die() == "Cone") {
                figure.drawCone(configuration[figureName]["n"].as_int_or_die(), configuration[figureName]["height"].as_double_or_die());
            }

            // Drawing a Cylinder
            if (configuration[figureName]["type"].as_string_or_die() == "Cylinder") {
                figure.drawCylinder(configuration[figureName]["n"].as_int_or_die(), configuration[figureName]["height"].as_double_or_die());
            }

            // Drawing a Sphere
            if (configuration[figureName]["type"].as_string_or_die() == "Sphere") {
                figure.drawSphere(0,configuration[figureName]["n"].as_int_or_die());
            }

            // Drawing a Torus
            if (configuration[figureName]["type"].as_string_or_die() == "Torus") {
                figure.drawTorus(configuration[figureName]["r"].as_double_or_die(),configuration[figureName]["R"].as_double_or_die(),
                                 configuration[figureName]["n"].as_int_or_die(),configuration[figureName]["m"].as_int_or_die());

            }

            // Scaling and converting to 3D
            figure.scaleTranslateEye(centerVector,eye3D,scale,rotateX,rotateY,rotateZ); // TODO in de if hier onder of gewoon hier laten?
            if (typeString != "ZBuffering") {
                convert3D(figure, lines2D, color);
            }

                // Drawing a 3DLsystem
            if (configuration[figureName]["type"].as_string_or_die() == "3DLSystem") {
                LParser::LSystem3D l_system = createLSystem3D(configuration[figureName]["inputfile"].as_string_or_die());
                LSystem3D(l_system,configuration["General"]["backgroundcolor"].as_double_tuple_or_die(),configuration["General"]["size"].as_int_or_die(),
                          configuration[figureName]["color"].as_double_tuple_or_die());
            }


            //img::Color imgColor(color[0] * 255,color[1] * 255,color[2] * 255);
            figure.color.red = color[0] * 255; figure.color.green = color[1] * 255; figure.color.blue = color[2] * 255;
            allFigures.push_back(figure);
            figureIterator++;
        }
        if (typeString == "ZBuffering") {

            vector<Point2D> allProjectedPoints;
            for (const auto & figure: allFigures) {
                for (auto face: figure.faces) {
                    Point2D projectedA(((face->point_indexes[0]->x) / -face->point_indexes[0]->z), ((face->point_indexes[0]->y) / -face->point_indexes[0]->z));
                    Point2D projectedB(((face->point_indexes[1]->x) / -face->point_indexes[1]->z), ((face->point_indexes[1]->y) / -face->point_indexes[1]->z));
                    Point2D projectedC(((face->point_indexes[2]->x) / -face->point_indexes[2]->z), ((face->point_indexes[2]->y) / -face->point_indexes[2]->z));
                    allProjectedPoints.push_back(projectedA); allProjectedPoints.push_back(projectedB); allProjectedPoints.push_back(projectedC);
                }
            }
            double xMax = 0;
            double yMax = 0;

            for (auto & line: allProjectedPoints) {
                xMax = max(line.x,xMax);
                yMax = max(line.y,yMax);
            }

            double xMin = xMax;
            double yMin = yMax;

            for (auto & line: allProjectedPoints) {
                xMin = min(line.x,xMin);
                yMin = min(line.y,yMin);
            }





            double xRange = abs(xMax - xMin);
            cout << xRange << endl;
            double yRange = abs(yMax - yMin);

            double imageX = configuration["General"]["size"].as_double_or_die() *(xRange/max(xRange,yRange));
            double imageY = configuration["General"]["size"].as_double_or_die() *(yRange/max(xRange,yRange));




            double d = 0.95 * (imageX / xRange);
            double dcX = d*(xMin+xMax)/2;
            double dcY = d*(yMin+yMax)/2;

            double dx = (imageX / 2.0) -dcX;
            double dy = (imageY / 2.0) -dcY;

            cout << "d " << d << " dx " << dx << " dy " << dy << endl;


            img::EasyImage image(imageX,imageY);

            for (auto & figure: allFigures) {
                figure.triangulateAll();
            }



            ZBuffer zbuffer(image.get_width(),image.get_height());
            for (const auto& figure: allFigures) {
                for (auto face: figure.faces) {
                    vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();
                    img::Color imgColor(figure.color.red, figure.color.green, figure.color.blue);
                    image.draw_zbuf_triag(zbuffer,face->point_indexes[0],face->point_indexes[1],face->point_indexes[2],d,dx,dy,imgColor);
                }
            }

            //cout << "made it";
            //image.draw_line(0,0,1000,1000,{1,0,0});
            return image;
        }

        if (typeString == "ZBufferedWireframe") {
            return draw2DLines(lines2D, configuration["General"]["size"].as_int_or_die(),
                               configuration["General"]["backgroundcolor"].as_double_tuple_or_die(),true);
        } else {
            return draw2DLines(lines2D, configuration["General"]["size"].as_int_or_die(),
                               configuration["General"]["backgroundcolor"].as_double_tuple_or_die(),false);
        }
    }
    img::EasyImage imaged;
    return imaged;
}

int main(int argc, char const* argv[])
{
        int retVal = 0;
        try
        {
                for(int i = 1; i < argc; ++i)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(argv[i]);
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << argv[i] << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string fileName(argv[i]);
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << argv[i] << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory)
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
		//mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}
