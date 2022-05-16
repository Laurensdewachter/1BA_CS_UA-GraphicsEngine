#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "utils/easy_image.h"
#include "utils/ini_configuration.h"

namespace Light3D {
img::EasyImage lightedZBuffering(const ini::Configuration &configuration);
}

#endif
