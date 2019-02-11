#include "pch.h"
#include "TransformComponent.h"


TransformComponent::TransformComponent()
{

}


TransformComponent::~TransformComponent()
{

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