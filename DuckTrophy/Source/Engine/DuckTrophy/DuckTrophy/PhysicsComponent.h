#pragma once

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Component.h"
#include <math.h>
#include <complex> 
class PhysicsComponent :public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();
	
	struct AABB{
		sf::Vector2f min;
		sf::Vector2f max;
	};
	AABB aabb;
	struct Circle
	{
		float radius;
		sf::Vector2f position;
	};

	bool inAir;
	sf::Vector2f gravity = sf::Vector2f(0, 9.8);

	sf::Vector2f collisionNormal;

	bool collide;

	void fall(Actor A);

	sf::Clock clock;

	void setAABB(Actor A);

	bool AABBvsAABB(AABB a, AABB b);

	float Distance(sf::Vector2f a, sf::Vector2f b);

	float dotprodcut(const sf::Vector2f &v, const sf::Vector2f &w);

	bool CirclevsCircleUnoptimized(Circle a, Circle b);

	//bool CirclevsCircleOptimized(Circle a, Circle b);

	void ResolveCollision(Actor A, Actor B);

	void checkCollision(Actor &A, Actor &B);

};

