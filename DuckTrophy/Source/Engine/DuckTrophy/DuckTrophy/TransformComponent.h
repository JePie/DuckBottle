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

	sf::Transformable transform;

	void moveObject(float x, float y);
	void rotateObject(float x);
	void scaleObject(float x, float y);

};

