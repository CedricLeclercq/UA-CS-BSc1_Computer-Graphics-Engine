//
// Created by Cédric Leclercq on 25/04/2021.
//

#include "LSystemUtils.h"
#include "../Utilities/easy_image.h"
#include "../Utilities/Utils.h"

inline int roundToInt(double d) { return static_cast<int>(round(d)); }

LParser::LSystem2D LSystemUtils::createLSystem2D(const string& inputfile) {
    LParser::LSystem2D l_system;
    ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();
    return l_system;
}

LParser::LSystem3D LSystemUtils::createLSystem3D(const string &inputfile) {
    LParser::LSystem3D l_system;
    ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();
    return l_system;
}

string LSystemUtils::recursiveInitiator(const LParser::LSystem2D& sys, const string& initiator, unsigned int nrOfIterations) {

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

img::EasyImage LSystemUtils::LSystem2D(const LParser::LSystem2D&  sys, const vector<double>& backgroundColor, int size, vector<double> lineColor) {
    double currentAngle = sys.get_starting_angle() * M_PI / 180;
    const string& initiator = sys.get_initiator();

    // Then creating a Lines2D object to draw later
    Lines2D lines;

    //cout << endl << initiator[0] << endl;
    //string test = sys.get_replacement(initiator[0]);

    //cout << endl << recursiveInitiator(sys,test,sys.get_nr_iterations()) << endl;
    string fullString = LSystemUtils::recursiveInitiator(sys,initiator,sys.get_nr_iterations());
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
    img::EasyImage image = Utils::draw2DLines(lines,size, backgroundColor, false);
    return image;
}

string LSystemUtils::recursiveInitiator3D(const LParser::LSystem3D &sys, const string &initiator,
                                          unsigned int nrOfIterations) {
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

img::EasyImage LSystemUtils::LSystem3D(const LParser::LSystem3D &sys, const vector<double> &backgroundColor, int size,
                                       const vector<double>& lineColor) {
    double currentAngle = sys.get_angle() * M_PI / 180;
    const string& initiator = sys.get_initiator();

    string fullString = LSystemUtils::recursiveInitiator3D(sys,initiator,sys.get_nr_iterations());

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
