//
// Created by Cédric Leclercq on 30/04/2021.
//

#ifndef ENGINE_INFPOINTLIGHT_H
#define ENGINE_INFPOINTLIGHT_H
#include "../Lines/vector3d.h"
#include "Light.h"


class InfLight: public Light {
public:
    Vector3D ldVector; // Direction that the light shines in
    /**
     * \brief Default constructor
     */
    InfLight()=default;
    /**
     * \brief Constructor that initialises all member variables of the class
     * @param newLdVector
     * @param ambientLight
     * @param diffuseLight
     * @param specularLight
     */
    InfLight(const Vector3D& newLdVector, const Color & ambientLight, const Color & diffuseLight, const Color & specularLight) : Light() {
        this->ldVector = newLdVector;
        this->ambientLight = ambientLight;
        this->diffuseLight = diffuseLight;
        this->specularLight = specularLight;
        this->lightClass = Infinity;
    }
};

class PointLight: public Light {
public:
    Vector3D location; // Location of the light source
    double spotAngle{}; // Angle of the light source
    ZBuffer shadowMask;
    Matrix eye;
    double d;
    double dx;
    double dy;


    /**
     * \brief Default constructor
     */
    PointLight()=default;
    /**
     * \brief Constructor that initialises all member variables of the class
     * @param location
     * @param spotAngle
     * @param ambientLight
     * @param diffuseLight
     * @param specularLight
     */
    PointLight(const Vector3D& location, const double spotAngle, const Color& ambientLight, const Color& diffuseLight, const Color& specularLight) : Light() {
        this->location = location;
        this->spotAngle = spotAngle;
        this->ambientLight = ambientLight;
        this->diffuseLight = diffuseLight;
        this->specularLight = specularLight;
        this->lightClass = Point;
    }
};

#endif //ENGINE_INFPOINTLIGHT_H
