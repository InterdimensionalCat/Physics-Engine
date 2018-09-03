#include "Polygon.h"
#include <iostream>



Polygon::Polygon(std::vector<Vec2D>* vertices, int vertexCount)
{
	Polygon::vertices.resize(20);
	normals.resize(20);

	Polygon::vertexCount = vertexCount;
	for (int i = 0; i < vertexCount; i++) {
		Polygon::vertices.at(i) = vertices->at(i);
	}

	for (int i1 = 0; i1 < vertexCount; ++i1)
	{
		int i2 = i1 + 1 < vertexCount ? i1 + 1 : 0;
		Vec2D face = Vec2D(vertices->at(i2).x - vertices->at(i1).x, vertices->at(i2).y - vertices->at(i1).y);


		// Calculate normal with 2D cross product between vector and scalar
		normals[i1] = Vec2D(face.y, -face.x);
		normals[i1] = normalize(normals[i1]);
	}

}


Polygon::~Polygon()
{

}

// The extreme point along a direction within a polygon
Vec2D Polygon::getSupport(const Vec2D& dir)
{
	float bestProjection = -FLT_MAX;
	Vec2D bestVertex;

	normalize(dir);

	for (int i = 0; i < vertices.size(); ++i)
	{
		Vec2D v = vertices[i];
		float projection = dotProd(v, dir);

		if (projection > bestProjection)
		{
			bestVertex = v;
			bestProjection = projection;
		}
	}

	return bestVertex;
}

float FindAxisLeastPenetration(int *faceIndex, Polygon* A, Polygon* B)
{
	float bestDistance = -FLT_MAX;
	int bestIndex;

	for (int i = 0; i < A->vertexCount; ++i)
	{
		// Retrieve a face normal from A
		Vec2D n = A->normals[i];

		// Retrieve support point from B along -n
		Vec2D s = B->getSupport(Vec2D(-n.x, -n.y));

		// Retrieve vertex on face from A, transform into
		// B's model space
		Vec2D v = A->vertices[i];

		// Compute penetration distance (in B's model space)
		float d = dotProd(n, Vec2D(s.x - v.x, s.y - v.y));

		// Store greatest distance
		if (d > bestDistance)
		{
			bestDistance = d;
			bestIndex = i;
		}
	}

	if (bestDistance == -FLT_MAX) {
		std::cout << "WTF" << std::endl;
	}

	*faceIndex = bestIndex;
	return bestDistance;
}
