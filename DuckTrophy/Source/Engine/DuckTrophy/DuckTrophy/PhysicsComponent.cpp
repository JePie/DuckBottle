#include "pch.h"
#include "PhysicsComponent.h"
bool PhysicsComponent::AABBvsAABB(AABB a, AABB b) {
	{
		if (a.max.x < b.min.x or a.min.x > b.max.x) return false;
		if (a.max.y < b.min.y or a.min.y > b.max.y) return false;
		return true;
	}
}

void PhysicsComponent::setAABB(GameObject &A)
{
	aabb.min = sf::Vector2f(A.centerX - A.sprite.getGlobalBounds().width, A.centerY - A.sprite.getGlobalBounds().height);
	aabb.max = sf::Vector2f(A.centerX + A.sprite.getGlobalBounds().width, A.centerY + A.sprite.getGlobalBounds().height);
}

float PhysicsComponent::Distance(sf::Vector2f a, sf::Vector2f b) {

		float x = a.x - b.x;
		pow(x,2);
		float y = a.y - b.y;
		pow(y, 2);
		return x+y;
}

bool PhysicsComponent::CirclevsCircleUnoptimized(Circle a, Circle b)
{
	float r = a.radius + b.radius;
	return r < Distance(a.position, b.position);
}

//bool PhysicsComponent::CirclevsCircleOptimized(Circle a, Circle b)
//{
//	float r = a.radius + b.radius;
//	r *= r;
//
//	float x = a.x - b.x;
//	pow(x, 2);
//	float y = a.y - b.y;
//	pow(y, 2);
//
//	return r <x+y;
//}
float PhysicsComponent::dotprodcut(const sf::Vector2f &v, const sf::Vector2f &w)
{
	return v.x*w.x + v.y*w.y;
}


float magnitude(const sf::Vector2f &v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

float angle(const sf::Vector2f &v)
{
	float pi = 3.14159265359;
	if (v.x == 0)
	{
		if (v.y < 0) return 270;
		return 90;
	}

	float angle = atan(v.y / v.x) * 180 / pi;
	if (v.x < 0) angle += 180;
	else if (v.y < 0) angle += 360;

	return angle;
}

sf::RectangleShape PhysicsComponent::get_rectangleShape(GameObject &A) const
{
	const sf::Texture *pTexture = &A.actorTexture;

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(100, 100));
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(A.getPosition().x, A.getPosition().y);
	rectangle.setTexture(pTexture);
	
	return rectangle;
}

void PhysicsComponent::ResolveCollision(GameObject &A, GameObject &B)
{
	float minBounce = std::min(A.bounciness, B.bounciness);
	sf::Vector2f rv = B.velocity - A.velocity;

	float velAlongNormal = dotprodcut(rv, collisionNormal);

	if (velAlongNormal > 0)
		return;
	float j = -(1 + minBounce) * velAlongNormal;
	j /= 1 / A.mass + 1 / B.mass;
	sf::Vector2f impulse = j * collisionNormal;
	A.velocity -= 1 / A.mass * impulse;
	B.velocity += 1 / B.mass * impulse;
}
 
void PhysicsComponent::checkCollision(GameObject &A, GameObject &B) {
	float m = A.mass;
	float n = B.mass;
	sf::Vector2f vA = A.velocity;
	sf::Vector2f vB = B.velocity;

	sf::Vector2f x1 = A.getPosition();
	sf::Vector2f x2 = B.getPosition();


	if (x1 != x2)
	{
		if (dotprodcut(vB - vA, x2 - x1) < 0)
		{

			sf::Vector2f pr = (vB - vA, x2 - x1);
			A.velocity = vA + 2 * n / (m + n)*pr;
			B.velocity = vB - 2 * m / (m + n)*pr;
			collide = true;
		}
	}
		
}
void PhysicsComponent::fall(GameObject &A) {
	if (inAir == true) {
		A.moveObject({ 0, A.velocity.y*gravity.y });
	}
	//player.moveObject({ 0, player.velocity.y*physicsEngine.gravity.y });
	else if (A.sprite.getPosition().y > 500) {
			inAir = false;
	}
	else 
	{
		inAir = true;
	}
}
