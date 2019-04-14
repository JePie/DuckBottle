#include "pch.h"
#include "Bullet.h"
#include "Initialise.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}
void Bullet::movedir(int dir) {
	direction = dir;
	switch (direction)
	{
	case 1:
		this->moveObject({this->velocity.x*1,0});
	case 2:
		this->moveObject({-this->velocity.x*1,0 });
	case 3:
		this->moveObject({0,this->velocity.y*1 });
	case 4:
		this->moveObject({0,-this->velocity.y*1});
	default:
		break;
	}

}

