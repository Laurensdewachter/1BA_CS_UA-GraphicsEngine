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
    //bool clipping = false;
    //std::vector<double> viewDirection;
    //double hfov, aspectRatio, dNear, dFar;

    Matrix V;
    /*
    if (configuration["General"]["clipping"].as_bool_if_exists(clipping)) {
        viewDirection = configuration["General"]["viewDirection"].as_double_tuple_or_die();
        hfov = configuration["General"]["hfov"].as_double_or_die();
        aspectRatio = configuration["General"]["aspectRatio"].as_double_or_die();
        dNear = configuration["General"]["dNear"].as_double_or_die();
        dFar = configuration["General"]["dFar"].as_double_or_die();

        double thetaDir, phiDir, rDir;
        Utils::toPolar(Vector3D::vector(-viewDirection[0], -viewDirection[1], -viewDirection[2]), thetaDir, phiDir, rDir);
        double thetaPos, phiPos, rPos;
        Utils::toPolar(Vector3D::point(eye[0], eye[1], eye[2]), thetaPos, phiPos, rPos);

        V = Transformation::clippingTrans(thetaDir, phiDir, rPos);
    } else {
        V = Transformation::eyePointTrans(Vector3D::point(eye[0], eye[1], eye[2]));
    }
     */
    V = Transformation::eyePointTrans(Vector3D::point(eye[0], eye[1], eye[2]));

    for (unsigned int i = 0; i < nrFigures; i++) {
        std::string figureName = "Figure" + std::to_string(i);

        std::string type = configuration[figureName]["type"].as_string_or_die();

        Figures3D currentFigs;

        if (type == "Cube") currentFigs.push_back(createCube(configuration, figureName, V));
        else if (type == "Tetrahedron") currentFigs.push_back(createTetrahedron(configuration, figureName, V));
        else if (type == "Octahedron") currentFigs.push_back(createOctahedron(configuration, figureName, V));
        else if (type == "Icosahedron") currentFigs.push_back(createIcosahedron(configuration, figureName, V));
        else if (type == "Dodecahedron") currentFigs.push_back(createDodecahedron(configuration, figureName, V));
        else if (type == "Sphere") currentFigs.push_back(createSphere(configuration, figureName, V));
        else if (type == "Cone") currentFigs.push_back(createCone(configuration, figureName, V));
        else if (type == "Cylinder") currentFigs.push_back(createCylinder(configuration, figureName, V));
        else if (type == "Torus") currentFigs.push_back(createTorus(configuration, figureName, V));
        else if (type == "FractalCube") {
            Figures3D fractalFigs = createFractalCube(configuration, figureName, V);
            for (auto &curFig : fractalFigs) currentFigs.push_back(curFig);
        }
        else if (type == "FractalTetrahedron") {
            Figures3D fractalFigs = createFractalTetrahedron(configuration, figureName, V);
            for (auto &curFig : fractalFigs) currentFigs.push_back(curFig);
        }
        else if (type == "FractalOctahedron") {
            Figures3D fractalFigs = createFractalOctahedron(configuration, figureName, V);
            for (auto &curFig : fractalFigs) currentFigs.push_back(curFig);
        }
        else if (type == "FractalIcosahedron") {
            Figures3D fractalFigs = createFractalIcosahedron(configuration, figureName, V);
            for (auto &curFig : fractalFigs) currentFigs.push_back(curFig);
        }
        else if (type == "FractalDodecahedron") {
            Figures3D fractalFigs = createFractalDodecahedron(configuration, figureName, V);
            for (auto &curFig : fractalFigs) currentFigs.push_back(curFig);
        }
        else if (type == "BuckyBall") currentFigs.push_back(createBuckyBall(configuration, figureName, V));
        else if (type == "FractalBuckyBall") {
            Figures3D fractalFigs = createFractalBuckyBall(configuration, figureName, V);
            for (auto &curFig : fractalFigs) currentFigs.push_back(curFig);
        }
        else if (type == "MengerSponge") {
            Figures3D fractalFigs = createMengerSponge(configuration, figureName, V);
            for (auto &curFig : fractalFigs) currentFigs.push_back(curFig);
        }

        for (auto &currentFig : currentFigs) {
            std::vector<Face> newFaces;
            for (auto &f: currentFig.faces) {
                if (f.point_indexes.size() > 3) {
                    std::vector<Face> tempNewFaces;
                    tempNewFaces = Utils::triangulate(f);
                    for (auto &f2: tempNewFaces) newFaces.push_back(f2);
                } else newFaces.push_back(f);
            }
            currentFig.faces = newFaces;

            figures.push_back(currentFig);
        }
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