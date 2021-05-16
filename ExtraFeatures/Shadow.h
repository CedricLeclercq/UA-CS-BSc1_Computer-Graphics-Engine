//
// Created by Cédric Leclercq on 16/05/2021.
//

#ifndef ENGINE_SHADOW_H
#define ENGINE_SHADOW_H

class Shadow {
public:
    static bool shadowPrevention(double lX, double lY, double lZ, ZBuffer &shadowMask);

};

bool Shadow::shadowPrevention(double lX, double lY, double lZ, ZBuffer &shadowMask) {
    bool result = true;

    double alphaX = lX - floor(lX);
    double alphaY = lY - floor(lY);
    double Za = shadowMask[floor(lX)][ceil(lY)];
    double Zb = shadowMask[ceil(lX)][ceil(lY)];
    double Zc = shadowMask[floor(lX)][floor(lY)];
    double Zd = shadowMask[ceil(lX)][floor(lY)];
    double Ze = (1 - alphaX) * Za + alphaX * Zb;
    double Zf = (1 - alphaX) * Zc + alphaX * Zd;
    double Zl = alphaY * Ze + (1 - alphaY) * Zf;

    if (abs(Zl - 1.0 / lZ) > pow(10,-4)) {
        result = false;
    }
    return result;
}

#endif //ENGINE_SHADOW_H
