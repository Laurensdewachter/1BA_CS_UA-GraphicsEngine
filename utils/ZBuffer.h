#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H

#include <vector>
#include <limits>

class ZBuffer : public std::vector<std::vector<double>> {
public:
    ZBuffer(const unsigned int width, const unsigned int height) : std::vector<std::vector<double>>(width, std::vector<double>(height, std::numeric_limits<double>::infinity())) {}
};

#endif