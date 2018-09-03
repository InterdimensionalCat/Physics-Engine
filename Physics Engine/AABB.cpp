#include "AABB.h"


AABB::AABB(Vec2D pos, Vec2D size)
{
	AABB::pos = pos;
	AABB::size = size;
}


AABB::~AABB()
{

}

bool AABBvsAABB(AABB a, AABB b)
{
	// Exit with no intersection if found separated along an axis
	//if (a.max.x < b.min.x or a.min.x > b.max.x) return false;
	//if (a.max.y < b.min.y or a.min.y > b.max.y) return false;

	// No separating axis found, therefor there is at least one overlapping axis
	return true;
}
