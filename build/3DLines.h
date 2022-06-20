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

Lines2D doProjectionConst(const Figures3D &figs);

Figure createEyeFigure(const ini::Configuration &configuration, std::string &figureName, Matrix &V);
Figures3D createThickEyeFigure(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);

Figures3D generateThickFigures(Figure &fig, double r, unsigned int n, unsigned int m);

Figure createCube(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figures3D createFractalCube(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figures3D createThickCube(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);

Figure createTetrahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figures3D createFractalTetrahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figures3D createThickTetrahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);

Figure createOctahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figures3D createFractalOctahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figures3D createThickOctahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);

Figure createIcosahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figures3D createFractalIcosahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figures3D createThickIcosahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);

Figure createDodecahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figures3D createFractalDodecahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figures3D createThickDodecahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);

Figure createSphere(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);

Figure createCone(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);

Figure createCylinder(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figure createLineCylinder(int n, double height);

Figure createTorus(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);

Figure createBuckyBall(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figures3D createFractalBuckyBall(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);
Figures3D createThickBuckyBall(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);

Figures3D createMengerSponge(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);

Figures3D createThick3DLSystem(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light = false);

Figure createRoad(const ini::Configuration &configuration, std::string &figureName, Matrix &V);

namespace Lines3D {
    img::EasyImage wireframe(const ini::Configuration &configuration, bool zBuffer);
}

#endif