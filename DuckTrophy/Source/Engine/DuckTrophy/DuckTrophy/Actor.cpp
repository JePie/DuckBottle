
#include "pch.h"
#include"Actor.h"

Actor::Actor()
{
	speed = 800;

	//texture.loadFromFile("duck.png");
	//sprite.setTexture(texture);

	position.x = 800;
	position.y = 800;

}
void Actor::stopLeft()
{
	LeftPressed = false;
}
void Actor::stopRight()
{
	RightPressed = false;
}
void Actor::stopUp()
{
	UpPressed = false;
}
void Actor::stopDown()
{
	DownPressed = false;
}
Sprite Actor::getSprite()
{
	return sprite;
}

void Actor::moveLeft()
{
	LeftPressed = true;
}

void Actor::moveRight()
{
	RightPressed = true;
}
void Actor::moveUp()
{
	UpPressed = true;
}
void Actor::moveDown()
{
	DownPressed = true;
}

void Actor::update(float elapsedTime)
{
	if (RightPressed)
	{
		position.x += speed * elapsedTime;
	}

	if (LeftPressed)
	{
		position.x -= speed * elapsedTime;
	}

	if (UpPressed)
	{
		position.y -= speed * elapsedTime;
	}

	if (DownPressed)
	{
		position.y += speed * elapsedTime;
	}

	sprite.setPosition(position);

}