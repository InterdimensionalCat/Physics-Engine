#pragma once
#include "RigidBody.h"
class RigidSquare : public RigidBody
{
public:
	RigidSquare(Vec2D startVelocity, float restitution, float mass, Vec2D pos, Vec2D size, float staticFriction, float dynamicFriction);
	~RigidSquare();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void onUpdate(float deltaTime);
	virtual void movePos(Vec2D movement);
	AABB* body;
};

