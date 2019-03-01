#pragma once
#include "Component.h"
#include "Vector2.h"

class TransformComponent : Component
{
public:
	TransformComponent() : position(), rotation(), scale(1.0f, 1.0f) {}

	void Start();
	void Update();

	sf::Transform transformMatrix;
	Vector2 position;
	Vector2 rotation;
	Vector2 scale;

	//Check
	sf::Transformable transform;
	void move(float x, float y);
	void rotation(float x);
	void scale(float x, float y);
};

