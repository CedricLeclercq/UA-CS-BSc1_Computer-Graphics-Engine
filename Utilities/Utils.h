//
// Created by Cédric Leclercq on 25/04/2021.
//

#ifndef README_MD_UTILS_H
#define README_MD_UTILS_H

#include "../Figure/Figure.h"


class Utils {
public:
    static vector<Figure*> filterOutFigure(const vector<Figure*>& allFiguresconst, Figure * toFilterOut);
    static void addToVector(vector<Figure *> &figures, vector<Figure *> &toAdd);
};


#endif //README_MD_UTILS_H
