#ifndef ENGINE_2DLSYSTEM_H
#define ENGINE_2DLSYSTEM_H

#include <fstream>
#include <cmath>
#include <stack>
#include <random>

#include "utils/ini_configuration.h"
#include "utils/easy_image.h"
#include "utils/l_parser.h"
#include "CoordToPixel.h"

namespace LSystem2D {
    img::EasyImage LSystem2D(const ini::Configuration &configuration);
}

#endif
