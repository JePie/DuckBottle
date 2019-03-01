#pragma once
#include "tubeStd.h"
#include "windows.h"
#include<SFML/Graphics.hpp>
class Actor
{
public:

	Actor();
	~Actor();
	void setImage(std::string image);
	void setPosition(float x, float y);
	void draw();
	sf::Sprite actor;
	sf::Texture actorTexture;
};

