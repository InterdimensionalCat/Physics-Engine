#include "RigidSquare.h"



RigidSquare::RigidSquare(Vec2D startVelocity, float restitution, float mass, Vec2D pos, Vec2D size, float staticFriction, float dynamicFriction) : RigidBody(startVelocity, restitution, mass, staticFriction, dynamicFriction)
{
	body = new AABB(pos, size);
}


RigidSquare::~RigidSquare()
{

}

void RigidSquare::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::RectangleShape drawn(sf::Vector2f(body->size.x, body->size.y));
	drawn.setPosition(sf::Vector2f(body->pos.x, body->pos.y));
	drawn.setOutlineThickness(3);
	drawn.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(drawn);
}

void RigidSquare::onUpdate(float deltaTime) {
	if (massInv != 0) {
		velocity.y += 0.1;
	}
	body->pos.x += velocity.x;
	body->pos.y += velocity.y;
}

void RigidSquare::movePos(Vec2D movement) {
	body->pos.x += movement.x * massInv;
	body->pos.y += movement.y * massInv;
}
