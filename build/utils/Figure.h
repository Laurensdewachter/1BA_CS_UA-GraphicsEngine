#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include <iostream>
#include <list>
#include <vector>
#include "vector3d.h"
#include "easy_image.h"

struct Face {
    std::vector<int> point_indexes;
    Face() = default;
    explicit Face(std::vector<int> i);
};

struct Figure {
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    img::Color ambientReflection;
    img::Color diffuseReflection;
    img::Color specularReflection;
    double reflectionCoefficient;
};

using Figures3D = std::list<Figure>;

struct Light {
    img::Color ambientLight;
    img::Color diffuseLight;
    img::Color specularLight;

    Light() = default;
    Light(const img::Color &a, const img::Color &d, const img::Color &s);

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
