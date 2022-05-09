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

    Figures3D generateFractal(Figure &fig, unsigned int nrIterations, double scale);

    void clip(Figure &fig, const double hfov, const double aspectRatio, const double dNear, const double hFar);
};


#endif