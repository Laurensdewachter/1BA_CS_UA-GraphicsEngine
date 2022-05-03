#ifndef ENGINE_3DTRIANGLES_H
#define ENGINE_3DTRIANGLES_H

#include "utils/easy_image.h"
#include "utils/ini_configuration.h"

namespace Triangles3D {
    img::EasyImage zBuffer(const ini::Configuration &configuration);
}

#endif
