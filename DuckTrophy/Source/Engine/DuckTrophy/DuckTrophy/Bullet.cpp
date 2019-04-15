#include "pch.h"
#include "Bullet.h"
#include "Initialise.h"
#include <iostream>

Bullet::Bullet()
{
}

Bullet::Bullet(int d, float v, sf::Vector2f pos)
{
	direction = d;
	velocity = v;
	this->setBodySize({ 10,10 });
	this->setBodyOrigin(body.getSize() / 2.0f);
	this->setobjectPosition({pos.x,pos.y});
}

Bullet::~Bullet()
{
}

void Bullet::movedir() {
	if (direction == 1)
		this->moveObject({ 0,-velocity * 1 });
	else if (direction == 2)
		this->moveObject({ velocity * 1,0 });
	else if (direction == 3)
		this->moveObject({ 0,velocity * 1 });
	else if (direction == 4)
		this->moveObject({ -velocity * 1,0 });

}


void Bullet::updateBullet() 
{
	movedir();
}

