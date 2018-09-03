#pragma once
#include "Vec2D.h"
#include <vector>

const int maxverticies = 20;

struct Polygon
{
public:
	Polygon(std::vector<Vec2D>* verticies, int vertexCount);
	~Polygon();

	int vertexCount;

	std::vector<Vec2D> vertices;
	std::vector<Vec2D> normals;
	Vec2D getSupport(const Vec2D& dir);
};

float FindAxisLeastPenetration(int *faceIndex, Polygon* A, Polygon* B);

