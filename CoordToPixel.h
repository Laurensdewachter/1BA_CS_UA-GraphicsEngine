#ifndef ENGINE_COORDTOPIXEL_H
#define ENGINE_COORDTOPIXEL_H

#include <list>
#include <algorithm>
#include <cmath>
#include "utils/easy_image.h"


struct Point2D {
    double x;
    double y;
};

struct Line2D {
    Point2D p1;
    Point2D p2;
    img::Color color;

    double z1;
    double z2;
};

using Lines2D = std::list<Line2D>;

img::EasyImage coordToPixel(Lines2D &lines, double size, img::Color backgroundColor);

#endif