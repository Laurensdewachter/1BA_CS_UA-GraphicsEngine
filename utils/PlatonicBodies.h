#ifndef ENGINE_PLATONICBODIES_H
#define ENGINE_PLATONICBODIES_H

#include <cmath>
#include "../Figure.h"

class PlatonicBodies {
public:
    static Figure* cubeFigure;
    static Figure* tetrahedronFigure;
    static Figure* octahedronFigure;
    static Figure* icosahedronFigure;
    static Figure* dodecahedronFigure;

    PlatonicBodies();

    static Figure getCubeFigure();

    static Figure getTetrahedronFigure();

    static Figure getOctahedronFigure();

    static Figure getIcosahedronFigure();

    static Figure getDodecahedronFigure();
};

#endif