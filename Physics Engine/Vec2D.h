#pragma once
#include <cmath>


struct Vec2D
{
public:
	Vec2D(float x, float y);
	Vec2D();
	~Vec2D();
	float x;
	float y;
};

float Distance(Vec2D a, Vec2D b);
float dotProd(Vec2D a, Vec2D b);
Vec2D normalize(Vec2D vecIn);
float magnitude(Vec2D vecIn);

float CrossProduct(const Vec2D& a, const Vec2D& b);
Vec2D CrossProduct(const Vec2D& a, float s);
Vec2D CrossProduct(float s, const Vec2D& a);
float Average(float a, float b);

