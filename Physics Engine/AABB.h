#pragma once
#include "Vec2D.h"
#include "Circle.h"

struct AABB
{
public:
	AABB(Vec2D pos, Vec2D size);
	~AABB();
	Vec2D pos;
	Vec2D size;
};

