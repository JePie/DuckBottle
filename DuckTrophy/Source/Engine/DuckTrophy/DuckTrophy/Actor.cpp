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
	actor.setTexture(actorTexture);
}
void Actor::setPosition(float x, float y) {
	actor.setPosition(x, y);
}

void Actor::draw() {
	Engine engine;
	engine.Window.draw(actor);
}