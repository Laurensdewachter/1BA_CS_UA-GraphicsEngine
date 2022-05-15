#ifndef ENGINE_CLIPPING_H
#define ENGINE_CLIPPING_H

#include "Figure.h"

namespace Clipping {
    void clipFigure(Figure &fig, double dNear, double dFar, double right, double left, double top, double bottom);
}

#endif
