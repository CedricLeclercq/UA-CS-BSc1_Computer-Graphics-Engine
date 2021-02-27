#include "easy_image.h"
#include "ini_configuration.h"
#include "Line2D.h"
#include "l_parser.h"
#include "l_parser.cc"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <list>
#include <cmath>
using namespace std;
using Lines2D = std::list<Line2D>;


inline int roundToInt(double d) { return static_cast<int>(round(d)); }

img::EasyImage draw2DLines (img::EasyImage& image, const Lines2D &lines, const int size) {

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

    cout << endl << xMin << " " << xMax << " " << yMin << " " << yMax << endl << endl;

    // Defining xRange and yRange
    double xRange = xMax - xMin;
    double yRange = yMax - yMin;

    // Scaling for the size
    double imageX = size*(xRange/max(xRange,yRange));
    double imageY = size*(yRange/max(xRange,yRange));

    // Defining scaling factor d
    double scalingFactorD = 0.95*(imageX/xRange);

    // Defining dcX and dcY
    double dcX = scalingFactorD*(xMin+xMax)/2;
    double dcY = scalingFactorD*(yMin+yMax)/2;

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
        line.p1.x = line.p1.x * scalingFactorD + imageX / 2 - dcX; // TODO should these all be rounded to int?
        line.p1.y = line.p1.y * scalingFactorD + imageY / 2 - dcY;
        line.p2.x = line.p2.x * scalingFactorD + imageX / 2 - dcX;
        line.p2.y = line.p2.y * scalingFactorD + imageY / 2 - dcY;

        cout << line.p1.x << "; " << line.p1.y << "; " << line.p2.x << "; " << line.p2.y << endl; //TODO test code


        image.draw_line(line.p1.x,line.p1.y,line.p2.x,line.p2.y,img::Color(line.color.red,line.color.green,line.color.blue));
    }
    return image;
}

LParser::LSystem2D createLSystem2D(const string& inputfile) {

    LParser::LSystem2D l_system;
    ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();
    return l_system;
}

img::EasyImage LSystem2D(const LParser::LSystem2D&  sys, const vector<double>& backgroundColor, int size, vector<double> lineColor) {
    double currentAngle = sys.get_starting_angle();
    const set<char>& alphabet = sys.get_alphabet();
    const string& initiator = sys.get_initiator();
    img::EasyImage image(size,size);

    // First drawing the background
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-1; j++) {
            image(i,j).red = roundToInt(255 * backgroundColor[0]);
            image(i,j).green = roundToInt(255 * backgroundColor[1]);
            image(i,j).blue = roundToInt(255 * backgroundColor[2]);
        }
    }

    // Then creating a Lines2D object to draw later
    Lines2D lines;

    double currentX = 0;
    double currentY = 0;
    // Looping over the initiator and seeing what to do
    for (char letter: initiator) {

        if (letter == '+') {
            currentAngle += sys.get_angle() * M_PI / 180;

        } else if (letter == '-') {
            currentAngle -= sys.get_angle() * M_PI / 180;

        //if ( letter == '+' || letter == '-' ) { cout << 1;
        } else {
            Line2D line{};
            bool lengthDraw = sys.draw('F');
            if (lengthDraw) {
                line.p1.x = currentX;
                line.p1.y = currentY;
                line.p2.x = currentX + cos(currentAngle);
                line.p2.y = currentY + sin(currentAngle);
                line.color.red = roundToInt(255 * lineColor[0]);
                line.color.green = roundToInt(255 * lineColor[1]);
                line.color.blue = roundToInt(255 * lineColor[2]);
                lines.push_back(line);
            }
        }
    }
    image = draw2DLines(image,lines,size);
    //for (int i = 0; i < size; i++) { // TODO debugging remove before submission
        //for (int j = 0; j < size; j++) {
            //cout << image(i,j).blue << endl;
        //}
    //}
    return image;
}

img::EasyImage generate_image(const ini::Configuration &configuration) {

    img::EasyImage image;
    string typeString = configuration["General"]["type"].as_string_or_die();


    if (typeString == "2DLSystem") { // A 2DLSystem - initialising everything
        const string inputfile = configuration["2DLSystem"]["inputfile"];
        vector<double> color = configuration["2DLSystem"]["color"].as_double_tuple_or_die();
        vector<double> backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
        const int size = configuration["General"]["size"].as_int_or_die();
        ifstream input_stream(inputfile);
        LParser::LSystem2D lSystem2D = createLSystem2D(inputfile); // Creating the lSystem here from the input file
        image = LSystem2D(lSystem2D,backgroundColor, size, color);


    } //else img::EasyImage image1(configuration["ImageProperties"]["width"].as_int_or_die(), configuration["ImageProperties"]["height"].as_int_or_die());
    // First drawing the background
    //for (int i = 0; i < 1000; i++) {
        //for (int j = 0; j < 1000; j++) {
            //image(i,j).red = 1;
            //image(i,j).green = 1;
            //image(i,j).blue = 1;
        //}

	return image;
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
