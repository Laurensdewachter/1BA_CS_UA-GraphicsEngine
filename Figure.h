#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include <iostream>
#include <list>
#include <vector>
#include "utils/vector/vector3d.h"
#include "utils/easy_image.h"

struct Face {
    std::vector<int> point_indexes;
    Face() = default;
    explicit Face(std::vector<int> i) : point_indexes(std::move(i)) {}
};

struct Figure {
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    img::Color color;
};

using Figures3D = std::list<Figure>;

#endif
