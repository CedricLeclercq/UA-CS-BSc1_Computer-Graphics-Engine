//
// Created by Cédric Leclercq on 25/04/2021.
//

#ifndef README_MD_LSYSTEMUTILS_H
#define README_MD_LSYSTEMUTILS_H

#include "iostream"
#include "fstream"
#include "l_parser.h"
#include "../../Image/easy_image.h"

using namespace std;


class LSystemUtils {
public:

     /**
    * Creates an Lsystem
    * @param inputfile
    * @return
    */
    static LParser::LSystem2D createLSystem2D(const string& inputfile);

    static LParser::LSystem3D createLSystem3D(const string& inputfile);

    static string recursiveInitiator(const LParser::LSystem2D &sys, const string &initiator, unsigned int nrOfIterations);


    static img::EasyImage LSystem2D(const LParser::LSystem2D &sys, const vector<double> &backgroundColor, int size, vector<double> lineColor);

    static string recursiveInitiator3D(const LParser::LSystem3D& sys, const string& initiator, unsigned int nrOfIterations);

    // TODO afwerken
    static img::EasyImage LSystem3D(const LParser::LSystem3D& sys, const vector<double>& backgroundColor, int size, const vector<double>& lineColor);
};


#endif //README_MD_LSYSTEMUTILS_H
