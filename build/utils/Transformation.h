#ifndef ENGINE_TRANSFORMATION_H
#define ENGINE_TRANSFORMATION_H

#include "Figure.h"
#include "vector3d.h"

namespace Transformation {
    Matrix scaleFigure(double scale);

    Matrix rotateX(double angle);

    Matrix rotateY(double angle);

    Matrix rotateZ(double angle);

    Matrix translate(const Vector3D &vec);

    Matrix eyePointTrans(const Vector3D &eyepoint);

    void applyTransformation(Figure &fig, const Matrix &M);

    Matrix clippingTrans(const double theta, const double phi, const double r);
};


#endif