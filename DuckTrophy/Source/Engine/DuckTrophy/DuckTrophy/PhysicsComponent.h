#pragma once

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Component.h"
#include <math.h>
#include <complex> 

float magnitude(const sf::Vector2f &v);

class PhysicsComponent :public Component
{
public:
	
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
	sf::Vector2f pt1;
	sf::Vector2f pt2;
	sf::Vector2f velocity_l;
	sf::Vector2f velocity_2;

	float pi = 3.14159265359;

	float thickness = 1.0f;
	bool inAir;
	sf::Vector2f gravity = sf::Vector2f(0, 9.8);

	sf::Vector2f collisionNormal;

	bool collide;

	float get_length() const { return magnitude(velocity_l); }

	void fall(GameObject &A);

	sf::Clock clock;

	void setAABB(GameObject &A);

	bool AABBvsAABB(AABB a, AABB b);

	float Distance(sf::Vector2f a, sf::Vector2f b);

	float dotprodcut(const sf::Vector2f &v, const sf::Vector2f &w);

	bool CirclevsCircleUnoptimized(Circle a, Circle b);

	//bool CirclevsCircleOptimized(Circle a, Circle b);

	void ResolveCollision(GameObject &A, GameObject &B);

	void checkCollision(GameObject &A, GameObject &B);

	sf::RectangleShape get_rectangleShape(GameObject &A ) const;
};


