#include "3DTriangles.h"
#include "3DLines.h"
#include "utils/Transformation.h"
#include "utils/Utils.h"
#include "utils/Clipping.h"

img::EasyImage Triangles3D::zBuffer(const ini::Configuration &configuration) {
    Figures3D figures;

    const unsigned int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    img::Color backgroundColorElement(backgroundColor[0] * 255, backgroundColor[1] * 255, backgroundColor[2] * 255);
    const unsigned int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();
    bool clipping = false;
    std::vector<double> viewDirection;
    double hfov, aspectRatio, dNear, dFar, right, left, top, bottom;

    Matrix V;
    if (configuration["General"]["clipping"].as_bool_if_exists(clipping)) {
        viewDirection = configuration["General"]["viewDirection"].as_double_tuple_or_die();
        hfov = configuration["General"]["hfov"].as_double_or_die();
        aspectRatio = configuration["General"]["aspectRatio"].as_double_or_die();
        dNear = configuration["General"]["dNear"].as_double_or_die();
        dFar = configuration["General"]["dFar"].as_double_or_die();
        hfov = hfov/2.0;
        hfov = (hfov*M_PI)/180.0;

        right = dNear * tan(hfov);
        left = -right;
        top = right/aspectRatio;
        bottom = -top;

        double thetaDir, phiDir, rDir;
        Vector3D eyeDir = Vector3D::vector(viewDirection[0], viewDirection[1], viewDirection[2]);
        Utils::toPolar(-eyeDir, thetaDir, phiDir, rDir);

        double thetaPos, phiPos, rPos;
        Vector3D eyePos = Vector3D::vector(eye[0], eye[1], eye[2]);
        Utils::toPolar(eyePos, thetaPos, phiPos, rPos);

        V = Transformation::clippingTrans(thetaDir, phiDir, rPos);
    } else {
        V = Transformation::eyePointTrans(Vector3D::point(eye[0], eye[1], eye[2]));
    }

    Lights3D lights = {new Light(img::Color(1, 1, 1), img::Color(0, 0, 0), img::Color(0, 0, 0))};

    for (unsigned int i = 0; i < nrFigures; i++) {
        std::string figureName = "Figure" + std::to_string(i);

        std::string type = configuration[figureName]["type"].as_string_or_die();

        Figures3D currentFigs;

        if (type == "Cube") currentFigs = {createCube(configuration, figureName, V)};
        else if (type == "Tetrahedron") currentFigs = {createTetrahedron(configuration, figureName, V)};
        else if (type == "Octahedron") currentFigs = {createOctahedron(configuration, figureName, V)};
        else if (type == "Icosahedron") currentFigs = {createIcosahedron(configuration, figureName, V)};
        else if (type == "Dodecahedron") currentFigs = {createDodecahedron(configuration, figureName, V)};
        else if (type == "Sphere") currentFigs = {createSphere(configuration, figureName, V)};
        else if (type == "Cone") currentFigs = {createCone(configuration, figureName, V)};
        else if (type == "Cylinder") currentFigs = {createCylinder(configuration, figureName, V)};
        else if (type == "Torus") currentFigs = {(createTorus(configuration, figureName, V))};
        else if (type == "FractalCube") currentFigs = createFractalCube(configuration, figureName, V);
        else if (type == "FractalTetrahedron") currentFigs = createFractalTetrahedron(configuration, figureName, V);
        else if (type == "FractalOctahedron") currentFigs = createFractalOctahedron(configuration, figureName, V);
        else if (type == "FractalIcosahedron") currentFigs = createFractalIcosahedron(configuration, figureName, V);
        else if (type == "FractalDodecahedron") currentFigs = createFractalDodecahedron(configuration, figureName, V);
        else if (type == "BuckyBall") currentFigs.push_back(createBuckyBall(configuration, figureName, V));
        else if (type == "FractalBuckyBall") currentFigs = createFractalBuckyBall(configuration, figureName, V);
        else if (type == "MengerSponge") currentFigs = createMengerSponge(configuration, figureName, V);

        for (auto &currentFig : currentFigs) {
            Utils::triangulate(currentFig);
            if (clipping) Clipping::clipFigure(currentFig, dNear, dFar, right, left, top, bottom);

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
                                  curFig.points[curFace.point_indexes[2]], d, dx, dy, curFig.ambientReflection,
                                  curFig.diffuseReflection, curFig.specularReflection,
                                  curFig.reflectionCoefficient, lights);
        }
    }

    return image;
}