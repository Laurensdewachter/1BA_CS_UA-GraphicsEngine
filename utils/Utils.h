#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H

#include "vector3d.h"
#include "Figure.h"
#include "../CoordToPixel.h"

namespace Utils {
    void toPolar(const Vector3D &point, double &theta, double &phi, double &r);

    void splitTriangles(Figure &figure);

    std::vector<Face> triangulate(const Face &face);

    void calculateValues(Lines2D &lines, double size, double &width, double &height, double &d, double &dx, double &dy);
};


#endif