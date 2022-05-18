#include "Utils.h"
#include "Transformation.h"
#include <cmath>

void Utils::toPolar(const Vector3D &point, double &theta, double &phi, double &r) {
    r = std::sqrt(std::pow(point.x, 2) + std::pow(point.y, 2) + std::pow(point.z, 2));
    theta = std::atan2(point.y, point.x);
    phi = std::acos(point.z/r);
}

void Utils::splitTriangles(Figure &figure) {
    Figure newFig;
    newFig.ambientReflection = figure.ambientReflection;
    newFig.diffuseReflection = figure.diffuseReflection;
    newFig.specularReflection = figure.specularReflection;
    newFig.reflectionCoefficient = figure.reflectionCoefficient;
    int pointCounter = 0;

    for (auto face : figure.faces) {
        Vector3D a = figure.points[face.point_indexes[0]];
        Vector3D b = figure.points[face.point_indexes[1]];
        Vector3D c = figure.points[face.point_indexes[2]];

        Vector3D d = (a+b)/2;
        Vector3D e = (a+c)/2;
        Vector3D f = (b+c)/2;

        newFig.points.push_back(a);
        newFig.points.push_back(b);
        newFig.points.push_back(c);
        newFig.points.push_back(d);
        newFig.points.push_back(e);
        newFig.points.push_back(f);

        Face face1({pointCounter, pointCounter+3, pointCounter+4});
        Face face2({pointCounter+1, pointCounter+5, pointCounter+3});
        Face face3({pointCounter+2, pointCounter+4, pointCounter+5});
        Face face4({pointCounter+3, pointCounter+5, pointCounter+4});

        newFig.faces.push_back(face1);
        newFig.faces.push_back(face2);
        newFig.faces.push_back(face3);
        newFig.faces.push_back(face4);

        pointCounter += 6;
    }
    figure = newFig;
}

void Utils::triangulate(Figure &fig) {
    std::vector<Face> newFaces;

    for (auto &f: fig.faces) {
        if (f.point_indexes.size() > 3) {
            for (unsigned int i = 1; i < f.point_indexes.size()-1; i++) {
                Face newFace({f.point_indexes[0], f.point_indexes[i], f.point_indexes[i+1]});
                newFaces.push_back(newFace);
            }
        } else newFaces.push_back(f);
    }
    fig.faces = newFaces;
}

void Utils::calculateValues(Lines2D &lines, double size, double &width, double &height, double &d, double &dx, double &dy) {
    std::list<Point2D> points;
    for (auto &i: lines) {
        points.push_back(i.p1);
        points.push_back(i.p2);
    }
    std::list<double> xPoints;
    std::list<double> yPoints;
    for (auto &i: points) {
        xPoints.push_back(i.x);
        yPoints.push_back(i.y);
    }

    double xMax = *std::max_element(xPoints.begin(), xPoints.end());
    double xMin = *std::min_element(xPoints.begin(), xPoints.end());
    double yMax = *std::max_element(yPoints.begin(), yPoints.end());
    double yMin = *std::min_element(yPoints.begin(), yPoints.end());

    double xRange = xMax - xMin;
    double yRange = yMax - yMin;

    width = size * (xRange / std::max(xRange, yRange));
    height = size * (yRange / std::max(xRange, yRange));

    d = 0.95 * (width / xRange);

    double DCx = d * ((xMax + xMin)/2.0);
    double DCy = d * ((yMax + yMin)/2.0);
    dx = (width/2.0) - DCx;
    dy = (height/2.0) - DCy;
}

Figures3D Utils::generateFractal(Figure &fig, const unsigned int nrIterations, const double scale) {
    std::vector<Figure> toConvert = {fig};
    std::vector<Figure> newFigs;

    for (unsigned int it = 0; it < nrIterations; it++) {
        newFigs.clear();
        for (auto & curFig : toConvert) {
            for (unsigned int pointIndex = 0; pointIndex < curFig.points.size(); pointIndex++) {
                Vector3D curPoint = curFig.points[pointIndex];

                Figure newFig = curFig;
                Matrix S = Transformation::scaleFigure(1 / scale);
                Transformation::applyTransformation(newFig, S);

                Matrix T = Transformation::translate(curPoint - newFig.points[pointIndex]);
                Transformation::applyTransformation(newFig, T);

                newFigs.push_back(newFig);
            }
        }
        toConvert = newFigs;
    }

    Figures3D result;
    for (auto &curFig : newFigs) result.push_back(curFig);
    return result;
}

Figures3D Utils::generateMengerSponge(Figure &fig, unsigned int nrIterations) {
    fig.points.push_back(Vector3D::point(0, -1, 1));
    fig.points.push_back(Vector3D::point(0, -1, -1));
    fig.points.push_back(Vector3D::point(0, 1, 1));
    fig.points.push_back(Vector3D::point(0, 1, -1));
    fig.points.push_back(Vector3D::point(-1, 0, 1));
    fig.points.push_back(Vector3D::point(-1, 0, -1));
    fig.points.push_back(Vector3D::point(1, 0, 1));
    fig.points.push_back(Vector3D::point(1, 0, -1));
    fig.points.push_back(Vector3D::point(-1, -1, 0));
    fig.points.push_back(Vector3D::point(1, -1, 0));
    fig.points.push_back(Vector3D::point(-1, 1, 0));
    fig.points.push_back(Vector3D::point(1, 1, 0));
    std::vector<Figure> toConvert = {fig};
    std::vector<Figure> newFigs;

    for (unsigned int it = 0; it < nrIterations; it++) {
        newFigs.clear();
        for (auto & curFig : toConvert) {
            for (unsigned int pointIndex = 0; pointIndex < curFig.points.size(); pointIndex++) {
                Vector3D curPoint = curFig.points[pointIndex];

                Figure newFig = curFig;
                Matrix S = Transformation::scaleFigure(1.0/3.0);
                Transformation::applyTransformation(newFig, S);

                Matrix T = Transformation::translate(curPoint - newFig.points[pointIndex]);
                Transformation::applyTransformation(newFig, T);

                newFigs.push_back(newFig);
            }
        }
        toConvert = newFigs;
    }

    Figures3D result;
    for (auto &curFig : newFigs) result.push_back(curFig);
    return result;
}
