#pragma once
#include "Vec2D.h"
#include <cmath>
#include "RigidCircle.h"

class RigidCircle;

struct Manifold //system for calculating penetration and collision normal
{
	Manifold(RigidCircle* A, RigidCircle* B);
	~Manifold();
	RigidCircle* A;
	RigidCircle* B;
	float penetration;
	Vec2D normal;

};

