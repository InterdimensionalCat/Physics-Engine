#pragma once
#include "RigidCircle.h"
#include "RigidBody.h"
#include "RigidSquare.h"
#include "RigidPolygon.h"
#include <algorithm>

bool CircleCollision(RigidCircle* A, RigidCircle* B);
bool AABBCollision(RigidSquare* A, RigidSquare* B);
bool CircleToAABB(RigidCircle* A, RigidSquare* B);
bool PolygontoPolygon(RigidPolygon* A, RigidPolygon* B);
bool BiasGreaterThan(float a, float b);
void FindIncidentFace(Vec2D *v, RigidPolygon* RefPoly, RigidPolygon* IncPoly, int referenceIndex);
int Clip(Vec2D n, float c, Vec2D *face);

