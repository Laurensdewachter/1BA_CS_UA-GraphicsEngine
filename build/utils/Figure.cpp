#include "Figure.h"

CustomColor::CustomColor(double r, double g, double b) : red(r), green(g), blue(b) {}
CustomColor::CustomColor(const CustomColor &c) {
    red = c.red;
    green = c.green;
    blue = c.blue;
}

Face::Face(std::vector<int> i) : point_indexes(std::move(i)) {}

Light::Light(const CustomColor &a, const CustomColor &d, const CustomColor &s) : ambientLight(a), diffuseLight(d), specularLight(s) {}
char Light::getType() const {return 'L';}

char InfLight::getType() const {return 'I';}

char PointLight::getType() const {return 'P';}