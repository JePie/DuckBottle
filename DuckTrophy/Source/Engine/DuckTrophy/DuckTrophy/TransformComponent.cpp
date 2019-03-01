#include "pch.h"
#include "TransformComponent.h"
#include<iostream>

void TransformComponent::Start()
{
	std::cout << "Transform Component Initialized" << std::endl;
}

void TransformComponent::Update()
{
	std::cout << "Pos (x: " << position.x << ", y: " << position.y << ")" << std::endl;
}

void TransformComponent::move(float x, float y) {
	transform.move(x, y);
}
void TransformComponent::rotation(float x) {
	transform.rotate(x);
}
void TransformComponent::scale(float x, float y) {
	transform.scale(x, y);
}