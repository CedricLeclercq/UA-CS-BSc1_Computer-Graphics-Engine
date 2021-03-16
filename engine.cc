#include "easy_image.h"
#include "ini_configuration.h"
#include "Line2D.h"
#include "l_parser.h"
#include "l_parser.cc"
#include "Figure.h"
#include "wireframe.h"

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

Matrix scalefigure(const double scale) {
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

Matrix rotateX(double angle) {

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

Matrix rotateY( double angle) {

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

Matrix rotateZ( double angle) {

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

Matrix translate(const Vector3D &vector) {

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

void applyTransformation(Figure & figure, const Matrix & matrix) {
    matrix.print(cout);
    for (auto & point: figure.points) {
        point = point * matrix;
    }
}

void toPolar(const Vector3D &point, double &theta, double &phi, double &r) {

    // r
    r = sqrt(pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2));

    // theta

    theta = atan2(point.y, point.x);

    // phi
    phi = acos(point.z/r);
}



Matrix eyePointTrans(const Vector3D &eyepoint) {

    // Declaring the matrix
    Matrix matrix;

    // Declaring the polar coordinates
    double theta, phi, r;


    // Initialising theta, phi and r
    toPolar(eyepoint,theta,phi,r);

    Vector3D test = Vector3D::point(0,0,-r);

    matrix = rotateZ((-M_PI / 2) - theta) * rotateX(phi*(-1.0)) * translate(test);

    /*
    // Debug
    cout << endl;
    cout << "Theta: " << theta << endl;
    cout << "Phi: " << phi << endl;
    cout << "R: " << r << endl;

    // Creating the eye point transformation matrix
    matrix(1,1) = -sin(theta);
    matrix(1,2) = -cos(theta) * cos(phi);
    matrix(1,3) = cos(theta) * sin (phi);
    matrix(2,1) = cos(theta);
    matrix(2,2) = -sin(theta) * cos(phi);
    matrix(2,3) = sin(theta) * sin (phi);
    matrix(3,2) = sin(phi);
    matrix(3,3) = cos(phi);
    matrix(4,3) = -r;
    matrix(4,4) = 1;
    return matrix;
     */
    return matrix;
}

Point2D doProjection(const Vector3D * point, const double d) {

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

img::EasyImage draw2DLines (const Lines2D &lines, const int size, const vector<double>& backgroundColor) {

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


    // TODO for debugging
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

    for (auto line: lines) {

        // Before actually drawing, apply the scaling factor d ...
        // ... and fixing the middle point of the image
        line.p1.x = line.p1.x * scalingFactorD + imageX / 2 - dcX;
        line.p1.y = line.p1.y * scalingFactorD + imageY / 2 - dcY;
        line.p2.x = line.p2.x * scalingFactorD + imageX / 2 - dcX;
        line.p2.y = line.p2.y * scalingFactorD + imageY / 2 - dcY;

        image.draw_line(roundToInt(line.p1.x),roundToInt(line.p1.y),roundToInt(line.p2.x),roundToInt(line.p2.y),img::Color(line.color.red,line.color.green,line.color.blue));
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

        //if ( letter == '+' || letter == '-' ) { cout << 1;
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
    img::EasyImage image = draw2DLines(lines,size, backgroundColor);
    return image;
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
    else if (typeString == "Wireframe") {

        Figure figure;
        int nrPoints = configuration["Figure0"]["nrPoints"].as_int_or_die();
        int nrLines = configuration["Figure0"]["nrLines"].as_int_or_die();

        int iterator = 0;
        string point;
        while (iterator < nrPoints) {
            point = "point";
            point += to_string(iterator);
            vector<double> points = configuration["Figure0"][point].as_double_tuple_or_die();
            Vector3D createdPoint;
            createdPoint.x = points[0];
            createdPoint.y = points[1];
            createdPoint.z = points[2];
            figure.points.push_back(createdPoint);
            iterator++;
        }
        iterator = 0;
        string line;
        vector<pair<Vector3D*,Vector3D*>> lines;
        while (iterator < nrLines) {
            line = "line";
            line += to_string(iterator);
            vector<int> newLines = configuration["Figure0"][line].as_int_tuple_or_die();
            //MyClass *myclass;
            //MyClass c;
            //myclass = & c;
            Vector3D *vector;
            vector = & figure.points[newLines[0]];
            Vector3D *vectorB;
            vectorB = & figure.points[newLines[1]];

            lines.emplace_back(vector,vectorB);

            iterator++;
        }

        // rotate, scale and translate



        vector<double> center = configuration["Figure0"]["center"].as_double_tuple_or_die();
        Vector3D centerVector;
        //centerVector.x = 0; centerVector.y = 0; centerVector.z = 0;
        centerVector.x = center[0]; centerVector.y = center[1]; centerVector.z = center[2];
        //applyTransformation(figure,translate(centerVector));

        Matrix final = scalefigure(configuration["Figure0"]["scale"].as_double_or_die()) *
                       rotateX(configuration["Figure0"]["rotateX"].as_double_or_die()) *
                       rotateY(configuration["Figure0"]["rotateY"].as_double_or_die()) *
                       rotateZ(configuration["Figure0"]["rotateZ"].as_double_or_die()) *
                       translate(centerVector);


        applyTransformation(figure,final);


        // Eye point transformation
        vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();
        Vector3D eye3D;
        eye3D.x = eye[0]; eye3D.y = eye[1]; eye3D.z = eye[2];
        applyTransformation(figure,eyePointTrans(eye3D));

        // Converting to 2D lines
        Lines2D lines2D;
        vector<double> color = configuration["Figure0"]["color"].as_double_tuple_or_die();

        for (auto & line3D: lines) {
            Line2D line2D;
            line2D.p1 = doProjection(line3D.first,1);
            line2D.p2 = doProjection(line3D.second,1);
            line2D.color.red = color[0] * 255;
            line2D.color.green = color[1] * 255;
            line2D.color.blue = color[2] * 255;
            lines2D.push_back(line2D);
        }

        cout << "All lines: ";
        for (auto linedd: lines2D) {
            cout << "p1: " << linedd.p1.x << "," << linedd.p1.y << endl << "p2: " << linedd.p2.x << "," << linedd.p2.y << endl;
        }

        return draw2DLines(lines2D,configuration["General"]["size"].as_int_or_die(),configuration["General"]["backgroundcolor"].as_double_tuple_or_die());
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
