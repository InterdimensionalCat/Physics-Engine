#pragma once
#include "Vec2D.h"
#include <cmath>
#include <iostream>
#include "AABB.h"

struct Manifold;

struct Circle
{
public:
	Circle(float radius, Vec2D position);
	~Circle();
	float radius;
	Vec2D position;
};

bool CirclevsCircleOptimized(Circle a, Circle b);
bool CirclevsCircle(Manifold* m);

