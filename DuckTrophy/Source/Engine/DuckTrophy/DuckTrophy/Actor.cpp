#include "pch.h"
#include "Actor.h"
#include "Initialise.h"

Actor::Actor()
{
}


Actor::~Actor()
{
}
 ;
void Actor::setImage(std::string image) {
	actorTexture.loadFromFile(image);
	sprite.setTexture(actorTexture);
}

void Actor::setPosition(sf::Vector2f newpos) {
	sprite.setPosition(newpos);
}

void Actor::draw(sf::RenderWindow &window) {
	window.draw(sprite);
}

void Actor::moveObject(sf::Vector2f m) {
	sprite.move(m);
}

void Actor::rotateObject(float x) {
	sprite.rotate(x);
}

void Actor::scaleObject(sf::Vector2f m) {
	sprite.scale(m);
}

void Actor::Scale(sf::Vector2f m) {
	sprite.setScale(m);
}

void Actor::UpdateTransform(float dtAsSec)
{
	dtAsSec = dt.asSeconds();
}

