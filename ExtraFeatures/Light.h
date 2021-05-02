//
// Created by Cédric Leclercq on 30/04/2021.
//

#ifndef README_MD_LIGHT_H
#define README_MD_LIGHT_H
#include "../Figure/ExtraAndUtils/Color.h"
enum LightClass {Infinity, Point};

class Light {
public:
    Color ambientLight; // The ambient light component
    Color diffuseLight; // The diffuse light component
    Color specularLight; // The specular light component
    LightClass lightClass;

    /**
     * \brief Default contructor
     */
    Light()=default;
};


typedef std::vector<Light*> Lights3D; // Vector with light pointers

#endif //README_MD_LIGHT_H
