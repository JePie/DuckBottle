#pragma once
#include "tubeStd.h"
#include "windows.h"
#include "GameObject.h"
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Actor:sf::Transformable//,public GameObject
{
public:

	Actor();
	~Actor();
	void setImage(std::string image);
	void setPosition(float x, float y);
	void draw();

	sf::Sprite sprite;
	sf::Texture actorTexture;

	sf::Transformable transform;
	void moveObject(float x, float y);
	void rotateObject(float x);
	void scaleObject(float x, float y);
	void Scale(float x, float y);
};

