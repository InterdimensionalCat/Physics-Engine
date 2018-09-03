#include "RigidCircle.h"



RigidCircle::RigidCircle(Vec2D startVelocity, float restitution, float mass, float radius, Vec2D position, float staticFriction, float dynamicFriction) : RigidBody(startVelocity, restitution, mass, staticFriction, dynamicFriction)
{
	body = new Circle(radius, position);
}


RigidCircle::~RigidCircle()
{

}



void RigidCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::CircleShape drawn(body->radius);
	drawn.setOrigin(body->radius, body->radius);
	drawn.setPosition(body->position.x, body->position.y);
	drawn.setOutlineThickness(3);
	drawn.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(drawn);

}

void RigidCircle::movePos(Vec2D movement) { //this function is for positional correction only
	body->position.x += movement.x * massInv;
	body->position.y += movement.y * massInv;
}

void RigidCircle::onUpdate(float deltaTime) {

	if (massInv != 0) {
		velocity.y += 0.1;
	}
	body->position.x += velocity.x;
	body->position.y += velocity.y;

}
