#include "Circle.h"




Circle::Circle(float radius, Vec2D position)
{
	Circle::radius = radius;
	Circle::position = position;
}


Circle::~Circle()
{

}

bool CirclevsCircleOptimized(Circle a, Circle b)
{
	float r = a.radius + b.radius;
	return r > Distance(a.position, b.position);
}

//bool CirclevsCircle(Manifold *m)
//{
//	// Setup a couple pointers to each object
//	RigidCircle* A = m->A;
//	RigidCircle* B = m->B;
//
//	//Check for collision
//	float r = A->body->radius + B->body->radius;
//	float d = Distance(A->body->position, B->body->position);
//	if (!(r > d)) {
//		return false;
//	}
//
//
//	// Vector from A to B
//	Vec2D n(A->body->position.x - B->body->position.x, A->body->position.y - B->body->position.y);
//
//	//float r = A->body->radius + B->body->radius;
//	//r *= r;
//	//if (!(r > Distance(A->body->position, B->body->position)))
//	//	return false;
//
//	//if (!r > pow(magnitude(n), 2))
//	//	return false;
//
//	// Circles have collided, now compute manifold
//	//float d = magnitude(n); // perform actual sqrt
//
//	// If distance between circles is not zero
//	if (d != 0) {
//		// Distance is difference between radius and distance
//		m->penetration = r - d;
//
//		// Utilize our d since we performed sqrt on it already within Length( )
//		// Points from A to B, and is a unit vector
//		//m->normal = Vec2D(n.x / d, n.y / d);
//		m->normal = normalize(n);
//		return true;
//	} else {
//	    // Circles are on same position
//	    // Choose random (but consistent) values
//		m->penetration = A->body->radius;
//		m->normal = Vec2D(1, 0);
//		return true;
//	}
//}
