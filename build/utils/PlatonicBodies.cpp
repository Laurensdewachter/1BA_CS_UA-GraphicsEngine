#include "PlatonicBodies.h"

#include <cmath>

Figure *PlatonicBodies::cubeFigure = nullptr;
Figure *PlatonicBodies::tetrahedronFigure = nullptr;
Figure *PlatonicBodies::octahedronFigure = nullptr;
Figure *PlatonicBodies::icosahedronFigure = nullptr;
Figure *PlatonicBodies::dodecahedronFigure = nullptr;
Figure *PlatonicBodies::buckyBallFigure = nullptr;

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
        Face face1({0, 1, 2});
        Face face2({1, 3, 2});
        Face face3({0, 3, 1});
        Face face4({0, 2, 3});
        tetrahedronFigure->faces = {face1, face2, face3, face4};
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
        Face face1({0, 1, 5});
        Face face2({1, 2, 5});
        Face face3({2, 3, 5});
        Face face4({3, 0, 5});
        Face face5({1, 0, 4});
        Face face6({2, 1, 4});
        Face face7({3, 2, 4});
        Face face8({0, 3, 4});
        octahedronFigure->faces = {face1, face2, face3, face4, face5, face6, face7, face8};
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
                                    Vector3D::point(cos(3*M_PI/5), sin(3*M_PI/5), -0.5),
                                    Vector3D::point(cos(5*M_PI/5), sin(5*M_PI/5), -0.5),
                                    Vector3D::point(cos(7*M_PI/5), sin(7*M_PI/5), -0.5),
                                    Vector3D::point(cos(9*M_PI/5), sin(9*M_PI/5), -0.5),
                                    Vector3D::point(0, 0, -sqrt(5)/2)};

        Face face1({0, 1, 2});
        Face face2({0, 2, 3});
        Face face3({0, 3, 4});
        Face face4({0, 4, 5});
        Face face5({0, 5, 1});
        Face face6({1, 6, 2});
        Face face7({2, 6, 7});
        Face face8({2, 7, 3});
        Face face9({3, 7, 8});
        Face face10({3, 8, 4});
        Face face11({4, 8, 9});
        Face face12({4, 9, 5});
        Face face13({5, 9, 10});
        Face face14({5, 10, 1});
        Face face15({1, 10, 6});
        Face face16({11, 7, 6});
        Face face17({11, 8, 7});
        Face face18({11, 9, 8});
        Face face19({11, 10, 9});
        Face face20({11, 6, 10});

        icosahedronFigure->faces = {face1, face2, face3, face4, face5, face6, face7, face8, face9, face10, face11,
                                   face12, face13, face14, face15, face16, face17, face18, face19, face20};
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

        Face face1({0, 1, 2, 3, 4});
        Face face2({0, 5, 6, 7, 1});
        Face face3({1, 7, 8, 9, 2});
        Face face4({2, 9, 10, 11, 3});
        Face face5({3, 11, 12, 13, 4});
        Face face6({4, 13, 14, 5, 0});
        Face face7({19, 18, 17, 16, 15});
        Face face8({19, 14, 13, 12, 18});
        Face face9({18, 12, 11, 10, 17});
        Face face10({17, 10, 9, 8, 16});
        Face face11({16, 8, 7, 6, 15});
        Face face12({15, 6, 5, 14, 19});

        dodecahedronFigure->faces = {face1, face2, face3, face4, face5, face6, face7, face8, face9, face10, face11, face12};
    }
    return *dodecahedronFigure;
}

Figure PlatonicBodies::getBuckyBall() {
    if (buckyBallFigure == nullptr) {
        buckyBallFigure = new Figure;
        buckyBallFigure->points = {Vector3D::point(cos((2*M_PI)/5)/3, sin((2*M_PI)/5)/3, 0.5+(2*((sqrt(5)/2.0)-0.5)/3)),
                                   Vector3D::point(2*cos((2*M_PI)/5)/3, 2*sin((2*M_PI)/5)/3, 0.5+(((sqrt(5)/2.0)-0.5)/3)),
                                   Vector3D::point(1-(2*(1-cos((2*M_PI)/5))/3), 2*(sin((2*M_PI)/5))/3, 0.5),
                                   Vector3D::point(1-(1-cos((2*M_PI)/5))/3, (sin((2*M_PI)/5))/3, 0.5),
                                   Vector3D::point(2.0/3.0, 0, 0.5+(((sqrt(5)/2.0)-0.5)/3)),
                                   Vector3D::point(1.0/3.0, 0, 0.5+(2*((sqrt(5)/2.0)-0.5)/3)),
                                   Vector3D::point(cos((4*M_PI)/5)/3, sin((4*M_PI)/5)/3, 0.5+2*((sqrt(5)/2)-0.5)/3),
                                   Vector3D::point(2*cos((4*M_PI)/5)/3, 2*sin((4*M_PI)/5)/3, 0.5+((sqrt(5)/2)-0.5)/3),
                                   Vector3D::point(cos((2*M_PI)/5)-2*std::abs((cos((2*M_PI)/5)-cos((4*M_PI)/5))/3), sin((2*M_PI)/5)-2*std::abs((sin((2*M_PI)/5)-sin((4*M_PI)/5))/3), 0.5),
                                   Vector3D::point(cos((2*M_PI)/5)-std::abs((cos((2*M_PI)/5)-cos((4*M_PI)/5))/3), sin((2*M_PI)/5)-std::abs((sin((2*M_PI)/5)-sin((4*M_PI)/5))/3), 0.5),
                                   Vector3D::point(cos((6*M_PI)/5)/3, sin((6*M_PI)/5)/3, 0.5+(2*((sqrt(5)/2.0)-0.5)/3)),
                                   Vector3D::point(2*cos((6*M_PI)/5)/3, 2*sin((6*M_PI)/5)/3, 0.5+(((sqrt(5)/2.0)-0.5)/3)),
                                   Vector3D::point(cos((4*M_PI)/5)-2*std::abs((cos((4*M_PI)/5)-cos((6*M_PI)/5))/3), sin((4*M_PI)/5)-2*std::abs((sin((4*M_PI)/5)-sin((6*M_PI)/5))/3), 0.5),
                                   Vector3D::point(cos((4*M_PI)/5)-std::abs((cos((4*M_PI)/5)-cos((6*M_PI)/5))/3), sin((4*M_PI)/5)-std::abs((sin((4*M_PI)/5)-sin((6*M_PI)/5))/3), 0.5),
                                   Vector3D::point(cos((8*M_PI)/5)/3, sin((8*M_PI)/5)/3, 0.5+(2*((sqrt(5)/2.0)-0.5)/3)),
                                   Vector3D::point(2*cos((8*M_PI)/5)/3, 2*sin((8*M_PI)/5)/3, 0.5+(((sqrt(5)/2.0)-0.5)/3)),
                                   Vector3D::point(cos((6*M_PI)/5)+2*std::abs((cos((6*M_PI)/5)-cos((8*M_PI)/5))/3), sin((6*M_PI)/5)-2*std::abs((sin((6*M_PI)/5)-sin((8*M_PI)/5))/3), 0.5),
                                   Vector3D::point(cos((6*M_PI)/5)+std::abs((cos((6*M_PI)/5)-cos((8*M_PI)/5))/3), sin((6*M_PI)/5)-std::abs((sin((6*M_PI)/5)-sin((8*M_PI)/5))/3), 0.5),
                                   Vector3D::point(1-(1-cos((8*M_PI)/5))/3, sin((8*M_PI)/5)/3, 0.5),
                                   Vector3D::point(1-2*(1-cos((8*M_PI)/5))/3, 2*sin((8*M_PI)/5)/3, 0.5),
                                   Vector3D::point(1-(1-cos(M_PI/5))/3, sin(M_PI/5)/3, 0.5-(1.0/3.0)),
                                   Vector3D::point(1-2*(1-cos(M_PI/5))/3, 2*sin(M_PI/5)/3, 0.5-(2.0/3.0)),
                                   Vector3D::point(cos(M_PI/5)-(cos(M_PI/5)-cos((2*M_PI)/5))/3, sin((2*M_PI)/5)-2*(sin((2*M_PI)/5)-sin(M_PI/5))/3, 0.5-(2.0/3.0)),
                                   Vector3D::point(cos(M_PI/5)-2*(cos(M_PI/5)-cos((2*M_PI)/5))/3, sin((2*M_PI)/5)-(sin((2*M_PI)/5)-sin(M_PI/5))/3, 0.5-(1.0/3.0)),
                                   Vector3D::point(cos(M_PI/5)-std::abs((cos(M_PI/5)-cos(3*M_PI/5))/3), sin(M_PI/5)+(sin(3*M_PI/5)-sin(M_PI/5))/3, -0.5),
                                   Vector3D::point(cos(M_PI/5)-2*std::abs((cos(M_PI/5)-cos(3*M_PI/5))/3), sin(M_PI/5)+2*(sin(3*M_PI/5)-sin(M_PI/5))/3, -0.5),
                                   Vector3D::point(cos(3*M_PI/5)+std::abs((cos(2*M_PI/5)-cos(3*M_PI/5))/3), sin(3*M_PI/5), 0.5-(2.0/3.0)),
                                   Vector3D::point(cos(3*M_PI/5)+2*std::abs((cos(2*M_PI/5)-cos(3*M_PI/5))/3), sin(3*M_PI/5), 0.5-(1.0/3.0)),
                                   Vector3D::point(cos(3*M_PI/5)-std::abs((cos(4*M_PI/5)-cos(3*M_PI/5))/3), sin(4*M_PI/5)+2*std::abs((sin(3*M_PI/5)-sin(4*M_PI/5))/3), 0.5-(2.0/3.0)),
                                   Vector3D::point(cos(3*M_PI/5)-2*std::abs((cos(4*M_PI/5)-cos(3*M_PI/5))/3), sin(4*M_PI/5)+std::abs((sin(3*M_PI/5)-sin(4*M_PI/5))/3), 0.5-(1.0/3.0)),
                                   Vector3D::point(cos(4*M_PI/5)-std::abs((cos(4*M_PI/5)+1)/3),2*sin(4*M_PI/5)/3, 0.5-(1.0/3.0)),
                                   Vector3D::point(cos(4*M_PI/5)-2*std::abs((cos(4*M_PI/5)+1)/3),sin(4*M_PI/5)/3, 0.5-(2.0/3.0)),
                                   Vector3D::point(-1+std::abs((cos(3*M_PI/5)+1)/3), sin(3*M_PI/5)/3, -0.5),
                                   Vector3D::point(-1+2*std::abs((cos(3*M_PI/5)+1)/3), 2*sin(3*M_PI/5)/3, -0.5),
                                   Vector3D::point(-1+std::abs((cos(6*M_PI/5)+1)/3),sin(6*M_PI/5)/3, 0.5-(2.0/3.0)),
                                   Vector3D::point(-1+2*std::abs((cos(6*M_PI/5)+1)/3),2*sin(6*M_PI/5)/3, 0.5-(1.0/3.0)),
                                   Vector3D::point(cos(6*M_PI/5)+std::abs((cos(6*M_PI/5)-cos(7*M_PI/5))/3), sin(7*M_PI/5)+2*std::abs((sin(7*M_PI/5)-sin(6*M_PI/5))/3), 0.5-(1.0/3.0)),
                                   Vector3D::point(cos(6*M_PI/5)+2*std::abs((cos(6*M_PI/5)-cos(7*M_PI/5))/3), sin(7*M_PI/5)+std::abs((sin(7*M_PI/5)-sin(6*M_PI/5))/3), 0.5-(2.0/3.0)),
                                   Vector3D::point(-1+2*std::abs((-1-cos(7*M_PI/5))/3), 2*sin(7*M_PI/5)/3, -0.5),
                                   Vector3D::point(-1+std::abs((-1-cos(7*M_PI/5))/3), sin(7*M_PI/5)/3, -0.5),
                                   Vector3D::point(cos(8*M_PI/5)-2*std::abs((cos(7*M_PI/5)-cos(8*M_PI/5))/3), sin(7*M_PI/5), 0.5-(2.0/3.0)),
                                   Vector3D::point(cos(8*M_PI/5)-std::abs((cos(7*M_PI/5)-cos(8*M_PI/5))/3), sin(7*M_PI/5), 0.5-(1.0/3.0)),
                                   Vector3D::point(cos(8*M_PI/5)+std::abs((cos(9*M_PI/5)-cos(8*M_PI/5))/3), sin(8*M_PI/5)+std::abs((sin(9*M_PI/5)-sin(8*M_PI/5))/3), 0.5-(1.0/3.0)),
                                   Vector3D::point(cos(8*M_PI/5)+2*std::abs((cos(9*M_PI/5)-cos(8*M_PI/5))/3), sin(8*M_PI/5)+2*std::abs((sin(9*M_PI/5)-sin(8*M_PI/5))/3), 0.5-(2.0/3.0)),
                                   Vector3D::point(cos(9*M_PI/5)-std::abs((cos(7*M_PI/5)-cos(9*M_PI/5))/3), sin(9*M_PI/5)-std::abs((sin(9*M_PI/5)-sin(7*M_PI/5))/3), -0.5),
                                   Vector3D::point(cos(9*M_PI/5)-2*std::abs((cos(7*M_PI/5)-cos(9*M_PI/5))/3), sin(9*M_PI/5)-2*std::abs((sin(9*M_PI/5)-sin(7*M_PI/5))/3), -0.5),
                                   Vector3D::point(1-2*(1-cos(9*M_PI/5))/3, 2*sin(9*M_PI/5)/3, 0.5-(2.0/3.0)),
                                   Vector3D::point(1-(1-cos(9*M_PI/5))/3, sin(9*M_PI/5)/3, 0.5-(1.0/3.0)),
                                   Vector3D::point(cos(M_PI/5), sin(9*M_PI/5)+2*sin(M_PI/5)/3, -0.5),
                                   Vector3D::point(cos(M_PI/5), sin(9*M_PI/5)+4*sin(M_PI/5)/3, -0.5),
                                   Vector3D::point(2*cos(M_PI/5)/3, 2*sin(M_PI/5)/3, -0.5-((sqrt(5)/2)-(1.0/2.0))/3),
                                   Vector3D::point(cos(M_PI/5)/3, sin(M_PI/5)/3, -0.5-2*((sqrt(5)/2)-(1.0/2.0))/3),
                                   Vector3D::point(2*cos(3*M_PI/5)/3, 2*sin(3*M_PI/5)/3, -0.5-((sqrt(5)/2)-(1.0/2.0))/3),
                                   Vector3D::point(cos(3*M_PI/5)/3, sin(3*M_PI/5)/3, -0.5-2*((sqrt(5)/2)-(1.0/2.0))/3),
                                   Vector3D::point(-2.0/3, 0, -0.5-((sqrt(5)/2)-(1.0/2.0))/3),
                                   Vector3D::point(-1.0/3, 0, -0.5-2*((sqrt(5)/2)-(1.0/2.0))/3),
                                   Vector3D::point(2*cos(7*M_PI/5)/3, 2*sin(7*M_PI/5)/3, -0.5-((sqrt(5)/2)-(1.0/2.0))/3),
                                   Vector3D::point(cos(7*M_PI/5)/3, sin(7*M_PI/5)/3, -0.5-2*((sqrt(5)/2)-(1.0/2.0))/3),
                                   Vector3D::point(2*cos(9*M_PI/5)/3, 2*sin(9*M_PI/5)/3, -0.5-((sqrt(5)/2)-(1.0/2.0))/3),
                                   Vector3D::point(cos(9*M_PI/5)/3, sin(9*M_PI/5)/3, -0.5-2*((sqrt(5)/2)-(1.0/2.0))/3)
                                   };

        Face face1({5, 4, 3, 2, 1, 0});
        Face face2({0, 1, 9, 8, 7, 6});
        Face face3({6, 7, 13, 12, 11, 10});
        Face face4({10, 11, 17, 16, 15, 14});
        Face face5({14, 15, 19, 18, 4, 5});
        Face face6({10, 14, 5, 0, 6});
        Face face7({2, 3, 20, 21, 22, 23});
        Face face8({23, 22, 24, 25, 26, 27});
        Face face9({1, 2, 23, 27, 9});
        Face face10({8, 9, 27, 26, 28, 29});
        Face face11({7, 8, 29, 30, 13});
        Face face12({29, 28, 33, 32, 31, 30});
        Face face13({12, 13, 30, 31, 34, 35});
        Face face14({11, 12, 35, 36, 17});
        Face face15({35, 34, 39, 38, 37, 36});
        Face face16({16, 17, 36, 37, 40, 41});
        Face face17({15, 16, 41, 42, 19});
        Face face18({41, 40, 45, 44, 43, 42});
        Face face19({18, 19, 42, 43, 46, 47});
        Face face20({3, 4, 18, 47, 20});
        Face face21({47, 46, 48, 49, 21, 20});
        Face face22({22, 21, 49, 50, 24});
        Face face23({25, 24, 50, 51, 53, 52});
        Face face24({28, 26, 25, 52, 33});
        Face face25({32, 33, 52, 53, 55, 54});
        Face face26({34, 31, 32, 54, 39});
        Face face27({38, 39, 54, 55, 57, 56});
        Face face28({40, 37, 38, 56, 45});
        Face face29({44, 45, 56, 57, 59, 58});
        Face face30({49, 48, 58, 59, 51, 50});
        Face face31({51, 53, 55, 57, 59});
        Face face32({46, 43, 44, 58, 48});

        buckyBallFigure->faces = {face1, face2, face3, face4, face5, face6, face7, face8, face9, face10, face11,
                                  face12, face13, face14, face15, face16, face17, face18, face19, face20, face21,
                                  face22, face23, face24, face25, face26, face27, face28, face29, face30, face31, face32, face32};
    }
    return *buckyBallFigure;
}
