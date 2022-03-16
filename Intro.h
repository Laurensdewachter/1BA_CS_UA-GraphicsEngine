#ifndef ENGINE_INTRO_H
#define ENGINE_INTRO_H

#include <cmath>

#include "utils/ini_configuration.h"
#include "utils/easy_image.h"

void quarterCircle(img::EasyImage &image, std::pair<int, int> p1, std::pair<int, int> p2, const int N,
                   img::Color color);

namespace intro {
    img::EasyImage color_rectangle(const ini::Configuration &configuration);

    img::EasyImage generate_blocks(const ini::Configuration &configuration);

    img::EasyImage generate_lines(const ini::Configuration &configuration);
}

#endif //ENGINE_INTRO_H
