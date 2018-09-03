#include "CollisionEngine.h"


bool CircleCollision(RigidCircle* A, RigidCircle* B) {


	//Check for collision
	float r = A->body->radius + B->body->radius;
	float d = Distance(A->body->position, B->body->position);

	if (!(r > d)) {
		//Circles have not collided
		return false;
	}

	//Circles have collided

	float penetration;
	Vec2D normal;

	// Vector from A to B
	Vec2D n(A->body->position.x - B->body->position.x, A->body->position.y - B->body->position.y);


	if (d != 0) {

		//Circles are not occupying the same position
		penetration = r - d;
		normal = normalize(n);

	} else {
		// Circles are on same position
		// Choose random (but consistent) values
		penetration = A->body->radius;
		normal = Vec2D(1, 0);

	}

	ResolveCollision(A, B, normal, penetration);
	return true;
}

bool AABBCollision(RigidSquare* A, RigidSquare* B) {

	Vec2D minA = A->body->pos;
	Vec2D minB = B->body->pos;

	Vec2D maxA = Vec2D(A->body->pos.x + A->body->size.x, A->body->pos.y + A->body->size.y);
	Vec2D maxB = Vec2D(B->body->pos.x + B->body->size.x, B->body->pos.y + B->body->size.y);

	Vec2D centerA = Vec2D(A->body->pos.x + A->body->size.x / 2, A->body->pos.y + A->body->size.y / 2);
	Vec2D centerB = Vec2D(B->body->pos.x + B->body->size.x / 2, B->body->pos.y + B->body->size.y / 2);

	Vec2D distance = Vec2D(centerB.x - centerA.x, centerB.y - centerA.y);

	// Calculate half extents along x axis for each object
	float a_extent = (maxA.x - minA.x) / 2;
	float b_extent = (maxB.x - minB.x) / 2;

	// Calculate overlap on x axis
	float x_overlap = a_extent + b_extent - abs(distance.x);

	// SAT test on x axis
	if (x_overlap > 0)
	{
		// Calculate half extents along y axis for each object
		float a_extent = (maxA.y - minA.y) / 2;
		float b_extent = (maxB.y - minB.y) / 2;

		// Calculate overlap on y axis
		float y_overlap = a_extent + b_extent - abs(distance.y);

			// SAT test on y axis
			if (y_overlap > 0)
			{

				//AABB's have collided

				Vec2D normal;
				float penetration;

				// Find out which axis is axis of least penetration
				if (x_overlap < y_overlap)
				{
					// Point towards B knowing that n points from A to B
					if (distance.x < 0) {
						normal = Vec2D(1, 0);
					} else {
						normal = Vec2D(-1, 0);
					}

					penetration = x_overlap;
					//return true;


				} else {
					// Point toward B knowing that n points from A to B
					if (distance.y < 0) {
						normal = Vec2D(0, 1);
					} else {
						normal = Vec2D(0, -1);
					}

					penetration = y_overlap;
					//return true;
				}

				ResolveCollision(A, B, normal, penetration);
				return true;

			}

	}

	return false;
}

bool CircleToAABB(RigidCircle* A, RigidSquare* B) {
	Vec2D minB = B->body->pos;
	Vec2D maxB = Vec2D(B->body->pos.x + B->body->size.x, B->body->pos.y + B->body->size.y);
	Vec2D centerB = Vec2D(B->body->pos.x + B->body->size.x / 2, B->body->pos.y + B->body->size.y / 2);

	Vec2D distance = Vec2D(centerB.x - A->body->position.x, centerB.y - A->body->position.y);
	Vec2D closest = distance;

	float penetration;
	Vec2D normal;

	// Calculate half extents along each axis
	float x_extent = (maxB.x - minB.x) / 2;
	float y_extent = (maxB.y - minB.y) / 2;

	// Clamp point to edges of the AABB
	closest.x = std::clamp(closest.x , -x_extent, x_extent);
	closest.y = std::clamp(closest.y , -y_extent, y_extent);


	bool inside = false;

		// Circle is inside the AABB, so we need to clamp the circle's center
		// to the closest edge
	if (distance.x == closest.x && distance.y == closest.y)
	{
		inside = true;

		// Find closest axis
		if (abs(distance.x) > abs(distance.y))
		{
			// Clamp to closest extent
			if (closest.x > 0) {
				closest.x = x_extent;
			} else {
				closest.x = -x_extent;
			}
		} else {
			// y axis is shorter
			// Clamp to closest extent
			if (closest.y > 0) {
				closest.y = y_extent;
			} else {
				closest.y = -y_extent;
			}
		}
	}

	Vec2D n = Vec2D(distance.x - closest.x, distance.y - closest.y);
	//Vec2D n = Vec2D(A->body->position.x - closest.x, A->body->position.y - closest.y);
	double d = magnitude(n);
	double r = A->body->radius;

	// Early out of the radius is shorter than distance to closest point and
	// Circle not inside the AABB
	if (d > r && !inside) {
		return false;
	}

	// Collision normal needs to be flipped to point outside if circle was
	// inside the AABB
	if (inside)
	{
		normal = normalize(Vec2D(-n.x, n.y));
		penetration = r - d;
	} else {
		normal = normalize(Vec2D(-n.x, -n.y));
		penetration = r - d;
	}

	ResolveCollision(A, B, normal, penetration);

	return true;
}





bool PolygontoPolygon(RigidPolygon* A, RigidPolygon* B)
{

	float penetration;
	Vec2D normal;

	// Check for a separating axis with A's face planes
	int faceA;
	float penetrationA = FindAxisLeastPenetration(&faceA, A->body, B->body);
	if (penetrationA >= 0.0f)
		return false;

	// Check for a separating axis with B's face planes
	int faceB;
	float penetrationB = FindAxisLeastPenetration(&faceB, B->body, A->body);
	if (penetrationB >= 0.0f)
		return false;

	int referenceIndex;
	bool flip; // Always point from a to b

	RigidPolygon *RefPoly; // Reference
	RigidPolygon *IncPoly; // Incident

	// Determine which shape contains reference face
	if (BiasGreaterThan(penetrationA, penetrationB))
	{
		RefPoly = A;
		IncPoly = B;
		referenceIndex = faceA;
		flip = false;
	}

	else
	{
		RefPoly = B;
		IncPoly = A;
		referenceIndex = faceB;
		flip = true;
	}

	// World space incident face
	Vec2D incidentFace[2];
	FindIncidentFace(incidentFace, RefPoly, IncPoly, referenceIndex);

	//        y
	//        ^  ->n       ^
	//      +---c ------posPlane--
	//  x < | i |\
	  //      +---+ c-----negPlane--
//             \       v
//              r
//
//  r : reference face
//  i : incident poly
//  c : clipped point
//  n : incident normal

// Setup reference face vertices
	Vec2D v1 = RefPoly->body->vertices[referenceIndex];
	referenceIndex = referenceIndex + 1 == RefPoly->body->vertexCount ? 0 : referenceIndex + 1;
	Vec2D v2 = RefPoly->body->vertices[referenceIndex];

	// Transform vertices to world space
	//v1 = RefPoly->u * v1 + RefPoly->body->position;
	//v2 = RefPoly->u * v2 + RefPoly->body->position;

	// Calculate reference face side normal in world space
	Vec2D sidePlaneNormal = Vec2D(v2.x - v1.x, v2.y - v1.y);
	sidePlaneNormal = normalize(sidePlaneNormal);

	// Orthogonalize
	Vec2D refFaceNormal(sidePlaneNormal.y, -sidePlaneNormal.x);

	// ax + by = c
	// c is distance from origin
	float refC = dotProd(refFaceNormal, v1);
	float negSide = -dotProd(sidePlaneNormal, v1);
	float posSide = dotProd(sidePlaneNormal, v2);

	// Clip incident face to reference face side planes
	if (Clip(Vec2D(-sidePlaneNormal.x, -sidePlaneNormal.y), negSide, incidentFace) < 2)
		return false; // Due to floating point error, possible to not have required points

	if (Clip(sidePlaneNormal, posSide, incidentFace) < 2)
		return false; // Due to floating point error, possible to not have required points

				// Flip
	normal = flip ? Vec2D(refFaceNormal.x, refFaceNormal.y) : Vec2D(-refFaceNormal.x, -refFaceNormal.y);
	//normalize(normal);

	// Keep points behind reference face
	int cp = 0; // clipped points behind reference face
	float separation = dotProd(refFaceNormal, incidentFace[0]) - refC;
	if (separation <= 0.0f)
	{
		//m->contacts[cp] = incidentFace[0];
		penetration = -separation;
		++cp;
	} else {
		penetration = 0;
	}

	separation = dotProd(refFaceNormal, incidentFace[1]) - refC;
	if (separation <= 0.0f)
	{
		//m->contacts[cp] = incidentFace[1];

		penetration += -separation;
		++cp;

		// Average penetration
		penetration /= (float)cp;
	}

	//m->contact_count = cp;

	ResolveCollision(A, B, normal, penetration);

	return true;

}


 bool BiasGreaterThan(float a, float b)
{
	const float k_biasRelative = 0.95f;
	const float k_biasAbsolute = 0.01f;
	return a >= b * k_biasRelative + a * k_biasAbsolute;
}

 void FindIncidentFace(Vec2D *v, RigidPolygon* RefPoly, RigidPolygon* IncPoly, int referenceIndex)
 {
	 Vec2D referenceNormal = RefPoly->body->normals[referenceIndex];

	 // Calculate normal in incident's frame of reference
	 //referenceNormal = RefPoly->u * referenceNormal; // To world space
	 //referenceNormal = IncPoly->u.Transpose() * referenceNormal; // To incident's model space

	 // Find most anti-normal face on incident polygon
	 int incidentFace = 0;
	 float minDot = FLT_MAX;
	 for (int i = 0; i < IncPoly->body->vertexCount; ++i)
	 {
		 float dot = dotProd(referenceNormal, IncPoly->body->normals[i]);
		 if (dot < minDot)
		 {
			 minDot = dot;
			 incidentFace = i;
		 }
	 }

	 // Assign face vertices for incidentFace
	 v[0] = IncPoly->body->vertices[incidentFace];// +IncPoly->body->position;
	 incidentFace = incidentFace + 1 >= IncPoly->body->vertexCount ? 0 : incidentFace + 1;
	 v[1] = IncPoly->body->vertices[incidentFace];// +IncPoly->body->position;
 }

 int Clip(Vec2D n, float c, Vec2D *face)
 {
	 int sp = 0;
	 Vec2D out[2] = {
		 face[0],
		 face[1]
	 };

	 // Retrieve distances from each endpoint to the line
	 // d = ax + by - c
	 float d1 = dotProd(n, face[0]) - c;
	 float d2 = dotProd(n, face[1]) - c;

	 // If negative (behind plane) clip
	 if (d1 <= 0.0f) out[sp++] = face[0];
	 if (d2 <= 0.0f) out[sp++] = face[1];

	 // If the points are on different sides of the plane
	 if (d1 * d2 < 0.0f) // less than to ignore -0.0f
	 {
		 // Push interesection point
		 float alpha = d1 / (d1 - d2);
		 //out[sp] = face[0] + alpha * (face[1] - face[0]);
		 out[sp] = Vec2D(face[0].x + alpha * (face[1].x - face[0].x), face[0].y + alpha * (face[1].y - face[0].y));
		 ++sp;
	 }

	 // Assign our new converted values
	 face[0] = out[0];
	 face[1] = out[1];

	 return sp;
 }

