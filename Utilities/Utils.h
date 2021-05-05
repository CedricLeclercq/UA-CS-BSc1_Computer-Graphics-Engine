//
// Created by Cédric Leclercq on 25/04/2021.
//

#ifndef README_MD_UTILS_H
#define README_MD_UTILS_H

class Figure;
#include "../Image/easy_image.h"
#include "ini_configuration.h"


#include <fstream>


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

    /**
     * Converts all 3D points of a figure to a 2D points and adds it to a vector
     * @param figure
     * @param lines2D
     * @param color
     */
    static void convert3D(Figure & figure, Lines2D  & lines2D, vector<double> color);


    /**
     * Checks if a vector contains an element T
     * @tparam T
     * @param vector
     * @param element
     * @return      contains element
     */
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

    /**
     * Replaces an element T in a vector if its present
     * @tparam T
     * @param vector
     * @param element
     * @param secondElement
     */
    template<typename T>
    static void replace(std::vector<T>& vector, const T& element, const T& secondElement) {
        typedef typename std::vector<T>::iterator vectorIter;
        for (vectorIter iter = vector.begin(); iter != vector.end(); iter++) {
            if (*iter == element) {
                (*iter) = secondElement;
            }
        }
    }
    /**
     * Will read all the lights from an .ini file and return them collected in a vector of lights
     * @param config
     * @return
     */
    static vector<Light*> getLights(const ini::Configuration& config);



};


#endif //README_MD_UTILS_H
