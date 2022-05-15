#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H

#include "vector3d.h"
#include "Figure.h"
#include "../CoordToPixel.h"

namespace Utils {
    void toPolar(const Vector3D &point, double &theta, double &phi, double &r);

    void splitTriangles(Figure &figure);

    void triangulate(Figure &fig);

    void calculateValues(Lines2D &lines, double size, double &width, double &height, double &d, double &dx, double &dy);

    Figures3D generateFractal(Figure &fig, unsigned int nrIterations, double scale);

    Figures3D generateMengerSponge(Figure &fig, unsigned int nrIterations);
}

#endif
