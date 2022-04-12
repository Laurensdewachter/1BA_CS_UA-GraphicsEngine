#ifndef ENGINE_3DLINES_H
#define ENGINE_3DLINES_H

#include <iostream>
#include <utility>
#include <vector>
#include "utils/easy_image.h"
#include "utils/ini_configuration.h"
#include "utils/vector3d.h"
#include "CoordToPixel.h"
#include "utils/PlatonicBodies.h"
#include "utils/Figure.h"

Point2D doProjection(const Vector3D &point, double d);

Lines2D doProjection(const Figures3D &figs);

Figure eyeFigure(const ini::Configuration &configuration, std::string &figureName, Matrix &V);

Figure createCube(const ini::Configuration &configuration, std::string &figureName, Matrix &V);

Figure createTetrahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V);

Figure createOctahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V);

Figure createIcosahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V);

Figure createDodecahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V);

Figure createSphere(const ini::Configuration &configuration, std::string &figureName, Matrix &V);

Figure createCone(const ini::Configuration &configuration, std::string &figureName, Matrix &V);

Figure createCylinder(const ini::Configuration &configuration, std::string &figureName, Matrix &V);

Figure createTorus(const ini::Configuration &configuration, std::string &figureName, Matrix &V);

namespace Lines3D {
    img::EasyImage wireframe(const ini::Configuration &configuration);
}

#endif