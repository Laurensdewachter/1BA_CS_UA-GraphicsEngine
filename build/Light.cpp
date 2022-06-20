#include "Light.h"
#include "utils/Figure.h"
#include "utils/Transformation.h"
#include "3DLines.h"
#include "utils/Utils.h"
#include "utils/Clipping.h"

img::EasyImage Light3D::lightedZBuffering(const ini::Configuration &configuration) {
    Figures3D figures;

    const unsigned int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    img::Color backgroundColorElement(backgroundColor[0] * 255, backgroundColor[1] * 255, backgroundColor[2] * 255);
    const unsigned int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();
    const unsigned int nrLight = configuration["General"]["nrLights"].as_int_or_die();
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
    Lights3D lights;
    for (unsigned int i = 0; i < nrLight; i++) {
        std::string lightName = "Light" + std::to_string(i);

        std::vector<double> ambientLight = configuration[lightName]["ambientLight"].as_double_tuple_or_die();
        std::vector<double> diffuseLight;
        std::vector<double> specularLight = configuration[lightName]["specularLight"].as_double_tuple_or_default({0, 0, 0});

        if (configuration[lightName]["diffuseLight"].as_double_tuple_if_exists(diffuseLight)) {
            bool inf = configuration[lightName]["infinity"].as_bool_or_die();

            if (inf) {
                auto* newLight = new InfLight();

                const std::vector<double> direction = configuration[lightName]["direction"].as_double_tuple_or_die();
                newLight->ldVector = Vector3D::vector(direction[0], direction[1], direction[2])*V;

                newLight->ambientLight = CustomColor(ambientLight[0], ambientLight[1], ambientLight[2]);
                newLight->diffuseLight = CustomColor(diffuseLight[0], diffuseLight[1], diffuseLight[2]);
                newLight->specularLight = CustomColor(specularLight[0], specularLight[1], specularLight[2]);

                lights.push_back(newLight);
            } else {
                auto newLight = new PointLight();

                const std::vector<double> location = configuration[lightName]["location"].as_double_tuple_or_die();
                newLight->location = Vector3D::point(location[0], location[1], location[2])*V;
                newLight->spotAngle = configuration[lightName]["spotAngle"].as_double_or_default(90);

                newLight->ambientLight = CustomColor(ambientLight[0], ambientLight[1], ambientLight[2]);
                newLight->diffuseLight = CustomColor(diffuseLight[0], diffuseLight[1], diffuseLight[2]);
                newLight->specularLight = CustomColor(specularLight[0], specularLight[1], specularLight[2]);

                lights.push_back(newLight);
            }
        } else {
            auto newLight = new Light();
            newLight->ambientLight = CustomColor(ambientLight[0], ambientLight[1], ambientLight[2]);
            lights.push_back(newLight);
        }



    }

    for (unsigned int i = 0; i < nrFigures; i++) {
        std::string figureName = "Figure" + std::to_string(i);

        std::string type = configuration[figureName]["type"].as_string_or_die();

        Figures3D currentFigs;

        if (type == "Cube") currentFigs = {createCube(configuration, figureName, V, true)};
        else if (type == "Tetrahedron") currentFigs = {createTetrahedron(configuration, figureName, V, true)};
        else if (type == "Octahedron") currentFigs = {createOctahedron(configuration, figureName, V, true)};
        else if (type == "Icosahedron") currentFigs = {createIcosahedron(configuration, figureName, V, true)};
        else if (type == "Dodecahedron") currentFigs = {createDodecahedron(configuration, figureName, V, true)};
        else if (type == "Sphere") currentFigs = {createSphere(configuration, figureName, V, true)};
        else if (type == "Cone") currentFigs = {createCone(configuration, figureName, V, true)};
        else if (type == "Cylinder") currentFigs = {createCylinder(configuration, figureName, V, true)};
        else if (type == "Torus") currentFigs = {(createTorus(configuration, figureName, V, true))};
        else if (type == "FractalCube") currentFigs = createFractalCube(configuration, figureName, V, true);
        else if (type == "FractalTetrahedron") currentFigs = createFractalTetrahedron(configuration, figureName, V, true);
        else if (type == "FractalOctahedron") currentFigs = createFractalOctahedron(configuration, figureName, V, true);
        else if (type == "FractalIcosahedron") currentFigs = createFractalIcosahedron(configuration, figureName, V, true);
        else if (type == "FractalDodecahedron") currentFigs = createFractalDodecahedron(configuration, figureName, V, true);
        else if (type == "BuckyBall") currentFigs.push_back(createBuckyBall(configuration, figureName, V, true));
        else if (type == "FractalBuckyBall") currentFigs = createFractalBuckyBall(configuration, figureName, V, true);
        else if (type == "MengerSponge") currentFigs = createMengerSponge(configuration, figureName, V, true);
        else if (type == "ThickLineDrawing") currentFigs = createThickEyeFigure(configuration, figureName, V, true);
        else if (type == "ThickCube") currentFigs = createThickCube(configuration, figureName, V, true);
        else if (type == "ThickTetrahedron") currentFigs = createThickTetrahedron(configuration, figureName, V, true);
        else if (type == "ThickOctahedron") currentFigs = createThickOctahedron(configuration, figureName, V, true);
        else if (type == "ThickIcosahedron") currentFigs = createThickIcosahedron(configuration, figureName, V, true);
        else if (type == "ThickDodecahedron") currentFigs = createThickDodecahedron(configuration, figureName, V, true);
        else if (type == "Thick3DLSystem") currentFigs = createThick3DLSystem(configuration, figureName, V, true);
        else if (type == "ThickBuckyBall") currentFigs = createThickBuckyBall(configuration, figureName, V, true);
        else if (type == "Road") currentFigs = {createRoad(configuration, figureName, V)};

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
                                  curFig.diffuseReflection, curFig.specularReflection, curFig.reflectionCoefficient, lights);
        }
    }

    return image;
}