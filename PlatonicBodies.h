#ifndef ENGINE_PLATONICBODIES_H
#define ENGINE_PLATONICBODIES_H

#include "Figure.h"

class PlatonicBodies {
Figure cubeFigure;
Figure tetrahedronFigure;
Figure octahedronFigure;
Figure icosahedronFigure;
Figure dodecahedronFigure;

public:
    PlatonicBodies();

    Figure getCubeFigure() const;

    Figure getTetrahedronFigure() const;

    Figure getOctahedronFigure() const;

    Figure getIcosahedronFigure() const;

    Figure getDodecahedronFigure() const;
};


#endif