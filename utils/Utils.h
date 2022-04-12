#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H

#include "vector3d.h"
#include "Figure.h"

class Utils {
public:
    static void toPolar(const Vector3D &point, double &theta, double &phi, double &r);

    static void splitTriangles(Figure &figure);
};


#endif