//
// Created by Cédric Leclercq on 05/03/2021.
//

#ifndef ENGINE_FACE_H
#define ENGINE_FACE_H
#include <vector>
#include "../Lines/vector3d.h"
using namespace std;


class Face {
public:
    // Variables
    std::vector<Vector3D*> point_indexes;

    // Constructor
    Face(vector<Vector3D*> s) {
        point_indexes = s;
    }

};


#endif //ENGINE_FACE_H
