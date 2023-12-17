#pragma once
#include <vector>
#include "Vector2.h"
#include "RotationMatrix.h"

class Collision
{
public:
	bool collides = false;
	Vector2 col_point1;
	Vector2 col_point2;


	Collision()
		: col_point1(Vector2()), col_point2(Vector2())
	{
	}
	Collision(Vector2 col_point1,Vector2 col_point2)
		: col_point1(col_point1), col_point2(col_point2)
	{
	}
};


class Polygon
{
public:
	Polygon();
	Polygon(std::vector<Vector2> vertices);
	std::vector<Vector2> vertices;
	Vector2 mean;
	double avg_radius;
	double max_radius;

	void MoveTo(Vector2 mean_position);
	void MoveBy(Vector2 offset);
	void RotateBy(double radians);
	std::vector<Vector2> PerimeterPoints(double stepsize);

	std::pair<bool, Vector2> Contains(Vector2 point);
	Collision CollidesWith(Polygon other);

	static Polygon Circle(double radius, int vertices);

};
