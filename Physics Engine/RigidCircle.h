#pragma once
#include "RigidBody.h"

class RigidBody;

class RigidCircle : public RigidBody
{
public:
	RigidCircle(Vec2D startVelocity, float restitution, float mass, float radius, Vec2D position, float staticFriction, float dynamicFriction);
	~RigidCircle();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void onUpdate(float deltaTime);
	virtual void movePos(Vec2D movement);
	Circle* body;
};

