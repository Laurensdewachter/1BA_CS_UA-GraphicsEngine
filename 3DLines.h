#ifndef ENGINE_3DLINES_H
#define ENGINE_3DLINES_H

#include <iostream>
#include <vector>
#include "utils/easy_image.h"
#include "utils/ini_configuration.h"
#include "utils/vector/vector3d.h"
#include "CoordToPixel.h"

struct Face {
    std::vector<int> point_indexes;
};

struct Figure {
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    img::Color color;
};

using Figures3D = std::list<Figure>;

void toPolar(const Vector3D &point, double &theta, double &phi, double &r);

namespace trans {
    Matrix scaleFigure(const double scale);

    Matrix rotateX(const double angle);

    Matrix rotateY(const double angle);

    Matrix rotateZ(const double angle);

    Matrix translate(const Vector3D &vec);

    Matrix eyePointTrans(const Vector3D &eyepoint);

    void applyTransformation(Figure &fig, const Matrix &M);
}

Point2D doProjection(const Vector3D &point, const double d);

Lines2D doProjection(const Figures3D &figs);

namespace Lines3D {
    img::EasyImage wireframe(const ini::Configuration &configuration);
}

#endif