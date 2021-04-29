//
// Created by Cédric Leclercq on 25/04/2021.
//

#ifndef README_MD_UTILS_H
#define README_MD_UTILS_H

#include "../Figure/Figure.h"
#include "../Utilities/easy_image.h"
#include "ini_configuration.h"
#include "../Lsystems/l_parser.h"
#include "../Lsystems/LSystemUtils.h"
#include "../Figure/FigureUtils.h"

#include <fstream>
#include <iostream>


class Utils {
public:

    /**
     * Will generate an image according to the configuration file
     * @param configuration
     * @return  image to draw
     */
    static img::EasyImage generate_image(const ini::Configuration &configuration);
    /**
     * Filters out a figure out of a vector of figures
     * @param allFiguresconst
     * @param toFilterOut
     * @return
     */
    static vector<Figure*> filterOutFigure(const vector<Figure*>& allFiguresConst, Figure * toFilterOut);
    /**
     * Adds a vector to another
     * @param figures
     * @param toAdd
     */
    static void addToVector(vector<Figure *> &figures, vector<Figure *> &toAdd);
    /**
     * Creates an image, writes 2DLines on it, and returns the image
     * @param lines
     * @param size
     * @param backgroundColor
     * @param zBuffering
     * @return
     */
    static img::EasyImage draw2DLines (const Lines2D &lines, int size, const vector<double>& backgroundColor, bool zBuffering);

    static void convert3D(Figure & figure, Lines2D  & lines2D, vector<double> color);


    template<typename T>
    static bool contains(const std::vector<T> &vector, const T& element) {
        typedef typename std::vector<T>::const_iterator vectorIter;
        for (vectorIter iter = vector.begin(); iter != vector.end(); iter++) {
            if (*iter == element) {
                return true;
            }
        }
        return false;
    }

    template<typename T>
    static void replace(std::vector<T>& vector, const T& element, const T& secondElement) {
        typedef typename std::vector<T>::iterator vectorIter;
        for (vectorIter iter = vector.begin(); iter != vector.end(); iter++) {
            if (*iter == element) {
                (*iter) = secondElement;
            }
        }
    }



};


#endif //README_MD_UTILS_H
