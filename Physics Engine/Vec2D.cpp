#include "Vec2D.h"




Vec2D::Vec2D(float x, float y)
{
	Vec2D::x = x;
	Vec2D::y = y;
}

Vec2D::Vec2D()
{
	Vec2D::x = 0;
	Vec2D::y = 0;
}

Vec2D::~Vec2D()
{

}

float Average(float a, float b) {
	return sqrt(a * a + b * b);
}

float Distance(Vec2D a, Vec2D b)
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

float dotProd(Vec2D a, Vec2D b) {
	return a.x * b.x + a.y * b.y;
}

Vec2D normalize(Vec2D vecIn) {
	float mag = magnitude(vecIn);
	if (magnitude > 0) {
		vecIn.x /= mag;
		vecIn.y /= mag;
	}

	return vecIn;
}

float magnitude(Vec2D vecIn) {
	return sqrt(pow(vecIn.x, 2) + pow(vecIn.y, 2));
}

// Two crossed vectors return a scalar
float CrossProduct(const Vec2D& a, const Vec2D& b)
{
	return a.x * b.y - a.y * b.x;
}

// More exotic (but necessary) forms of the cross product
// with a vector a and scalar s, both returning a vector
Vec2D CrossProduct(const Vec2D& a, float s)
{
	return Vec2D(s * a.y, -s * a.x);
}

Vec2D CrossProduct(float s, const Vec2D& a)
{
	return Vec2D(-s * a.y, s * a.x);
}
