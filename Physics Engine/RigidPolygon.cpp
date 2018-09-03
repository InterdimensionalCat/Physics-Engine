#include "RigidPolygon.h"



RigidPolygon::RigidPolygon(Vec2D startVelocity, float restitution, float mass, std::vector<Vec2D>* verticies, int vertexCount, float staticFriction, float dynamicFriction) : RigidBody(startVelocity, restitution, mass, staticFriction, dynamicFriction)
{
	body = new Polygon(verticies, vertexCount);
}


RigidPolygon::~RigidPolygon()
{

}

void RigidPolygon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::ConvexShape drawn(body->vertexCount);
	for (int i = 0; i < body->vertexCount; i++) {
		drawn.setPoint(i, sf::Vector2f(body->vertices[i].x, body->vertices[i].y));
	}
	//drawn.setPosition(sf::Vector2f(body->pos.x, body->pos.y));
	drawn.setOutlineThickness(3);
	drawn.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(drawn);
}

void RigidPolygon::onUpdate(float deltaTime) {
	if (massInv != 0) {
		velocity.y += 0.01* 1 / massInv;
		std::cout << velocity.x << " " << velocity.y << std::endl;
	}

	for (int i = 0; i < body->vertexCount; i++) {
		if (abs(velocity.x) > 0.05) {
			body->vertices[i].x += velocity.x;
		}

		if (abs(velocity.y) > 0.05) {
			body->vertices[i].y += velocity.y;
		}
	}

	//body->pos.x += velocity.x;
	//body->pos.y += velocity.y;
}

void RigidPolygon::movePos(Vec2D movement) {
	for (int i = 0; i < body->vertexCount; i++) {
		body->vertices[i].x += movement.x * massInv;
		body->vertices[i].y += movement.y * massInv;
	}
}
