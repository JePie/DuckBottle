#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include<SFML/Graphics/Sprite.hpp>
#include "GameObject.h"
#include "windows.h"


class Bullet :public sf::Transformable , public GameObject
{
public:

	Bullet();
	~Bullet();
	int direction;

	void movedir(int dir);
};

