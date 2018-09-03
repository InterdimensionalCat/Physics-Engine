#pragma once
#include<SFML\Graphics.hpp>
#include "Vec2D.h"
#include "Circle.h"
#include <cmath>
#include <iostream>
#include "MassData.h"
#include "Material.h"
#include "Transformer.h"
#include "CollisionShape.h"


class sf::Drawable;
class sf::Transformable;
struct Circle;
class RigidCircle;

class RigidBody : public sf::Drawable, public sf::Transformable
{
public:
	RigidBody(Vec2D startVelocity, float restitution, float mass, float staticFriction, float dynamicFriction);
	~RigidBody();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void onUpdate(float deltaTime);
	virtual void movePos(Vec2D movement);
	Vec2D velocity;
	float restitution;
	float massInv;
	float staticFriction;
	float dynamicFriction;

};


void ResolveCollision(RigidBody* A, RigidBody* B, Vec2D normal, float penetration);
void PositionalCorrection(RigidBody* A, RigidBody* B, Vec2D normal, float penetration);

