#include "Figure.h"

Face::Face(std::vector<int> i) : point_indexes(std::move(i)) {}

Light::Light(const img::Color &a, const img::Color &d, const img::Color &s) : ambientLight(a), diffuseLight(d), specularLight(s) {}
char Light::getType() const {return 'L';}

char InfLight::getType() const {return 'I';}

char PointLight::getType() const {return 'P';}