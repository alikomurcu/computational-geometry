#include <iostream>

struct Point2D {
    double x, y;
};

struct Point3D {
    double x, y, z;
};

// Returns x-value of point of intersection of two lines
double intersectX(double x1, double y1, double x2, double y2,
                double x3, double y3, double x4, double y4)
{
    double num = (x1*y2 - y1*x2) * (x3-x4) -
              (x1-x2) * (x3*y4 - y3*x4);
    double den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

// Returns y-value of point of intersection of two lines
double intersectY(double x1, double y1, double x2, double y2,
                double x3, double y3, double x4, double y4)
{
    double num = (x1*y2 - y1*x2) * (y3-y4) -
              (y1-y2) * (x3*y4 - y3*x4);
    double den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}
