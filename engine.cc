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
#include <utility>
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

string recursiveInitiator(const LParser::LSystem2D& sys, const string& initiator, unsigned int nrOfIterations) {

    string result;

    for (char k: initiator) {
        if (k != '-' and k != '+') {
            if (nrOfIterations != 0) {
                const string& newString = sys.get_replacement(k);
                result += newString;
            }
        } else if (k == '-') { result += '-';} else { result += '+'; }
    } nrOfIterations -= 1; cout << endl << endl << result << endl << endl; if (nrOfIterations != 0) {
        result = recursiveInitiator(sys,result,nrOfIterations);
    }

    return result;
    /*
    // Basis, if this is true, continue recursive
    for (char k: initiator) {

        if (k == '+' ) { result += '+'; }
        else if (k == '-' ) { result += '-'; }

        else if (nrOfIterations != 0) {
            nrOfIterations -= 1;
            string iteration = recursiveInitiator(sys,sys.get_replacement(k),nrOfIterations);
            result += iteration;
        } result += initiator;
        //nrOfIterations = sys.get_nr_iterations();
    }

    return result;
    */
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

    //cout << endl << initiator[0] << endl;
    string test = sys.get_replacement(initiator[0]);

    //cout << endl << recursiveInitiator(sys,test,sys.get_nr_iterations()) << endl;
    string testd = recursiveInitiator(sys,test,sys.get_nr_iterations()-1);
    //string testd = "XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF+F+XF-F+F-XF-F+F-XF-F+F-XF+F+XF-F+F-X";
    cout << testd;
    double currentX = 0;
    double currentY = 0;
    // Looping over the initiator and seeing what to do
    for (char letter: testd) {

        if (letter == '+') {
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
    image.draw2DLines(lines,size);
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


    }

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
