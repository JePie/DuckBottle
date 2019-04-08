#include "pch.h"
#include "GameObject.h"


GameObject::GameObject()
{
	 parent = NULL;

	 body.setSize(sf::Vector2f(100.0f, 100.0f));
	 body.setOrigin(body.getSize() / 2.0f);
	 body.setPosition(206.0f, 206.0f);
	 body.setTexture(objectTexture);
}
GameObject::~GameObject()
{
	/*for (unsigned int i = 0; i < children.size(); i++){
		delete children[i];
	}*/
}
void GameObject::Start()
{

	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Start();
	}
}

void GameObject::AddChild(GameObject* s) {
	children.push_back(s);
	s->parent = this;
}

void GameObject::Update(float msec) {
	if (parent) { //This node has a parent...
		worldTransform = parent->worldTransform * transforms;
	}
	else { //Root node, world transform is local transform!
		worldTransform = transforms;
	}
	for (std::vector<GameObject*>::iterator i = children.begin(); i !=
		children.end(); ++i) {
		(*i)->Update(msec);
	}
}



//from actor
void GameObject::setImage(std::string image) {
	actorTexture.loadFromFile(image);
	sprite.setTexture(actorTexture);
}

void GameObject::setPosition(sf::Vector2f newpos) {
	sprite.setPosition(newpos);
}

void GameObject::draw(sf::RenderWindow &window) {
	window.draw(sprite);
}

void GameObject::moveObject(sf::Vector2f m) {
	sprite.move(m);
}

void GameObject::rotateObject(float x) {
	sprite.rotate(x);
}

void GameObject::scaleObject(sf::Vector2f m) {
	sprite.scale(m);
}

void GameObject::Scale(sf::Vector2f m) {
	sprite.setScale(m);
}

void GameObject::UpdateTransform(float dtAsSec)
{
	dtAsSec = dt.asSeconds();
}

void GameObject::oncollision(sf::Vector2f direction) {

	if (direction.x < 0.0f) {
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) {
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f) {
		velocity.y = 0.0f;
	}
	else if (direction.y > 0.0f) {
		velocity.y = 0.0f;
	}
}



