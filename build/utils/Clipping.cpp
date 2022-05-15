#include "Clipping.h"

void Clipping::clipFigure(Figure &fig, double dNear, double dFar, double right, double left, double top, double bottom) {
    std::vector<Face> newFaces;
    std::vector<Face> toClip;
    int pointIndexCounter = (int) fig.points.size();

    double dVal = -dNear;
    for (auto &curFace : fig.faces) {
        Vector3D point1 = fig.points[curFace.point_indexes[0]];
        Vector3D point2 = fig.points[curFace.point_indexes[1]];
        Vector3D point3 = fig.points[curFace.point_indexes[2]];

        if (point1.z > dVal || point2.z > dVal || point3.z > dVal) {
            std::vector<Vector3D *> pointsOutside;
            std::vector<Vector3D *> pointsInside;
            if (point1.z > dVal) pointsOutside.push_back(&point1);
            else pointsInside.push_back(&point1);
            if (point2.z > dVal) pointsOutside.push_back(&point2);
            else pointsInside.push_back(&point2);
            if (point3.z > dVal) pointsOutside.push_back(&point3);
            else pointsInside.push_back(&point3);

            Vector3D *A;
            Vector3D *B;
            Vector3D *C;

            if (pointsOutside.size() == 2) {
                A = pointsInside[0];
                B = pointsOutside[0];
                C = pointsOutside[1];
            } else if (pointsInside.size() == 2) {
                A = pointsOutside[0];
                B = pointsInside[0];
                C = pointsInside[1];
            } else {
                continue;
            }

            const double p1 = (dVal - B->z) / (A->z - B->z);
            const double p2 = (dVal - C->z) / (A->z - C->z);
            Vector3D newA = p1 * *A + (1 - p1) * *B;
            Vector3D newB = p2 * *A + (1 - p2) * *C;

            fig.points.push_back(newA);
            fig.points.push_back(newB);

            if (pointsOutside.size() == 2) {
                Face newFaceA;
                if (pointsInside[0] == &point1) {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                } else if (pointsInside[0] == &point2) {
                    newFaceA.point_indexes = {curFace.point_indexes[1], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                } else {
                    newFaceA.point_indexes = {curFace.point_indexes[2], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                }
                toClip.push_back(newFaceA);
            }

            if (pointsInside.size() == 2) {
                Face newFaceA;
                Face newFaceB;
                if (pointsOutside[0] == &point1) {
                    newFaceA.point_indexes = {curFace.point_indexes[1], pointIndexCounter, curFace.point_indexes[2]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[2]};
                    pointIndexCounter += 2;
                } else if (pointsOutside[0] == &point2) {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, curFace.point_indexes[2]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[2]};
                    pointIndexCounter += 2;
                } else {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, curFace.point_indexes[1]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[1]};
                    pointIndexCounter += 2;
                }
                toClip.push_back(newFaceA);
                toClip.push_back(newFaceB);
            }
        } else toClip.push_back(curFace);
    }

    std::vector<Face> toClipExtra;

    dVal = -dFar;
    for (auto &curFace : toClip) {
        Vector3D point1 = fig.points[curFace.point_indexes[0]];
        Vector3D point2 = fig.points[curFace.point_indexes[1]];
        Vector3D point3 = fig.points[curFace.point_indexes[2]];

        if (point1.z < dVal || point2.z < dVal || point3.z < dVal) {
            std::vector<Vector3D *> pointsOutside;
            std::vector<Vector3D *> pointsInside;
            if (point1.z < dVal) pointsOutside.push_back(&point1);
            else pointsInside.push_back(&point1);
            if (point2.z < dVal) pointsOutside.push_back(&point2);
            else pointsInside.push_back(&point2);
            if (point3.z < dVal) pointsOutside.push_back(&point3);
            else pointsInside.push_back(&point3);

            Vector3D *A;
            Vector3D *B;
            Vector3D *C;

            if (pointsOutside.size() == 2) {
                A = pointsInside[0];
                B = pointsOutside[0];
                C = pointsOutside[1];
            } else if (pointsInside.size() == 2) {
                A = pointsOutside[0];
                B = pointsInside[0];
                C = pointsInside[1];
            } else {
                continue;
            }

            const double p1 = (dVal - B->z) / (A->z - B->z);
            const double p2 = (dVal - C->z) / (A->z - C->z);
            Vector3D newA = p1 * *A + (1 - p1) * *B;
            Vector3D newB = p2 * *A + (1 - p2) * *C;

            fig.points.push_back(newA);
            fig.points.push_back(newB);

            if (pointsOutside.size() == 2) {
                Face newFaceA;
                if (pointsInside[0] == &point1) {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                } else if (pointsInside[0] == &point2) {
                    newFaceA.point_indexes = {curFace.point_indexes[1], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                } else {
                    newFaceA.point_indexes = {curFace.point_indexes[2], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                }
                toClipExtra.push_back(newFaceA);
            }

            if (pointsInside.size() == 2) {
                Face newFaceA;
                Face newFaceB;
                if (pointsOutside[0] == &point1) {
                    newFaceA.point_indexes = {curFace.point_indexes[1], pointIndexCounter, curFace.point_indexes[2]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[2]};
                    pointIndexCounter += 2;
                } else if (pointsOutside[0] == &point2) {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, curFace.point_indexes[2]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[2]};
                    pointIndexCounter += 2;
                } else {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, curFace.point_indexes[1]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[1]};
                    pointIndexCounter += 2;
                }
                toClipExtra.push_back(newFaceA);
                toClipExtra.push_back(newFaceB);
            }
        } else toClipExtra.push_back(curFace);
    }

    toClip = toClipExtra;
    toClipExtra.clear();

    dVal = left;
    for (auto &curFace : toClip) {
        Vector3D point1 = fig.points[curFace.point_indexes[0]];
        Vector3D point2 = fig.points[curFace.point_indexes[1]];
        Vector3D point3 = fig.points[curFace.point_indexes[2]];

        if ((-point1.x*dNear)/point1.z < dVal || (-point2.x*dNear)/point2.z < dVal || (-point3.x*dNear)/point3.z < dVal) {
            std::vector<Vector3D *> pointsOutside;
            std::vector<Vector3D *> pointsInside;
            if ((-point1.x*dNear)/point1.z < dVal) pointsOutside.push_back(&point1);
            else pointsInside.push_back(&point1);
            if ((-point2.x*dNear)/point2.z < dVal) pointsOutside.push_back(&point2);
            else pointsInside.push_back(&point2);
            if ((-point3.x*dNear)/point3.z < dVal) pointsOutside.push_back(&point3);
            else pointsInside.push_back(&point3);

            Vector3D *A;
            Vector3D *B;
            Vector3D *C;

            if (pointsOutside.size() == 2) {
                A = pointsInside[0];
                B = pointsOutside[0];
                C = pointsOutside[1];
            } else if (pointsInside.size() == 2) {
                A = pointsOutside[0];
                B = pointsInside[0];
                C = pointsInside[1];
            } else {
                continue;
            }

            const double p1 = (B->x * dNear + B->z * dVal) / ((B->x - A->x) * dNear + (B->z - A->z) * dVal);
            const double p2 = (C->x * dNear + C->z * dVal) / ((C->x - A->x) * dNear + (C->z - A->z) * dVal);
            Vector3D newA = p1 * *A + (1 - p1) * *B;
            Vector3D newB = p2 * *A + (1 - p2) * *C;

            fig.points.push_back(newA);
            fig.points.push_back(newB);

            if (pointsOutside.size() == 2) {
                Face newFaceA;
                if (pointsInside[0] == &point1) {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                } else if (pointsInside[0] == &point2) {
                    newFaceA.point_indexes = {curFace.point_indexes[1], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                } else {
                    newFaceA.point_indexes = {curFace.point_indexes[2], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                }
                toClipExtra.push_back(newFaceA);
            }

            if (pointsInside.size() == 2) {
                Face newFaceA;
                Face newFaceB;
                if (pointsOutside[0] == &point1) {
                    newFaceA.point_indexes = {curFace.point_indexes[1], pointIndexCounter, curFace.point_indexes[2]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[2]};
                    pointIndexCounter += 2;
                } else if (pointsOutside[0] == &point2) {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, curFace.point_indexes[2]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[2]};
                    pointIndexCounter += 2;
                } else {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, curFace.point_indexes[1]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[1]};
                    pointIndexCounter += 2;
                }
                toClipExtra.push_back(newFaceA);
                toClipExtra.push_back(newFaceB);
            }
        } else toClipExtra.push_back(curFace);
    }

    toClip = toClipExtra;
    toClipExtra.clear();

    dVal = right;
    for (auto &curFace : toClip) {
        Vector3D point1 = fig.points[curFace.point_indexes[0]];
        Vector3D point2 = fig.points[curFace.point_indexes[1]];
        Vector3D point3 = fig.points[curFace.point_indexes[2]];

        if ((-point1.x*dNear)/point1.z > dVal || (-point2.x*dNear)/point2.z > dVal || (-point3.x*dNear)/point3.z > dVal) {
            std::vector<Vector3D *> pointsOutside;
            std::vector<Vector3D *> pointsInside;
            if ((-point1.x*dNear)/point1.z > dVal) pointsOutside.push_back(&point1);
            else pointsInside.push_back(&point1);
            if ((-point2.x*dNear)/point2.z > dVal) pointsOutside.push_back(&point2);
            else pointsInside.push_back(&point2);
            if ((-point3.x*dNear)/point3.z > dVal) pointsOutside.push_back(&point3);
            else pointsInside.push_back(&point3);

            Vector3D *A;
            Vector3D *B;
            Vector3D *C;

            if (pointsOutside.size() == 2) {
                A = pointsInside[0];
                B = pointsOutside[0];
                C = pointsOutside[1];
            } else if (pointsInside.size() == 2) {
                A = pointsOutside[0];
                B = pointsInside[0];
                C = pointsInside[1];
            } else {
                continue;
            }

            const double p1 = (B->x * dNear + B->z * dVal) / ((B->x - A->x) * dNear + (B->z - A->z) * dVal);
            const double p2 = (C->x * dNear + C->z * dVal) / ((C->x - A->x) * dNear + (C->z - A->z) * dVal);
            Vector3D newA = p1 * *A + (1 - p1) * *B;
            Vector3D newB = p2 * *A + (1 - p2) * *C;

            fig.points.push_back(newA);
            fig.points.push_back(newB);

            if (pointsOutside.size() == 2) {
                Face newFaceA;
                if (pointsInside[0] == &point1) {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                } else if (pointsInside[0] == &point2) {
                    newFaceA.point_indexes = {curFace.point_indexes[1], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                } else {
                    newFaceA.point_indexes = {curFace.point_indexes[2], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                }
                toClipExtra.push_back(newFaceA);
            }

            if (pointsInside.size() == 2) {
                Face newFaceA;
                Face newFaceB;
                if (pointsOutside[0] == &point1) {
                    newFaceA.point_indexes = {curFace.point_indexes[1], pointIndexCounter, curFace.point_indexes[2]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[2]};
                    pointIndexCounter += 2;
                } else if (pointsOutside[0] == &point2) {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, curFace.point_indexes[2]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[2]};
                    pointIndexCounter += 2;
                } else {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, curFace.point_indexes[1]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[1]};
                    pointIndexCounter += 2;
                }
                toClipExtra.push_back(newFaceA);
                toClipExtra.push_back(newFaceB);
            }
        } else toClipExtra.push_back(curFace);
    }

    toClip = toClipExtra;
    toClipExtra.clear();

    dVal = bottom;
    for (auto &curFace : toClip) {
        Vector3D point1 = fig.points[curFace.point_indexes[0]];
        Vector3D point2 = fig.points[curFace.point_indexes[1]];
        Vector3D point3 = fig.points[curFace.point_indexes[2]];

        if ((-point1.y*dNear)/point1.z < dVal || (-point2.y*dNear)/point2.z < dVal || (-point3.y*dNear)/point3.z < dVal) {
            std::vector<Vector3D *> pointsOutside;
            std::vector<Vector3D *> pointsInside;
            if ((-point1.y*dNear)/point1.z < dVal) pointsOutside.push_back(&point1);
            else pointsInside.push_back(&point1);
            if ((-point2.y*dNear)/point2.z < dVal) pointsOutside.push_back(&point2);
            else pointsInside.push_back(&point2);
            if ((-point3.y*dNear)/point3.z < dVal) pointsOutside.push_back(&point3);
            else pointsInside.push_back(&point3);

            Vector3D *A;
            Vector3D *B;
            Vector3D *C;

            if (pointsOutside.size() == 2) {
                A = pointsInside[0];
                B = pointsOutside[0];
                C = pointsOutside[1];
            } else if (pointsInside.size() == 2) {
                A = pointsOutside[0];
                B = pointsInside[0];
                C = pointsInside[1];
            } else {
                continue;
            }

            const double p1 = (B->y * dNear + B->z * dVal) / ((B->y - A->y) * dNear + (B->z - A->z) * dVal);
            const double p2 = (C->y * dNear + C->z * dVal) / ((C->y - A->y) * dNear + (C->z - A->z) * dVal);
            Vector3D newA = p1 * *A + (1 - p1) * *B;
            Vector3D newB = p2 * *A + (1 - p2) * *C;

            fig.points.push_back(newA);
            fig.points.push_back(newB);

            if (pointsOutside.size() == 2) {
                Face newFaceA;
                if (pointsInside[0] == &point1) {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                } else if (pointsInside[0] == &point2) {
                    newFaceA.point_indexes = {curFace.point_indexes[1], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                } else {
                    newFaceA.point_indexes = {curFace.point_indexes[2], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                }
                toClipExtra.push_back(newFaceA);
            }

            if (pointsInside.size() == 2) {
                Face newFaceA;
                Face newFaceB;
                if (pointsOutside[0] == &point1) {
                    newFaceA.point_indexes = {curFace.point_indexes[1], pointIndexCounter, curFace.point_indexes[2]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[2]};
                    pointIndexCounter += 2;
                } else if (pointsOutside[0] == &point2) {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, curFace.point_indexes[2]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[2]};
                    pointIndexCounter += 2;
                } else {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, curFace.point_indexes[1]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[1]};
                    pointIndexCounter += 2;
                }
                toClipExtra.push_back(newFaceA);
                toClipExtra.push_back(newFaceB);
            }
        } else toClipExtra.push_back(curFace);
    }

    toClip = toClipExtra;
    toClipExtra.clear();

    dVal = top;
    for (auto &curFace : toClip) {
        Vector3D point1 = fig.points[curFace.point_indexes[0]];
        Vector3D point2 = fig.points[curFace.point_indexes[1]];
        Vector3D point3 = fig.points[curFace.point_indexes[2]];

        if ((-point1.y*dNear)/point1.z > dVal || (-point2.y*dNear)/point2.z > dVal || (-point3.y*dNear)/point3.z > dVal) {
            std::vector<Vector3D *> pointsOutside;
            std::vector<Vector3D *> pointsInside;
            if ((-point1.y*dNear)/point1.z > dVal) pointsOutside.push_back(&point1);
            else pointsInside.push_back(&point1);
            if ((-point2.y*dNear)/point2.z > dVal) pointsOutside.push_back(&point2);
            else pointsInside.push_back(&point2);
            if ((-point3.y*dNear)/point3.z > dVal) pointsOutside.push_back(&point3);
            else pointsInside.push_back(&point3);

            Vector3D *A;
            Vector3D *B;
            Vector3D *C;

            if (pointsOutside.size() == 2) {
                A = pointsInside[0];
                B = pointsOutside[0];
                C = pointsOutside[1];
            } else if (pointsInside.size() == 2) {
                A = pointsOutside[0];
                B = pointsInside[0];
                C = pointsInside[1];
            } else {
                continue;
            }

            const double p1 = (B->y * dNear + B->z * dVal) / ((B->y - A->y) * dNear + (B->z - A->z) * dVal);
            const double p2 = (C->y * dNear + C->z * dVal) / ((C->y - A->y) * dNear + (C->z - A->z) * dVal);
            Vector3D newA = p1 * *A + (1 - p1) * *B;
            Vector3D newB = p2 * *A + (1 - p2) * *C;

            fig.points.push_back(newA);
            fig.points.push_back(newB);

            if (pointsOutside.size() == 2) {
                Face newFaceA;
                if (pointsInside[0] == &point1) {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                } else if (pointsInside[0] == &point2) {
                    newFaceA.point_indexes = {curFace.point_indexes[1], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                } else {
                    newFaceA.point_indexes = {curFace.point_indexes[2], pointIndexCounter, pointIndexCounter + 1};
                    pointIndexCounter += 2;
                }
                newFaces.push_back(newFaceA);
            }

            if (pointsInside.size() == 2) {
                Face newFaceA;
                Face newFaceB;
                if (pointsOutside[0] == &point1) {
                    newFaceA.point_indexes = {curFace.point_indexes[1], pointIndexCounter, curFace.point_indexes[2]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[2]};
                    pointIndexCounter += 2;
                } else if (pointsOutside[0] == &point2) {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, curFace.point_indexes[2]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[2]};
                    pointIndexCounter += 2;
                } else {
                    newFaceA.point_indexes = {curFace.point_indexes[0], pointIndexCounter, curFace.point_indexes[1]};
                    newFaceB.point_indexes = {pointIndexCounter, pointIndexCounter + 1, curFace.point_indexes[1]};
                    pointIndexCounter += 2;
                }
                newFaces.push_back(newFaceA);
                newFaces.push_back(newFaceB);
            }
        } else newFaces.push_back(curFace);
    }

    fig.faces = newFaces;
}
