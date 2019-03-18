#include "pch.h"
#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent()
{
}


PhysicsComponent::~PhysicsComponent()
{
}
bool PhysicsComponent::AABBvsAABB(AABB a, AABB b) {
	{
		if (a.max.x < b.min.x or a.min.x > b.max.x) return false;
		if (a.max.y < b.min.y or a.min.y > b.max.y) return false;
		return true;
	}
}

void PhysicsComponent::setAABB(Actor A)
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

void PhysicsComponent::ResolveCollision(Actor A, Actor B)
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

sf::RectangleShape PhysicsComponent::get_rectangleShape(Actor &A) const
{
	sf::RectangleShape rect(sf::Vector2f(get_length(), 2 * thickness));
	rect.setOrigin(0, thickness);
	rect.setPosition(A.getPosition());
	rect.setRotation(angle(velocity_l));
	rect.setFillColor(sf::Color(0,0,1));

	return rect;
}

void PhysicsComponent::checkCollision(Actor &A, Actor &B) {
	float m = A.mass;
	float n = B.mass;
	sf::Vector2f vA = A.velocity;
	sf::Vector2f vB = B.velocity;

	sf::Vector2f x1 = A.getPosition();
	sf::Vector2f x2 = B.getPosition();

	sf::FloatRect boundingBoxA = A.sprite.getGlobalBounds();
	sf::FloatRect boundingBoxB = B.sprite.getGlobalBounds();

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
	else if (boundingBoxA.intersects(boundingBoxB)) {
		B.velocity = sf::Vector2f(0, 0);
		ResolveCollision(A, B);
		collide = true;
	}
	else {
		collide = false;
	}
		
}
void PhysicsComponent::fall(Actor &A) {
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

	//if (physicsEngine.inAir == true) {
	//	//player.velocity.y += physicsEngine.gravity.y*timer.getElapsedTime().asSeconds()*10;
	//	player.moveObject({ player.velocity.x, player.velocity.y*timer.getElapsedTime().asSeconds() * 100 });
	//}
	//else if (physicsEngine.inAir &&player.getPosition().y > 150) {
	//	player.velocity = sf::Vector2f(0, 0);
	//	player.setPosition({ 1800,player.velocity.y });
	//	physicsEngine.inAir = false;
	//}
	//else {
	//	physicsEngine.inAir = true;
	//}
}