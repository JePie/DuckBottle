#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include<SFML/Graphics/Sprite.hpp>
#include "GameObject.h"
#include "windows.h"


class Actor :public sf::Transformable , public GameObject
{
public:

	Actor();
	~Actor();
	void setImage(std::string image);
	void setPosition(float x, float y);
	void draw();

	sf::Sprite sprite;
	sf::Texture actorTexture;
	float centerX = sprite.getGlobalBounds().width/2;
	float centerY = sprite.getGlobalBounds().height / 2;

	sf::Transformable transform;
	sf::Clock clock;
	sf::Time dt = clock.restart();
	void moveObject(float x, float y);
	void rotateObject(float x);
	void scaleObject(float x, float y);
	void Scale(float x, float y);
	void UpdateTransform(float dtAsSec);

};

