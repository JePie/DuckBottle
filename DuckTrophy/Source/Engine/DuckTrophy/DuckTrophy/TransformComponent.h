#pragma once
#include "Component.h"
class TransformComponent :public Component
{
public:
	TransformComponent();
	~TransformComponent();
	sf::Transformable transform;
	void move(float x, float y);
	void rotation(float x);
	void scale(float x, float y);
};

