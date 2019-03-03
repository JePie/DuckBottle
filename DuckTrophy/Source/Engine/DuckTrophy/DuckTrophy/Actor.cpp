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
void Actor::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}

void Actor::draw() {
	Engine engine;
	engine.Window.draw(sprite);
}
void Actor::moveObject(float x, float y) {
	sprite.move(x, y);
}
void Actor::rotateObject(float x) {
	sprite.rotate(x);
}
void Actor::scaleObject(float x, float y) {
	sprite.scale(x, y);
}
void Actor::Scale(float x,float y) {
	sprite.setScale(x,y);
}
void Actor::UpdateTransform(float dtAsSec)
{
	dtAsSec = dt.asSeconds();
	setPosition(velocity.x*dtAsSec, velocity.y*dtAsSec);
}

