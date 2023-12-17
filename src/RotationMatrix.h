#pragma once
#include "Vector2.h"
class RotationMatrix
{
public:
	static Vector2 Apply(double radians, Vector2 in);
};

