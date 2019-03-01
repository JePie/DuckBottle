#include "pch.h"
#include "GameObject.h"


GameObject::~GameObject()
{
	for (unsigned int i = 0; i < children.size(); i++){
		delete children[i];
	}
}
void GameObject::AddChild(GameObject* s) {
	children.push_back(s);
	s->parent = this;
}

void GameObject::Update(float msec) {
	if (parent) { //This node has a parent...
		worldTransform = parent->worldTransform * transform;
	}
	else { //Root node, world transform is local transform!
		worldTransform = transform;
	}
	for (std::vector<GameObject*>::iterator i = children.begin(); i !=
		children.end(); ++i) {
		(*i)->Update(msec);
	}
}

void GameObject::setImage(std::string image) {
	actorTexture.loadFromFile(image);
	actor.setTexture(actorTexture);
}
void GameObject::setPosition(float x, float y) {
	actor.setPosition(x, y);
}
//void GameObject::getPosition() {
//	actor.getPosition;
//}

void GameObject::draw() {
	Engine engine;
	engine.Window.draw(actor);
}
void GameObject::Scale(float x,float y) {
	actor.setScale(x,y);
}
