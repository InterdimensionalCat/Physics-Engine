#include "RigidBody.h"




RigidBody::RigidBody(Vec2D startVelocity, float restitution, float mass, float staticFriction, float dynamicFriction)
{
	velocity = startVelocity;
	RigidBody::restitution = restitution;
	if (mass == 0) {
		massInv = 0;
	} else {
		massInv = 1 / mass;
	}

	RigidBody::staticFriction = staticFriction;
	RigidBody::dynamicFriction = dynamicFriction;
}

//void ResolveCollision(RigidBody* A, RigidBody* B, Vec2D normal, float penetration)
//{
//	// Calculate relative velocity
//	Vec2D reletiveVelocity(B->velocity.x - A->velocity.x, B->velocity.y - A->velocity.y);
//
//
//	// Calculate relative velocity in terms of the normal direction
//	float velAlongNormal = dotProd(reletiveVelocity, normal);
//
//	// Do not resolve if velocities are separating
//	if (-velAlongNormal > 0) //should be  a >, but works with < (vel should be positive)
//		return;
//
//	// Calculate restitution
//	float e = std::min(A->restitution, B->restitution);
//
//	// Calculate impulse scalar
//	float j = -(1 + e) * velAlongNormal;
//	j /= A->massInv + B->massInv;
//
//	// Apply impulse
//	Vec2D impulse(j * normal.x, j * normal.y);
//
//	A->velocity.x -= A->massInv * impulse.x;
//	A->velocity.y -= A->massInv * impulse.y;
//	B->velocity.x += B->massInv * impulse.x;
//	B->velocity.y += B->massInv * impulse.y;
//
//	//Correct for sinking
//
//	PositionalCorrection(A, B, normal, penetration);
//}

void ResolveCollision(RigidBody* A, RigidBody* B, Vec2D normal, float penetration)
{
	// Calculate relative velocity
	Vec2D reletiveVelocity(B->velocity.x - A->velocity.x, B->velocity.y - A->velocity.y);


	// Calculate relative velocity in terms of the normal direction
	float velAlongNormal = dotProd(reletiveVelocity, normal);

	// Do not resolve if velocities are separating
	if (-velAlongNormal > 0) //should be  a >, but works with < (vel should be positive)
		return;

	// Calculate restitution
	float e = std::min(A->restitution, B->restitution);

	// Calculate impulse scalar
	float j = -(1 + A->restitution) * velAlongNormal;
	float i = -(1 + B->restitution) * velAlongNormal;
	j /= A->massInv + B->massInv;
	i /= A->massInv + B->massInv;

	// Apply impulse
	Vec2D impulse(j * normal.x, j * normal.y);
	Vec2D impulseb(i * normal.x, i * normal.y);

	A->velocity.x -= A->massInv * impulse.x;
	A->velocity.y -= A->massInv * impulse.y;
	B->velocity.x += B->massInv * impulseb.x;
	B->velocity.y += B->massInv * impulseb.y;

	//Correct for sinking

	PositionalCorrection(A, B, normal, penetration);

	reletiveVelocity = Vec2D(B->velocity.x - A->velocity.x, B->velocity.y - A->velocity.y);

	if (abs(magnitude(reletiveVelocity)) == 0) return;

	Vec2D tangent = Vec2D(reletiveVelocity.x - dotProd(reletiveVelocity, normal) * normal.x, reletiveVelocity.y - dotProd(reletiveVelocity, normal) * normal.y);
	tangent = normalize(tangent);

	//float velAlongNormal = dotProd(reletiveVelocity, normal);


	float jt = -dotProd(reletiveVelocity, tangent);
	jt = jt / (A->massInv + B->massInv);

	float mu = Average(A->staticFriction, B->staticFriction);
	Vec2D frictionImpulse;
	Vec2D frictionImpulseb;

	if (jt == 0) {
		return;
	}

	if (abs(jt) < j * mu)
		frictionImpulse = Vec2D(jt * tangent.x, jt * tangent.y);
	else
	{
		float dynamicFriction = Average(A->dynamicFriction, B->dynamicFriction);
		frictionImpulse = Vec2D(j * tangent.x * dynamicFriction, j * tangent.y * dynamicFriction);
	}

	if (abs(jt) < i * mu)
		frictionImpulseb = Vec2D(jt * tangent.x, jt * tangent.y);
	else
	{
		float dynamicFriction = Average(A->dynamicFriction, B->dynamicFriction);
		frictionImpulseb = Vec2D(i * tangent.x * dynamicFriction, i * tangent.y * dynamicFriction);
	}


	// Apply
	A->velocity.x -= A->massInv * frictionImpulse.x;
	A->velocity.y -= A->massInv * frictionImpulse.y;
	B->velocity.x += B->massInv * frictionImpulseb.x;
	B->velocity.y += B->massInv * frictionImpulseb.y;
}


void PositionalCorrection(RigidBody* A, RigidBody* B, Vec2D normal, float penetration)
{
	const float percent = 0.8; // usually 20% to 80%
	const float slop = 0.01;// usually 0.01 to 0.1
	float correctionFloat = std::max(penetration - slop, 0.0f) / (A->massInv + B->massInv);
	Vec2D correction = Vec2D(correctionFloat* normal.x, correctionFloat* normal.y);

	A->movePos(correction);

	correction.x *= -1;
	correction.y *= -1;

	B->movePos(correction);

	//m->A->body->position.x += m->A->massInv * correction.x;
	//m->A->body->position.y += m->A->massInv * correction.y;
	//m->B->body->position.x -= m->B->massInv * correction.x;
	//m->B->body->position.y -= m->B->massInv * correction.y;
}


RigidBody::~RigidBody()
{

}

void RigidBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {

}

void RigidBody::onUpdate(float deltaTime) {

}

void RigidBody::movePos(Vec2D movement) {

}
