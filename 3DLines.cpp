#include "3DLines.h"
#include "utils/Transformation.h"
#include "utils/Utils.h"
#include "LSystems/3DLSystem.h"

Point2D doProjection(const Vector3D &point, double d) {
    return Point2D{(d*point.x)/(-point.z), (d*point.y)/(-point.z)};
}

Lines2D doProjection(const Figures3D &figs) {
    Lines2D lines;
    for (auto i : figs) {
        for (auto j : i.faces) {
            for (unsigned int k = 0; k < j.point_indexes.size(); k++) {
                Line2D line;
                if (k == j.point_indexes.size()-1) {
                    line.p1 = doProjection(i.points[j.point_indexes[k]], 1);
                    line.p2 = doProjection(i.points[j.point_indexes[0]], 1);
                } else {
                    line.p1 = doProjection(i.points[j.point_indexes[k]], 1);
                    line.p2 = doProjection(i.points[j.point_indexes[k + 1]], 1);
                }
                line.color = i.color;
                lines.push_back(line);
            }
        }
    }
    return lines;
}

Figure eyeFigure(const ini::Configuration &configuration, std::string &figureName,
               Matrix &V) {
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

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    fig.color = colorElement;

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

Figure createCube(const ini::Configuration &configuration, std::string &figureName,
                Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getCubeFigure();

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    fig.color = colorElement;

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figure createTetrahedron(const ini::Configuration &configuration, std::string &figureName,
                       Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getTetrahedronFigure();

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    fig.color = colorElement;

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figure createOctahedron(const ini::Configuration &configuration, std::string &figureName,
                      Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getOctahedronFigure();

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    fig.color = colorElement;

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figure createIcosahedron(const ini::Configuration &configuration, std::string &figureName,
                       Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getIcosahedronFigure();

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    fig.color = colorElement;

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figure createDodecahedron(const ini::Configuration &configuration, std::string &figureName,
                        Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getDodecahedronFigure();

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    fig.color = colorElement;

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figure createSphere(const ini::Configuration &configuration, std::string &figureName, Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();
    const unsigned int n = configuration[figureName]["n"].as_int_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig = PlatonicBodies::getIcosahedronFigure();

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    fig.color = colorElement;

    for (unsigned int i = 0; i < n; i++) {
        Utils::splitTriangles(fig);
    }

    for (auto & point : fig.points) point.normalise();

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figure createCone(const ini::Configuration &configuration, std::string &figureName, Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();
    const int n = configuration[figureName]["n"].as_int_or_die();
    const double height = configuration[figureName]["height"].as_double_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig;

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    fig.color = colorElement;

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

Figure createCylinder(const ini::Configuration &configuration, std::string &figureName, Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();
    const int n = configuration[figureName]["n"].as_int_or_die();
    const double height = configuration[figureName]["height"].as_double_or_die();

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Figure fig;

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    fig.color = colorElement;

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
    for (int i = n-1; i >= 0; i--) ground.point_indexes.push_back(i);
    for (int i = (2*n)-1; i >= n; i--) roof.point_indexes.push_back(i);
    fig.faces.push_back(ground);
    fig.faces.push_back(roof);

    Transformation::applyTransformation(fig, F);

    return fig;
}

Figure createTorus(const ini::Configuration &configuration, std::string &figureName, Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();
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

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    fig.color = colorElement;

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

img::EasyImage Lines3D::wireframe(const ini::Configuration &configuration) {

    Figures3D figures;

    const unsigned int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    img::Color backgroundColorElement(backgroundColor[0]*255, backgroundColor[1]*255, backgroundColor[2]*255);
    const unsigned int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();

    Matrix V = Transformation::eyePointTrans(Vector3D::point(eye[0], eye[1], eye[2]));

    for (unsigned int i = 0; i < nrFigures; i++) {
        std::string figureName = "Figure" + std::to_string(i);

        std::string type = configuration[figureName]["type"].as_string_or_die();

        if (type == "LineDrawing") {
            figures.push_back(eyeFigure(configuration, figureName, V));
        } else if (type == "Cube") {
            figures.push_back(createCube(configuration, figureName, V));
        } else if (type == "Tetrahedron") {
            figures.push_back(createTetrahedron(configuration, figureName, V));
        } else if (type == "Octahedron") {
            figures.push_back(createOctahedron(configuration, figureName, V));
        } else if (type == "Icosahedron") {
            figures.push_back(createIcosahedron(configuration, figureName, V));
        } else if (type == "Dodecahedron") {
            figures.push_back(createDodecahedron(configuration, figureName, V));
        } else if (type == "Sphere") {
            figures.push_back(createSphere(configuration, figureName, V));
        } else if (type == "Cone") {
            figures.push_back(createCone(configuration, figureName, V));
        } else if (type == "Cylinder") {
            figures.push_back(createCylinder(configuration, figureName, V));
        } else if (type == "Torus") {
            figures.push_back(createTorus(configuration, figureName, V));
        } else if (type == "3DLSystem") {
            figures.push_back(LSystem3D::LSystem3D(configuration, figureName, V));
        }
    }

    Lines2D lines = doProjection(figures);

    return coordToPixel(lines, size, backgroundColorElement);
}