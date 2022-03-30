#ifndef ENGINE_3DLINES_H
#define ENGINE_3DLINES_H

#include <iostream>
#include <utility>
#include <vector>
#include "utils/easy_image.h"
#include "utils/ini_configuration.h"
#include "utils/vector3d.h"
#include "CoordToPixel.h"
#include "PlatonicBodies.h"
#include "Figure.h"

void toPolar(const Vector3D &point, double &theta, double &phi, double &r);

namespace trans {
    Matrix scaleFigure(double scale);

    Matrix rotateX(double angle);

    Matrix rotateY(double angle);

    Matrix rotateZ(double angle);

    Matrix translate(const Vector3D &vec);

    Matrix eyePointTrans(const Vector3D &eyepoint);

    void applyTransformation(Figure &fig, const Matrix &M);
}

Point2D doProjection(const Vector3D &point, double d);

Lines2D doProjection(const Figures3D &figs);

Figure eyeFigure(const ini::Configuration &configuration, std::string &figureName,
               Matrix &V);

Figure createCube(const ini::Configuration &configuration, Figure body, std::string &figureName,
                Matrix &V);

Figure createTetrahedron(const ini::Configuration &configuration, Figure body, std::string &figureName,
                       Matrix &V);

Figure createOctahedron(const ini::Configuration &configuration, Figure body, std::string &figureName,
                      Matrix &V);

Figure createIcosahedron(const ini::Configuration &configuration, Figure body, std::string &figureName,
                      Matrix &V);

Figure createDodecahedron(const ini::Configuration &configuration, Figure body, std::string &figureName,
                       Matrix &V);

namespace Lines3D {
    img::EasyImage wireframe(const ini::Configuration &configuration, PlatonicBodies &bodies);
}

#endif