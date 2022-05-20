#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include <iostream>
#include <list>
#include <vector>
#include "vector3d.h"
#include "easy_image.h"

struct CustomColor {
    double red;
    double green;
    double blue;

    CustomColor() = default;
    CustomColor(const CustomColor& c);
    CustomColor(double r, double g, double b);
};

struct Face {
    std::vector<int> point_indexes;
    Face() = default;
    explicit Face(std::vector<int> i);
};

struct Figure {
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    CustomColor ambientReflection;
    CustomColor diffuseReflection;
    CustomColor specularReflection;
    double reflectionCoefficient;
};

using Figures3D = std::list<Figure>;

struct Light {
    CustomColor ambientLight;
    CustomColor diffuseLight;
    CustomColor specularLight;

    Light() = default;
    Light(const CustomColor &a, const CustomColor &d, const CustomColor &s);

    virtual char getType() const;
};

struct InfLight : public Light {
    Vector3D ldVector;

    char getType() const override;
};

struct PointLight : public Light {
    Vector3D location;
    double spotAngle;

    char getType() const override;
};

using Lights3D = std::list<Light*>;

#endif
