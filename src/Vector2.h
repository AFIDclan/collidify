#pragma once

#include <cmath>

class Vector2
{
public:
	Vector2();
	Vector2(double x, double y);

	double x=0;
	double y=0;

	double Magnitude();
	double Dot(Vector2 other);
	Vector2 Normalize();
	Vector2 Clone();
	
	Vector2 operator+(Vector2 const& other)
	{
		return Vector2(x+other.x, y+other.y);
	}

	Vector2 operator-(Vector2 const& other)
	{
		return Vector2(x - other.x, y - other.y);
	}


	Vector2 operator+(double const& scalar)
	{
		return Vector2(x + scalar, y + scalar);
	}

	Vector2 operator-(double const& scalar)
	{
		return Vector2(x - scalar, y - scalar);
	}

	Vector2 operator*(double const& scalar)
	{
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator/(double const& scalar)
	{
		return Vector2(x / scalar, y / scalar);
	}

};

