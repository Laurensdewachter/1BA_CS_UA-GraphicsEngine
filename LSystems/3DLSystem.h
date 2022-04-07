#ifndef ENGINE_3DLSYSTEM_H
#define ENGINE_3DLSYSTEM_H

#include "../Figure.h"
#include "../utils/ini_configuration.h"
#include "../utils/vector3d.h"

namespace LSystem3D {
    Figure LSystem3D(const ini::Configuration &configuration, const std::string &figureName, Matrix &V);
}

#endif
