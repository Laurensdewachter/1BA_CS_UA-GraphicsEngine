#include "3DLines.h"

void toPolar(const Vector3D &point, double &theta, double &phi, double &r) {
    r = std::sqrt(std::pow(point.x, 2) + std::pow(point.y, 2) + std::pow(point.z, 2));
    theta = std::atan2(point.y, point.x);
    phi = std::acos(point.z/r);
}

Matrix trans::scaleFigure(double scale) {
    Matrix S;
    S(1, 1) = scale;
    S(2, 2) = scale;
    S(3, 3) = scale;

    return S;
}

Matrix trans::rotateX(double angle) {
    Matrix Mx;
    Mx(2, 2) = cos(angle);
    Mx(2, 3) = sin(angle);
    Mx(3, 2) = -sin(angle);
    Mx(3, 3) = cos(angle);

    return Mx;
}

Matrix trans::rotateY(double angle) {
    Matrix My;
    My(1, 1) = cos(angle);
    My(1, 3) = -sin(angle);
    My(3, 1) = sin(angle);
    My(3, 3) = cos(angle);

    return My;
}

Matrix trans::rotateZ(double angle) {
    Matrix Mz;
    Mz(1, 1) = cos(angle);
    Mz(1, 2) = sin(angle);
    Mz(2, 1) = -sin(angle);
    Mz(2, 2) = cos(angle);

    return Mz;
}

Matrix trans::translate(const Vector3D &vec) {
    Matrix T;
    T(4, 1) = vec.x;
    T(4, 2) = vec.y;
    T(4, 3) = vec.z;

    return T;
}

Matrix trans::eyePointTrans(const Vector3D &eyepoint) {
    double theta, phi, r;
    toPolar(eyepoint, theta, phi, r);

    Matrix M;
    M(1, 1) = -std::sin(theta);
    M(1, 2) = -std::cos(theta) * std::cos(phi);
    M(1, 3) = std::cos(theta) * std::sin(phi);
    M(2, 1) = std::cos(theta);
    M(2, 2) = -std::sin(theta) * std::cos(phi);
    M(2, 3) = std::sin(theta) * std::sin(phi);
    M(3, 2) = std::sin(phi);
    M(3, 3) = std::cos(phi);
    M(4, 3) = -r;

    return M;
}

void trans::applyTransformation(Figure &fig, const Matrix &M) {
    for (auto &j : fig.points) {
        j *= M;
    }
}

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

    Matrix S = trans::scaleFigure(scale);
    Matrix rX = trans::rotateX((rotateX*M_PI)/180);
    Matrix rY = trans::rotateY((rotateY*M_PI)/180);
    Matrix rZ = trans::rotateZ((rotateZ*M_PI)/180);
    Matrix T = trans::translate(Vector3D::point(center[0], center[1], center[2]));

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

    trans::applyTransformation(fig, F);

    return fig;
}

Figure createCube(const ini::Configuration &configuration, Figure body, std::string &figureName,
                Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();

    Matrix S = trans::scaleFigure(scale);
    Matrix rX = trans::rotateX((rotateX*M_PI)/180);
    Matrix rY = trans::rotateY((rotateY*M_PI)/180);
    Matrix rZ = trans::rotateZ((rotateZ*M_PI)/180);
    Matrix T = trans::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    body.color = colorElement;

    trans::applyTransformation(body, F);

    return body;
}

Figure createTetrahedron(const ini::Configuration &configuration, Figure body, std::string &figureName,
                       Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();

    Matrix S = trans::scaleFigure(scale);
    Matrix rX = trans::rotateX((rotateX*M_PI)/180);
    Matrix rY = trans::rotateY((rotateY*M_PI)/180);
    Matrix rZ = trans::rotateZ((rotateZ*M_PI)/180);
    Matrix T = trans::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    body.color = colorElement;

    trans::applyTransformation(body, F);

    return body;
}

Figure createOctahedron(const ini::Configuration &configuration, Figure body, std::string &figureName,
                      Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();

    Matrix S = trans::scaleFigure(scale);
    Matrix rX = trans::rotateX((rotateX*M_PI)/180);
    Matrix rY = trans::rotateY((rotateY*M_PI)/180);
    Matrix rZ = trans::rotateZ((rotateZ*M_PI)/180);
    Matrix T = trans::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    body.color = colorElement;

    trans::applyTransformation(body, F);

    return body;
}

Figure createIcosahedron(const ini::Configuration &configuration, Figure body, std::string &figureName,
                       Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();

    Matrix S = trans::scaleFigure(scale);
    Matrix rX = trans::rotateX((rotateX*M_PI)/180);
    Matrix rY = trans::rotateY((rotateY*M_PI)/180);
    Matrix rZ = trans::rotateZ((rotateZ*M_PI)/180);
    Matrix T = trans::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    body.color = colorElement;

    trans::applyTransformation(body, F);

    return body;
}

Figure createDodecahedron(const ini::Configuration &configuration, Figure body, std::string &figureName,
                        Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();

    Matrix S = trans::scaleFigure(scale);
    Matrix rX = trans::rotateX((rotateX*M_PI)/180);
    Matrix rY = trans::rotateY((rotateY*M_PI)/180);
    Matrix rZ = trans::rotateZ((rotateZ*M_PI)/180);
    Matrix T = trans::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    body.color = colorElement;

    trans::applyTransformation(body, F);

    return body;
}

img::EasyImage Lines3D::wireframe(const ini::Configuration &configuration, PlatonicBodies &bodies) {

    Figures3D figures;

    const unsigned int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    img::Color backgroundColorElement(backgroundColor[0]*255, backgroundColor[1]*255, backgroundColor[2]*255);
    const unsigned int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();

    Matrix V = trans::eyePointTrans(Vector3D::point(eye[0], eye[1], eye[2]));

    for (unsigned int i = 0; i < nrFigures; i++) {
        std::string figureName = "Figure" + std::to_string(i);

        std::string type = configuration[figureName]["type"].as_string_or_die();

        if (type == "LineDrawing") {
            figures.push_back(eyeFigure(configuration, figureName, V));
        } else if (type == "Cube") {
            figures.push_back(createCube(configuration, bodies.getCubeFigure(), figureName, V));
        } else if (type == "Tetrahedron") {
            figures.push_back(createTetrahedron(configuration, bodies.getTetrahedronFigure(), figureName, V));
        } else if (type == "Octahedron") {
            figures.push_back(createOctahedron(configuration, bodies.getOctahedronFigure(), figureName, V));
        } else if (type == "Icosahedron") {
            figures.push_back(createIcosahedron(configuration, bodies.getIcosahedronFigure(), figureName, V));
        } else if (type == "Dodecahedron") {
            figures.push_back(createDodecahedron(configuration, bodies.getDodecahedronFigure(), figureName, V));
        }
    }

    Lines2D lines = doProjection(figures);

    return coordToPixel(lines, size, backgroundColorElement);
}