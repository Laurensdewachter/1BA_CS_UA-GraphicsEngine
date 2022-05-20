#include "3DLines.h"
#include "utils/Transformation.h"
#include "utils/Utils.h"
#include "LSystems/3DLSystem.h"

Point2D doProjection(const Vector3D &point, double d) {
    return Point2D{(d*point.x)/(-point.z), (d*point.y)/(-point.z)};
}

Lines2D doProjection(const Figures3D &figs) {
    Lines2D lines;
    for (auto curFigure : figs) {
        for (auto curFace : curFigure.faces) {
            for (unsigned int k = 0; k < curFace.point_indexes.size(); k++) {
                Line2D line;
                if (k == curFace.point_indexes.size() - 1) {
                    line.p1 = doProjection(curFigure.points[curFace.point_indexes[k]], 1);
                    line.p2 = doProjection(curFigure.points[curFace.point_indexes[0]], 1);

                    line.z1 = curFigure.points[curFace.point_indexes[k]].z;
                    line.z2 = curFigure.points[curFace.point_indexes[0]].z;
                } else {
                    line.p1 = doProjection(curFigure.points[curFace.point_indexes[k]], 1);
                    line.p2 = doProjection(curFigure.points[curFace.point_indexes[k + 1]], 1);

                    line.z1 = curFigure.points[curFace.point_indexes[k]].z;
                    line.z2 = curFigure.points[curFace.point_indexes[k + 1]].z;
                }
                line.color = curFigure.ambientReflection;
                lines.push_back(line);
            }
        }
    }
    return lines;
}

Lines2D doProjectionConst(const Figures3D &figs) {
    Lines2D lines;
    for (auto i : figs) {
        for (auto j : i.faces) {
            for (unsigned int k = 0; k < j.point_indexes.size(); k++) {
                Line2D line;
                if (k == j.point_indexes.size()-1) {
                    line.p1 = doProjection(i.points[j.point_indexes[k]], 1);
                    line.p2 = doProjection(i.points[j.point_indexes[0]], 1);

                    line.z1 = i.points[j.point_indexes[k]].z;
                    line.z2 = i.points[j.point_indexes[0]].z;
                } else {
                    line.p1 = doProjection(i.points[j.point_indexes[k]], 1);
                    line.p2 = doProjection(i.points[j.point_indexes[k+1]], 1);

                    line.z1 = i.points[j.point_indexes[k]].z;
                    line.z2 = i.points[j.point_indexes[k+1]].z;
                }
                line.color = i.ambientReflection;
                lines.push_back(line);
            }
        }
    }
    return lines;
}

Figure eyeFigure(const ini::Configuration &configuration, std::string &figureName, Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();
    const unsigned int nrPoints = configuration[figureName]["nrPoints"].as_int_or_die();
    const unsigned int nrLines = configuration[figureName]["nrLines"].as_int_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig;
    
    fig.ambientReflection = CustomColor(color[0], color[1], color[2]);

    for (unsigned int j = 0; j < nrPoints; j++) {
        std::string pointName = "point" + std::to_string(j);

        std::vector<double> point_vec = configuration[figureName][pointName].as_double_tuple_or_die();
        fig.points.push_back(Vector3D::point(point_vec[0], point_vec[1], point_vec[2]));
    }

    for (unsigned int j = 0; j < nrLines; j++) {
        std::string lineName = "line" + std::to_string(j);

        std::vector<int> line_vec = configuration[figureName][lineName].as_int_tuple_or_die();
        Face f(line_vec);
        fig.faces.push_back(f);
    }

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figure createCube(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getCubeFigure();

    fig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
    fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
    fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
    fig.reflectionCoefficient = reflectionCoefficient;

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figures3D createFractalCube(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);
    const unsigned int nrIterations = configuration[figureName]["nrIterations"].as_int_or_die();
    const double fractalScale = configuration[figureName]["fractalScale"].as_double_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getCubeFigure();

    Figures3D fractalFigs;
    if (nrIterations > 0) fractalFigs = Utils::generateFractal(fig, nrIterations, fractalScale);
    else fractalFigs.push_back(fig);

    for (auto &curFig : fractalFigs) {
        curFig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
        fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
        fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
        fig.reflectionCoefficient = reflectionCoefficient;
        Transformation::applyTransformation(curFig, F);
    }

    return fractalFigs;
}

Figure createTetrahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getTetrahedronFigure();

    fig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
    fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
    fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
    fig.reflectionCoefficient = reflectionCoefficient;

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figures3D createFractalTetrahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);
    const unsigned int nrIterations = configuration[figureName]["nrIterations"].as_int_or_die();
    const double fractalScale = configuration[figureName]["fractalScale"].as_double_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getTetrahedronFigure();

    Figures3D fractalFigs;
    if (nrIterations > 0) fractalFigs = Utils::generateFractal(fig, nrIterations, fractalScale);
    else fractalFigs.push_back(fig);

    for (auto &curFig : fractalFigs) {
        curFig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
        fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
        fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
        fig.reflectionCoefficient = reflectionCoefficient;
        Transformation::applyTransformation(curFig, F);
    }

    return fractalFigs;
}

Figure createOctahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getOctahedronFigure();

    fig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
    fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
    fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
    fig.reflectionCoefficient = reflectionCoefficient;

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figures3D createFractalOctahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);
    const unsigned int nrIterations = configuration[figureName]["nrIterations"].as_int_or_die();
    const double fractalScale = configuration[figureName]["fractalScale"].as_double_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getOctahedronFigure();

    Figures3D fractalFigs;
    if (nrIterations > 0) fractalFigs = Utils::generateFractal(fig, nrIterations, fractalScale);
    else fractalFigs.push_back(fig);

    for (auto &curFig : fractalFigs) {
        curFig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
        fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
        fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
        fig.reflectionCoefficient = reflectionCoefficient;
        Transformation::applyTransformation(curFig, F);
    }

    return fractalFigs;
}

Figure createIcosahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getIcosahedronFigure();

    fig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
    fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
    fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
    fig.reflectionCoefficient = reflectionCoefficient;

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figures3D createFractalIcosahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);
    const unsigned int nrIterations = configuration[figureName]["nrIterations"].as_int_or_die();
    const double fractalScale = configuration[figureName]["fractalScale"].as_double_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getIcosahedronFigure();

    Figures3D fractalFigs;
    if (nrIterations > 0) fractalFigs = Utils::generateFractal(fig, nrIterations, fractalScale);
    else fractalFigs.push_back(fig);

    for (auto &curFig : fractalFigs) {
        curFig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
        fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
        fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
        fig.reflectionCoefficient = reflectionCoefficient;
        Transformation::applyTransformation(curFig, F);
    }

    return fractalFigs;
}

Figure createDodecahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getDodecahedronFigure();

    fig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
    fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
    fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
    fig.reflectionCoefficient = reflectionCoefficient;

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figures3D createFractalDodecahedron(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);
    const unsigned int nrIterations = configuration[figureName]["nrIterations"].as_int_or_die();
    const double fractalScale = configuration[figureName]["fractalScale"].as_double_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getDodecahedronFigure();

    Figures3D fractalFigs;
    if (nrIterations > 0) fractalFigs = Utils::generateFractal(fig, nrIterations, fractalScale);
    else fractalFigs.push_back(fig);

    for (auto &curFig : fractalFigs) {
        curFig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
        fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
        fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
        fig.reflectionCoefficient = reflectionCoefficient;
        Transformation::applyTransformation(curFig, F);
    }

    return fractalFigs;
}

Figure createSphere(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);
    const unsigned int n = configuration[figureName]["n"].as_int_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getIcosahedronFigure();

    fig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
    fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
    fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
    fig.reflectionCoefficient = reflectionCoefficient;

    for (unsigned int i = 0; i < n; i++) {
        Utils::splitTriangles(fig);
    }

    for (auto & point : fig.points) point.normalise();

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figure createCone(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);
    const int n = configuration[figureName]["n"].as_int_or_die();
    const double height = configuration[figureName]["height"].as_double_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig;

    fig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
    fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
    fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
    fig.reflectionCoefficient = reflectionCoefficient;

    for (int i = 0; i < n; i++) {
        fig.points.push_back(Vector3D::point(cos((2*M_PI*i)/n), sin((2*M_PI*i)/n), 0));
    }
    fig.points.push_back(Vector3D::point(0, 0, height));

    Face ground;
    for (int i = 0; i < n; i++) {
        Face face({i, (i+1)%n, n});
        fig.faces.push_back(face);

        ground.point_indexes.push_back(n-i-1);
    }
    fig.faces.push_back(ground);

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figure createCylinder(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);
    const int n = configuration[figureName]["n"].as_int_or_die();
    const double height = configuration[figureName]["height"].as_double_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig;

    fig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
    fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
    fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
    fig.reflectionCoefficient = reflectionCoefficient;

    for (int i = 0; i < n; i++) {
        fig.points.push_back(Vector3D::point(cos((2*M_PI*i)/n), sin((2*M_PI*i)/n), 0));
    }
    for (int i = 0; i < n; i++) {
        fig.points.push_back(Vector3D::point(cos((2*M_PI*i)/n), sin((2*M_PI*i)/n), height));
    }

    for (int i = 0; i < n-1; i++) {
        Face face({i, (i+1)%n, (i+n+1)%(2*n), n+i});
        fig.faces.push_back(face);
    }
    Face lastSquare({n-1, 0, n, (2*n)-1});
    fig.faces.push_back(lastSquare);

    Face ground;
    Face roof;
    for (int i = 0; i <= n-1; i++) ground.point_indexes.push_back(i);
    for (int i = n; i <= (2*n)-1; i++) roof.point_indexes.push_back(i);
    fig.faces.push_back(ground);
    fig.faces.push_back(roof);

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figure createTorus(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);
    const int n = configuration[figureName]["n"].as_int_or_die();
    const int m = configuration[figureName]["m"].as_int_or_die();
    const double R = configuration[figureName]["R"].as_double_or_die();
    const double r = configuration[figureName]["r"].as_double_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig;

    fig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
    fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
    fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
    fig.reflectionCoefficient = reflectionCoefficient;

    std::vector<std::vector<int>> pointTracker(n, std::vector<int>(m, 0));
    int loopCounter = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fig.points.push_back(Vector3D::point(cos((2*M_PI*i)/n)*(R+ cos((2*M_PI*j)/n)),
                                                 sin((2*M_PI*i)/n)*(R+ cos((2*M_PI*j)/n)),
                                                 r* sin((2*M_PI*j)/n)));
            pointTracker[i][j] = loopCounter;
            loopCounter++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Face face({pointTracker[i][j], pointTracker[(i+1)%n][j], pointTracker[(i+1)%n][(j+1)%m], pointTracker[i][(j+1)%m]});
            fig.faces.push_back(face);
        }
    }

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figure createBuckyBall(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getBuckyBall();

    fig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
    fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
    fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
    fig.reflectionCoefficient = reflectionCoefficient;

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figures3D createFractalBuckyBall(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);
    const unsigned int nrIterations = configuration[figureName]["nrIterations"].as_int_or_die();
    const double fractalScale = configuration[figureName]["fractalScale"].as_double_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getBuckyBall();

    Figures3D fractalFigs;
    if (nrIterations > 0) fractalFigs = Utils::generateFractal(fig, nrIterations, fractalScale);
    else fractalFigs.push_back(fig);

    for (auto &curFig : fractalFigs) {
        curFig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
        fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
        fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
        fig.reflectionCoefficient = reflectionCoefficient;
        Transformation::applyTransformation(curFig, F);
    }

    return fractalFigs;
}

Figures3D createMengerSponge(const ini::Configuration &configuration, std::string &figureName, Matrix &V, bool light) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> ambientReflection;
    if (light) {
        ambientReflection = configuration[figureName]["ambientReflection"].as_double_tuple_or_die();
    }
    else ambientReflection = configuration[figureName]["color"].as_double_tuple_or_die();
    std::vector<double> diffuseReflection = configuration[figureName]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0});
    std::vector<double> specularReflection = configuration[figureName]["specularReflection"].as_double_tuple_or_default({0, 0, 0});
    const double reflectionCoefficient = configuration[figureName]["reflectionCoefficient"].as_double_or_default(0);
    unsigned int nrIterations = configuration[figureName]["nrIterations"].as_int_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getCubeFigure();

    Figures3D fractalFigs;
    if (nrIterations > 0) fractalFigs = Utils::generateMengerSponge(fig, nrIterations);
    else fractalFigs.push_back(fig);

    for (auto &curFig : fractalFigs) {
        curFig.ambientReflection = CustomColor(ambientReflection[0], ambientReflection[1], ambientReflection[2]);
        fig.diffuseReflection = CustomColor(diffuseReflection[0], diffuseReflection[1], diffuseReflection[2]);
        fig.specularReflection = CustomColor(specularReflection[0], specularReflection[1], specularReflection[2]);
        fig.reflectionCoefficient = reflectionCoefficient;
        Transformation::applyTransformation(curFig, F);
    }

    return fractalFigs;
}

img::EasyImage Lines3D::wireframe(const ini::Configuration &configuration, bool zBuffer) {
    Figures3D figures;

    const unsigned int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    const unsigned int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();

    Matrix V = Transformation::eyePointTrans(Vector3D::point(eye[0], eye[1], eye[2]));

    Figures3D currentFigs;

    for (unsigned int i = 0; i < nrFigures; i++) {
        std::string figureName = "Figure" + std::to_string(i);

        std::string type = configuration[figureName]["type"].as_string_or_die();

        if (type == "LineDrawing") currentFigs = {eyeFigure(configuration, figureName, V)};
        else if (type == "Cube") currentFigs = {createCube(configuration, figureName, V)};
        else if (type == "Tetrahedron") currentFigs = {createTetrahedron(configuration, figureName, V)};
        else if (type == "Octahedron") currentFigs = {createOctahedron(configuration, figureName, V)};
        else if (type == "Icosahedron") currentFigs = {createIcosahedron(configuration, figureName, V)};
        else if (type == "Dodecahedron") currentFigs = {createDodecahedron(configuration, figureName, V)};
        else if (type == "Sphere") currentFigs = {createSphere(configuration, figureName, V)};
        else if (type == "Cone") currentFigs = {createCone(configuration, figureName, V)};
        else if (type == "Cylinder") currentFigs = {createCylinder(configuration, figureName, V)};
        else if (type == "Torus") currentFigs = {createTorus(configuration, figureName, V)};
        else if (type == "3DLSystem") currentFigs = {LSystem3D::LSystem3D(configuration, figureName, V)};
        else if (type == "FractalCube") currentFigs = createFractalCube(configuration, figureName, V);
        else if (type == "FractalTetrahedron") currentFigs = createFractalTetrahedron(configuration, figureName, V);
        else if (type == "FractalOctahedron") currentFigs = createFractalOctahedron(configuration, figureName, V);
        else if (type == "FractalIcosahedron") currentFigs = createFractalIcosahedron(configuration, figureName, V);
        else if (type == "FractalDodecahedron") currentFigs = createFractalDodecahedron(configuration, figureName, V);
        else if (type == "BuckyBall") currentFigs = {createBuckyBall(configuration, figureName, V)};
        else if (type == "FractalBuckyBall") currentFigs = createFractalBuckyBall(configuration, figureName, V);
        else if (type == "MengerSponge") currentFigs = createMengerSponge(configuration, figureName, V);

        for (auto &curFig : currentFigs) figures.push_back(curFig);
    }

    Lines2D lines = doProjection(figures);

    if (zBuffer) {
        return coordToPixel(lines, size, img::Color(backgroundColor[0] * 255, backgroundColor[1] * 255, backgroundColor[2] * 255), true);
    } else {
        return coordToPixel(lines, size, img::Color(backgroundColor[0] * 255, backgroundColor[1] * 255, backgroundColor[2] * 255));
    }
}