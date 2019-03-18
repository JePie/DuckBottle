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


//void TransformComponent::moveObject(Actor a, sf::Vector2f m) {
//	a.move(m);
//}
//
//void TransformComponent::rotateObject(Actor a, float x) {
//	a.rotate(x);
//}
//void TransformComponent::Scale(Actor a, sf::Vector2f m) {
//	a.setScale(m);
//}
//
//void TransformComponent::UpdateTransform(float dtAsSec)
//{
//	dtAsSec = dt.asSeconds();
//}