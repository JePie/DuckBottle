#include "pch.h"
#include "Collider.h"



Collider::Collider(sf::RectangleShape& body) : 
	body(body)
{
}


Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider other, sf::Vector2f& direction, float push)
{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();
	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersetX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x+5);
	float intersetY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y+5);
	if (intersetX < 0.0f && intersetY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);
		if (intersetX > intersetY)
		{
			if (deltaX > 0.0f)
			{
				Move(intersetX * (2.f - push), 0.0f);
				//other.Move(-intersetX * push, 0.0f);
				direction.x = 1.0f;
				direction.y = 0.0;
			}
			else
			{
				Move(-intersetX * (2.0f - push), 0.0f);
				//other.Move(intersetX * push, 0.0f);
				direction.x = -1.0f;
				direction.y = 0.0;
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersetY * (2.0f - push));
				//other.Move(0.0f, -intersetY * push);
				direction.x = 0.0f;
				direction.y = 1.0;
			}
			else
			{
				Move(0.0f, -intersetY * (2.0f - push));
				//other.Move(0.0f, intersetY * push);
				direction.x = 0.0f;
				direction.y = -1.0;
			}
		}
		return true;
	}
	return false;
}
