#pragma once
#include "Component.h"
#include "Vector2.h"

class TransformComponent : Component
{
public:
	//Check
	TransformComponent() : position(), rotation(), scale(1.0f, 1.0f) {}
	void Start();
	void Update();

	sf::Transform transformMatrix;
	Vector2 position;
	Vector2 rotation;
	Vector2 scale;
	sf::Clock clock;
	sf::Time dt = clock.restart();

	//Actor a;
	//void moveObject(sf::Vector2f m);
	//void rotateObject(float x);
	//void Scale(sf::Vector2f m);
	//void UpdateTransform(float dtAsSec);
};

