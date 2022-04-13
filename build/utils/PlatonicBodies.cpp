#include "PlatonicBodies.h"

#include <cmath>

Figure *PlatonicBodies::cubeFigure = nullptr;
Figure *PlatonicBodies::tetrahedronFigure = nullptr;
Figure *PlatonicBodies::octahedronFigure = nullptr;
Figure *PlatonicBodies::icosahedronFigure = nullptr;
Figure *PlatonicBodies::dodecahedronFigure = nullptr;

PlatonicBodies::PlatonicBodies() {}

Figure PlatonicBodies::getCubeFigure() {
    if (cubeFigure == nullptr) {
        cubeFigure = new Figure;
        cubeFigure->points = {Vector3D::point(1, -1, -1),
                             Vector3D::point(-1, 1, -1),
                             Vector3D::point(1, 1, 1),
                             Vector3D::point(-1, -1, 1),
                             Vector3D::point(1, 1, -1),
                             Vector3D::point(-1, -1, -1),
                             Vector3D::point(1, -1, 1),
                             Vector3D::point(-1, 1, 1)};
        Face face1({0, 4, 2, 6});
        Face face2({4, 1, 7, 2});
        Face face3({1, 5, 3, 7});
        Face face4({5, 0, 6, 3});
        Face face5({6, 2, 7, 3});
        Face face6({0, 5, 1, 4});
        cubeFigure->faces = {face1, face2, face3, face4, face5, face6};
    }
    return *cubeFigure;
}

Figure PlatonicBodies::getTetrahedronFigure() {
    if (tetrahedronFigure == nullptr){
        tetrahedronFigure = new Figure;
        tetrahedronFigure->points = {Vector3D::point(1, -1, -1),
                                    Vector3D::point(-1, 1, -1),
                                    Vector3D::point(1, 1, 1),
                                    Vector3D::point(-1, -1, 1)};
        Face face7({0, 1, 2});
        Face face8({1, 3, 2});
        Face face9({0, 3, 1});
        Face face10({0, 2, 3});
        tetrahedronFigure->faces = {face7, face8, face9, face10};
    }
    return *tetrahedronFigure;
}

Figure PlatonicBodies::getOctahedronFigure() {
    if (octahedronFigure == nullptr) {
        octahedronFigure = new Figure;
        octahedronFigure->points = {Vector3D::point(1, 0, 0),
                                   Vector3D::point(0, 1, 0),
                                   Vector3D::point(-1, 0, 0),
                                   Vector3D::point(0, -1, 0),
                                   Vector3D::point(0, 0, -1),
                                   Vector3D::point(0, 0, 1)};
        Face face11({0, 1, 5});
        Face face12({1, 2, 5});
        Face face13({2, 3, 5});
        Face face14({3, 0, 5});
        Face face15({1, 0, 4});
        Face face16({2, 1, 4});
        Face face17({3, 2, 4});
        Face face18({0, 3, 4});
        octahedronFigure->faces = {face11, face12, face13, face14, face15, face16, face17, face18};
    }
    return *octahedronFigure;
}

Figure PlatonicBodies::getIcosahedronFigure() {
    if (icosahedronFigure == nullptr) {
        icosahedronFigure = new Figure;
        icosahedronFigure->points = {Vector3D::point(0, 0, sqrt(5)/2),
                                    Vector3D::point(1, 0, 0.5),
                                    Vector3D::point(cos((2*M_PI)/5), sin((2*M_PI)/5), 0.5),
                                    Vector3D::point(cos((4*M_PI)/5), sin((4*M_PI)/5), 0.5),
                                    Vector3D::point(cos((6*M_PI)/5), sin((6*M_PI)/5), 0.5),
                                    Vector3D::point(cos((8*M_PI)/5), sin((8*M_PI)/5), 0.5),
                                    Vector3D::point(cos(M_PI/5), sin(M_PI/5), -0.5),
                                    Vector3D::point(cos((M_PI/5)+((2*M_PI)/5)), sin((M_PI/5)+((2*M_PI)/5)), -0.5),
                                    Vector3D::point(cos((M_PI/5)+((4*M_PI)/5)), sin((M_PI/5)+((4*M_PI)/5)), -0.5),
                                    Vector3D::point(cos((M_PI/5)+((6*M_PI)/5)), sin((M_PI/5)+((6*M_PI)/5)), -0.5),
                                    Vector3D::point(cos((M_PI/5)+((8*M_PI)/5)), sin((M_PI/5)+((8*M_PI)/5)), -0.5),
                                    Vector3D::point(0, 0, -sqrt(5)/2)};

        Face face19({0, 1, 2});
        Face face20({0, 2, 3});
        Face face21({0, 3, 4});
        Face face22({0, 4, 5});
        Face face23({0, 5, 1});
        Face face24({1, 6, 2});
        Face face25({2, 6, 7});
        Face face26({2, 7, 3});
        Face face27({3, 7, 8});
        Face face28({3, 8, 4});
        Face face29({4, 8, 9});
        Face face30({4, 9, 5});
        Face face31({5, 9, 10});
        Face face32({5, 10, 1});
        Face face33({1, 10, 6});
        Face face34({11, 7, 6});
        Face face35({11, 8, 7});
        Face face36({11, 9, 8});
        Face face37({11, 10, 9});
        Face face38({11, 6, 10});

        icosahedronFigure->faces = {face19, face20, face21, face22, face23, face24, face25, face26, face27, face28, face29,
                                   face30, face31, face32, face33, face34, face35, face36, face37, face38};
    }
    return *icosahedronFigure;
}

Figure PlatonicBodies::getDodecahedronFigure() {
    if (dodecahedronFigure == nullptr) {
        dodecahedronFigure = new Figure;
        dodecahedronFigure->points = {Vector3D::point((1+cos((2*M_PI)/5))/3, sin((2*M_PI)/5)/3, (1+(sqrt(5)/2))/3),
                                     Vector3D::point((cos((2*M_PI)/5)+cos((4*M_PI)/5))/3, (sin((2*M_PI)/5)+sin((4*M_PI)/5))/3, (1+(sqrt(5)/2))/3),
                                     Vector3D::point((cos((4*M_PI)/5)+cos((6*M_PI)/5))/3, (sin((4*M_PI)/5)+sin((6*M_PI)/5))/3, (1+(sqrt(5)/2))/3),
                                     Vector3D::point((cos((6*M_PI)/5)+cos((8*M_PI)/5))/3, (sin((6*M_PI)/5)+sin((8*M_PI)/5))/3, (1+(sqrt(5)/2))/3),
                                     Vector3D::point((1+cos((8*M_PI)/5))/3, (sin((8*M_PI)/5))/3, (1+(sqrt(5)/2))/3),
                                     Vector3D::point((1+cos((2*M_PI)/5)+cos(M_PI/5))/3, (sin((2*M_PI)/5)+sin(M_PI/5))/3, (0.5)/3),
                                     Vector3D::point((cos((2*M_PI)/5)+cos(M_PI/5)+cos((M_PI/5)+((2*M_PI)/5)))/3, (sin((2*M_PI)/5)+sin(M_PI/5)+sin((M_PI/5)+((2*M_PI)/5)))/3, (-0.5)/3),
                                     Vector3D::point((cos((2*M_PI)/5)+cos((4*M_PI)/5)+cos((M_PI/5)+((2*M_PI)/5)))/3, (sin((2*M_PI)/5)+sin((4*M_PI)/5)+sin((M_PI/5)+((2*M_PI)/5)))/3, (0.5)/3),
                                     Vector3D::point((cos((4*M_PI)/5)+cos((M_PI/5)+((2*M_PI)/5))+cos((M_PI/5)+((4*M_PI)/5)))/3, (sin((4*M_PI)/5)+sin((M_PI/5)+((2*M_PI)/5))+sin((M_PI/5)+((4*M_PI)/5)))/3, (-0.5)/3),
                                     Vector3D::point((cos((4*M_PI)/5)+cos((6*M_PI)/5)+cos((M_PI/5)+((4*M_PI)/5)))/3, (sin((4*M_PI)/5)+sin((6*M_PI)/5)+sin((M_PI/5)+((4*M_PI)/5)))/3, (0.5)/3),
                                     Vector3D::point((cos((6*M_PI)/5)+cos((M_PI/5)+((4*M_PI)/5))+cos((M_PI/5)+((6*M_PI)/5)))/3, (sin((6*M_PI)/5)+sin((M_PI/5)+((4*M_PI)/5))+sin((M_PI/5)+((6*M_PI)/5)))/3, (-0.5)/3),
                                     Vector3D::point((cos((6*M_PI)/5)+cos((8*M_PI)/5)+cos((M_PI/5)+((6*M_PI)/5)))/3, (sin((6*M_PI)/5)+sin((8*M_PI)/5)+sin((M_PI/5)+((6*M_PI)/5)))/3, (0.5)/3),
                                     Vector3D::point((cos((8*M_PI)/5)+cos((M_PI/5)+((6*M_PI)/5))+cos((M_PI/5)+((8*M_PI)/5)))/3, (sin((8*M_PI)/5)+sin((M_PI/5)+((6*M_PI)/5))+sin((M_PI/5)+((8*M_PI)/5)))/3, (-0.5)/3),
                                     Vector3D::point((1+cos((8*M_PI)/5)+cos((M_PI/5)+((8*M_PI)/5)))/3, (sin((8*M_PI)/5)+sin((M_PI/5)+((8*M_PI)/5)))/3, (0.5)/3),
                                     Vector3D::point((1+cos(M_PI/5)+cos((M_PI/5)+((8*M_PI)/5)))/3, (sin(M_PI/5)+sin((M_PI/5)+((8*M_PI)/5)))/3, (-0.5)/3),
                                     Vector3D::point((cos(M_PI/5)+cos((M_PI/5)+((2*M_PI)/5)))/3, (sin(M_PI/5)+sin((M_PI/5)+((2*M_PI)/5)))/3, ((-sqrt(5)/2)-1)/3),
                                     Vector3D::point((cos((M_PI/5)+((2*M_PI)/5))+cos((M_PI/5)+((4*M_PI)/5)))/3, (sin((M_PI/5)+((2*M_PI)/5))+sin((M_PI/5)+((4*M_PI)/5)))/3, ((-sqrt(5)/2)-1)/3),
                                     Vector3D::point((cos((M_PI/5)+((4*M_PI)/5))+cos((M_PI/5)+((6*M_PI)/5)))/3, (sin((M_PI/5)+((4*M_PI)/5))+sin((M_PI/5)+((6*M_PI)/5)))/3, ((-sqrt(5)/2)-1)/3),
                                     Vector3D::point((cos((M_PI/5)+((6*M_PI)/5))+cos((M_PI/5)+((8*M_PI)/5)))/3, (sin((M_PI/5)+((6*M_PI)/5))+sin((M_PI/5)+((8*M_PI)/5)))/3, ((-sqrt(5)/2)-1)/3),
                                     Vector3D::point((cos(M_PI/5)+cos((M_PI/5)+((8*M_PI)/5)))/3, (sin(M_PI/5)+sin((M_PI/5)+((8*M_PI)/5)))/3, ((-sqrt(5)/2)-1)/3)};

        Face face39({0, 1, 2, 3, 4});
        Face face40({0, 5, 6, 7, 1});
        Face face41({1, 7, 8, 9, 2});
        Face face42({2, 9, 10, 11, 3});
        Face face43({3, 11, 12, 13, 4});
        Face face44({4, 13, 14, 5, 0});
        Face face45({19, 18, 17, 16, 15});
        Face face46({19, 14, 13, 12, 18});
        Face face47({18, 12, 11, 10, 17});
        Face face48({17, 10, 9, 8, 16});
        Face face49({16, 8, 7, 6, 15});
        Face face50({15, 6, 5, 14, 19});

        dodecahedronFigure->faces = {face39, face40, face41, face42, face43, face44, face45, face46, face47, face48, face49, face50};
    }
    return *dodecahedronFigure;
}
