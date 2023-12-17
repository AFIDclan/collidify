#include "RotationMatrix.h"

Vector2 RotationMatrix::Apply(double radians, Vector2 in)
{

    double a1 = cos(radians);
    double a2 = -sin(radians);
    double b1 = sin(radians);
    double b2 = cos(radians);


    return Vector2(in.x*a1+in.y*a2, in.x*b1+in.y*b2);
}
