#include "3DTriangles.h"
#include "3DLines.h"
#include "utils/Transformation.h"
#include "utils/Utils.h"

img::EasyImage Triangles3D::zBuffer(const ini::Configuration &configuration) {
    Figures3D figures;

    const unsigned int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    img::Color backgroundColorElement(backgroundColor[0] * 255, backgroundColor[1] * 255, backgroundColor[2] * 255);
    const unsigned int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();

    Matrix V = Transformation::eyePointTrans(Vector3D::point(eye[0], eye[1], eye[2]));

    for (unsigned int i = 0; i < nrFigures; i++) {
        std::string figureName = "Figure" + std::to_string(i);

        std::string type = configuration[figureName]["type"].as_string_or_die();

        Figure currentFig;

        if (type == "LineDrawing") {
            currentFig = eyeFigure(configuration, figureName, V);
        } else if (type == "Cube") {
            currentFig = createCube(configuration, figureName, V);
        } else if (type == "Tetrahedron") {
            currentFig = createTetrahedron(configuration, figureName, V);
        } else if (type == "Octahedron") {
            currentFig = createOctahedron(configuration, figureName, V);
        } else if (type == "Icosahedron") {
            currentFig = createIcosahedron(configuration, figureName, V);
        } else if (type == "Dodecahedron") {
            currentFig = createDodecahedron(configuration, figureName, V);
        } else if (type == "Sphere") {
            currentFig = createSphere(configuration, figureName, V);
        } else if (type == "Cone") {
            currentFig = createCone(configuration, figureName, V);
        } else if (type == "Cylinder") {
            currentFig = createCylinder(configuration, figureName, V);
        } else if (type == "Torus") {
            currentFig = createTorus(configuration, figureName, V);
        }

        std::vector<Face> newFaces;
        for (auto &f : currentFig.faces) {
            if (f.point_indexes.size() > 3) {
                std::vector<Face> tempNewFaces;
                tempNewFaces = Utils::triangulate(f);
                for (auto &f2 : tempNewFaces) newFaces.push_back(f2);
            } else newFaces.push_back(f);
        }
        currentFig.faces = newFaces;
        figures.push_back(currentFig);
    }

    Lines2D projection = doProjectionConst(figures);
    double width, height, d, dx, dy;
    Utils::calculateValues(projection, size, width, height, d, dx, dy);

    img::EasyImage image(lround(width), lround(height), backgroundColorElement);
    ZBuffer buffer(image.get_width(), image.get_height());

    for (auto &curFig : figures) {
        for (auto &curFace : curFig.faces) {
            image.draw_zbuf_triag(buffer, curFig.points[curFace.point_indexes[0]], curFig.points[curFace.point_indexes[1]],
                                  curFig.points[curFace.point_indexes[2]], d, dx, dy, curFig.color);
        }
    }

    return image;
}