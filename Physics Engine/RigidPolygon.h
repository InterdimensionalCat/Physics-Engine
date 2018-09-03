#pragma once
#include "RigidBody.h"
#include "polygon.h"

class RigidPolygon : public RigidBody
{
public:
	RigidPolygon(Vec2D startVelocity, float restitution, float mass, std::vector<Vec2D>* verticies, int vertexCount, float staticFriction, float dynamicFriction);
	~RigidPolygon();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void onUpdate(float deltaTime);
	virtual void movePos(Vec2D movement);
	Polygon* body;
};

