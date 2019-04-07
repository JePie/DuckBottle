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
	void setPosition(sf::Vector2f newpos);
	void draw(sf::RenderWindow &window);
	
	sf::Sprite sprite;
	sf::Texture actorTexture;

	float centerX = sprite.getGlobalBounds().width/2;
	float centerY = sprite.getGlobalBounds().height/2;

	sf::Vector2f position;
	sf::Vector2f velocity = sf::Vector2f(1, 1);
	float bounciness = 1;
	float mass = 1;
	sf::Transformable transform;
	sf::Clock clock;
	sf::Time dt = clock.restart();

	void moveObject(sf::Vector2f m);
	void rotateObject(float x);
	void scaleObject(sf::Vector2f m);
	void Scale(sf::Vector2f m);
	void UpdateTransform(float dtAsSec);


};

