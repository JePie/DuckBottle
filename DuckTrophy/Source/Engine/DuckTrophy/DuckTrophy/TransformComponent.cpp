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

void TransformComponent::moveObject(float x, float y) {
	transform.move(x, y);
}
void TransformComponent::rotateObject(float x) {
	transform.rotate(x);
}
void TransformComponent::scaleObject(float x, float y) {
	transform.scale(x, y);
}