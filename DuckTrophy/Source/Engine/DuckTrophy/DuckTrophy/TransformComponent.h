#pragma once
#include "Component.h"
#include "Vector2.h"

class TransformComponent : Component
{
public:
	TransformComponent() : m_Position(), m_Rotation(), m_Scale(1.0f, 1.0f) {}

	void Start();
	void Update();

	sf::Transform transformMatrix;
	Vector2 m_Position;
	Vector2 m_Rotation;
	Vector2 m_Scale;

	//Check
	sf::Transformable transform;
	void move(float x, float y);
	void rotation(float x);
	void scale(float x, float y);
};

