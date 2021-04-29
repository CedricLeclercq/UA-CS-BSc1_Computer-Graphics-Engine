//
// Created by Cédric Leclercq on 25/04/2021.
//

#ifndef README_MD_UTILS_H
#define README_MD_UTILS_H

#include "../Figure/Figure.h"
#include "../Utilities/easy_image.h"



class Utils {
public:
    /**
     * Filters out a figure out of a vector of figures
     * @param allFiguresconst
     * @param toFilterOut
     * @return
     */
    static vector<Figure*> filterOutFigure(const vector<Figure*>& allFiguresconst, Figure * toFilterOut);
    /**
     * Adds a vector to another
     * @param figures
     * @param toAdd
     */
    static void addToVector(vector<Figure *> &figures, vector<Figure *> &toAdd);

    static img::EasyImage draw2DLines (const Lines2D &lines, const int size, const vector<double>& backgroundColor, bool zBuffering);



};


#endif //README_MD_UTILS_H
