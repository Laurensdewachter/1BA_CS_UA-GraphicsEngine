#include "Transformation.h"
#include "Utils.h"

#include <cmath>

Matrix Transformation::scaleFigure(double scale) {
    Matrix S;
    S(1, 1) = scale;
    S(2, 2) = scale;
    S(3, 3) = scale;

    return S;
}

Matrix Transformation::rotateX(double angle) {
    Matrix Mx;
    Mx(2, 2) = cos(angle);
    Mx(2, 3) = sin(angle);
    Mx(3, 2) = -sin(angle);
    Mx(3, 3) = cos(angle);

    return Mx;
}

Matrix Transformation::rotateY(double angle) {
    Matrix My;
    My(1, 1) = cos(angle);
    My(1, 3) = -sin(angle);
    My(3, 1) = sin(angle);
    My(3, 3) = cos(angle);

    return My;
}

Matrix Transformation::rotateZ(double angle) {
    Matrix Mz;
    Mz(1, 1) = cos(angle);
    Mz(1, 2) = sin(angle);
    Mz(2, 1) = -sin(angle);
    Mz(2, 2) = cos(angle);

    return Mz;
}

Matrix Transformation::translate(const Vector3D &vec) {
    Matrix T;
    T(4, 1) = vec.x;
    T(4, 2) = vec.y;
    T(4, 3) = vec.z;

    return T;
}

Matrix Transformation::eyePointTrans(const Vector3D &eyepoint) {
    double theta, phi, r;
    Utils::toPolar(eyepoint, theta, phi, r);

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

void Transformation::applyTransformation(Figure &fig, const Matrix &M) {
    for (auto &j : fig.points) {
        j *= M;
    }
}