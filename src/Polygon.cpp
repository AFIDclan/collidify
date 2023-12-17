#include "Polygon.h"
#include <iostream>


using namespace std;

Polygon::Polygon()
{
}

Polygon::Polygon(std::vector<Vector2> _vertices)
{

	vertices = _vertices;

	mean = Vector2();
	avg_radius = 0;
	for (Vector2& vec : vertices)
		mean = mean + vec;
		

	mean = mean / vertices.size();

	for (Vector2& vec : vertices)
	{
		double radius = (vec - mean).Magnitude();
		avg_radius += radius;
		max_radius = max(max_radius, radius);
	}
		

	avg_radius /= vertices.size();



}

void Polygon::MoveTo(Vector2 mean_position)
{

	Vector2 diff = mean_position - mean;

	MoveBy(diff);

}

void Polygon::MoveBy(Vector2 offset)
{
	for (Vector2& vec : vertices)
		vec = vec + offset;

	mean = mean + offset;
}

void Polygon::RotateBy(double radians)
{
	for (Vector2& vec : vertices)
	{
		Vector2 offset_vec = vec - mean;
		Vector2 rotated_vec = RotationMatrix::Apply(radians, offset_vec);
		vec = mean + rotated_vec;
	}
}

vector<Vector2> Polygon::PerimeterPoints(double stepsize)
{
	vector<Vector2> out;
	for (int i = 0; i < vertices.size(); i++)
	{
		int next_index = i + 1;

		if (next_index == vertices.size())
			next_index = 0;

		Vector2 edge_vec = vertices[next_index] - vertices[i];
		Vector2 edge_normalized = edge_vec.Normalize();

		double edge_length = edge_vec.Magnitude();

		for (double chi = 0; chi < edge_length; chi += stepsize)
		{
			out.push_back(vertices[i] + (edge_normalized * chi));
		}
	}

	return out;
}

pair<bool, Vector2> Polygon::Contains(Vector2 point)
{
	double closest_dist = 1e10;
	Vector2 closest_edge_point;
	for (int i = 0; i < vertices.size(); i++)
	{
		int next_index = i + 1;

		if (next_index == vertices.size())
			next_index = 0;

		Vector2 edge_vec = vertices[next_index] - vertices[i];
		Vector2 query_vec = point - vertices[i];


		double sign = (edge_vec.x * query_vec.y) - (edge_vec.y * query_vec.x);

		if (sign < 0)
			return make_pair(false, Vector2());

		Vector2 edge_vec_norm = edge_vec.Normalize();


		double edge_length = edge_vec_norm.Dot(query_vec);
		
		if (edge_length > 0 && edge_length < edge_vec.Magnitude())
		{
			Vector2 closest_point = vertices[i] + (edge_vec_norm * edge_length);

			double dist = (closest_point - point).Magnitude();

			if (dist < closest_dist)
			{
	
				closest_edge_point = closest_point;
				closest_dist = dist;
			}
		}
	
	}

	return make_pair(true, closest_edge_point);


}

Collision Polygon::CollidesWith(Polygon other)
{

	Collision collision;
	vector<Collision> all_collisions;

	//Preliminary check

	double dist = (other.mean - mean).Magnitude();

	if (dist > max_radius + other.max_radius)
		return collision;

	for (Vector2 check_point : other.vertices)
	{
		auto contains = Contains(check_point);

		if (contains.first)
			all_collisions.push_back(Collision(check_point, contains.second));
		
	}

	for (Vector2 check_point : vertices)
	{
		auto contains = other.Contains(check_point);

		if (contains.first)
			all_collisions.push_back(Collision(contains.second, check_point));

	}

	for (int i=0;i<all_collisions.size();i++)
	{
		Collision c = all_collisions[i];

		if (i == 0)
		{
			collision = c;
		}
		else {
			collision.col_point1 = collision.col_point1 + c.col_point1;
			collision.col_point2 = collision.col_point2 + c.col_point2;
		}
	}

	collision.col_point1 = collision.col_point1 / all_collisions.size();
	collision.col_point2 = collision.col_point2 / all_collisions.size();
	collision.collides = all_collisions.size() > 0;
	return collision;
}

Polygon Polygon::Circle(double radius, int vertices)
{

	std::vector<Vector2> vert;

	for (int i = 1; i <= vertices; i++)
	{
		double theta = (3.141592 * 2 / vertices) * i;

		vert.push_back(Vector2(cos(theta) * radius, sin(theta) * radius));
	}

	return Polygon(vert);
}


