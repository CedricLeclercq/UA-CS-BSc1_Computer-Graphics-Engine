//
// Created by Cédric Leclercq on 25/04/2021.
//

#include "Utils.h"

vector<Figure *> Utils::filterOutFigure(const vector<Figure*>& allFigures, Figure * toFilterOut) {
    vector<Figure*> filtered;
    for (auto figure: allFigures) {
        if (figure != toFilterOut) {
            filtered.push_back(figure);
        }
    }
    return filtered;
}

void Utils::addToVector(vector<Figure*>& figures, vector<Figure*>& toAdd) {
    for (auto figure: toAdd) {
        figures.push_back(figure);
    }
}
