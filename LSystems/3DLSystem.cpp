#include "3DLSystem.h"
#include "../utils/l_parser.h"
#include "../utils/Transformation.h"

#include <fstream>
#include <cmath>
#include <stack>

Figure LSystem3D::LSystem3D(const ini::Configuration &configuration, const std::string &figureName, Matrix &V) {
    const double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
    const double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
    const double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
    const double scale = configuration[figureName]["scale"].as_double_or_die();
    std::vector<double> center = configuration[figureName]["center"].as_double_tuple_or_die();
    std::vector<double> color = configuration[figureName]["color"].as_double_tuple_or_die();
    const std::string inputfile = configuration[figureName]["inputfile"].as_string_or_die();

    LParser::LSystem3D l_system;
    std::ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();

    const std::set<char> alphabet = l_system.get_alphabet();
    std::string initiator = l_system.get_initiator();
    double angle = l_system.get_angle();
    const unsigned int iterations = l_system.get_nr_iterations();

    std::map<char, std::string> replacements;
    std::map<char, bool> draw;
    for (auto i: alphabet) {
        draw[i] = l_system.draw(i);
        replacements[i] = l_system.get_replacement(i);
    }

    angle = (angle*M_PI)/180;

    Vector3D curPoint = Vector3D::point(0, 0, 0);
    Vector3D H = Vector3D::vector(1, 0, 0);
    Vector3D L = Vector3D::vector(0, 1, 0);
    Vector3D U = Vector3D::vector(0, 0, 1);
    std::stack<Vector3D> pointStack;
    std::stack<Vector3D> HStack;
    std::stack<Vector3D> LStack;
    std::stack<Vector3D> UStack;

    Figure fig;

    img::Color colorElement(color[0]*255, color[1]*255, color[2]*255);
    fig.color = colorElement;

    fig.points.push_back(curPoint);
    int indexCounter = 0;

    for (unsigned int i = 0; i < iterations; i++) {
        std::string replacement;
        for (auto j: initiator) {
            if (j == '+') replacement += "+";
            else if (j == '-') replacement += "-";
            else if (j == '(') replacement += "(";
            else if (j == ')') replacement += ")";
            else if (j == '^') replacement += "^";
            else if (j == '&') replacement += "&";
            else if (j == '\\') replacement += "\\";
            else if (j == '/') replacement += "/";
            else if (j == '|') replacement += "|";
            else replacement += replacements[j];
        }
        initiator = replacement;
    }

    for (auto i : initiator) {
        if (i == '+') {
            Vector3D tempH(H);
            H = (H*cos(angle)) + (L*sin(angle));
            L = (L*cos(angle)) - (tempH*sin(angle));
            continue;
        }
        if (i == '-') {
            Vector3D tempH(H);
            H = (H*cos(-angle)) + (L*sin(-angle));
            L = (L*cos(-angle)) - (tempH*sin(-angle));
            continue;
        }
        if (i == '^') {
            Vector3D tempH(H);
            H = (H*cos(angle)) + (U*sin(angle));
            U = (U*cos(angle)) - (tempH*sin(angle));
            continue;
        }
        if (i == '&') {
            Vector3D tempH(H);
            H = (H*cos(-angle)) + (U*sin(-angle));
            U = (U*cos(-angle)) - (tempH*sin(-angle));
            continue;
        }
        if (i == '\\') {
            Vector3D tempL(L);
            L = (L*cos(angle)) - (U*sin(angle));
            U = (tempL*sin(angle)) + (U*cos(angle));
            continue;
        }
        if (i == '/') {
            Vector3D tempL(L);
            L = (L*cos(-angle)) - (U*sin(-angle));
            U = (tempL*sin(-angle)) + (U*cos(-angle));
            continue;
        }
        if (i == '|') {
            H = -H;
            L = -L;
            continue;
        }
        if (i == '(') {
            pointStack.push(curPoint);
            HStack.push(H);
            LStack.push(L);
            UStack.push(U);
            continue;
        }
        if (i == ')') {
            curPoint = pointStack.top();
            pointStack.pop();
            H = HStack.top();
            HStack.pop();
            L = LStack.top();
            LStack.pop();
            U = UStack.top();
            UStack.pop();

            fig.points.push_back(curPoint);
            indexCounter++;
            continue;
        }
        curPoint += H;
        fig.points.push_back(curPoint);
        indexCounter++;
        if (draw[i]) {
            Face newFace({indexCounter, indexCounter-1});
            fig.faces.push_back(newFace);
        }
    }

    Matrix S = Transformation::scaleFigure(scale);
    Matrix rX = Transformation::rotateX((rotateX*M_PI)/180);
    Matrix rY = Transformation::rotateY((rotateY*M_PI)/180);
    Matrix rZ = Transformation::rotateZ((rotateZ*M_PI)/180);
    Matrix T = Transformation::translate(Vector3D::point(center[0], center[1], center[2]));

    Matrix F = S * rX * rY * rZ * T * V;

    Transformation::applyTransformation(fig, F);

    return fig;
}