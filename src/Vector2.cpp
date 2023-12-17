#include "Vector2.h"


Vector2::Vector2()
{
    x = 0;
    y = 0;
}
Vector2::Vector2(double _x, double _y)
{
    x = _x;
    y = _y;
}

double Vector2::Magnitude()
{
    return sqrt(x*x+y*y);
}

double Vector2::Dot(Vector2 other)
{
    return x * other.x + y * other.y;
}

Vector2 Vector2::Normalize()
{
    double m = Magnitude();

    if (m == 0)
        return Vector2(0, 0);

    return Vector2(x / m, y / m);
}

Vector2 Vector2::Clone()
{
    return Vector2(x, y);
}

