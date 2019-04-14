#include "pch.h"
#include "GameObject.h"


GameObject::GameObject()
{
	 parent = NULL;

	 body.setSize(sf::Vector2f(100.0f, 100.0f));
	 body.setOrigin(body.getSize() / 2.0f);
	 body.setOutlineColor(sf::Color::Red);
	 body.setOutlineThickness(5);

	 distanceFromParent = 0;
	 rotationOffsetFromParent = (sf::Vector2f(0,0));
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

void GameObject::AddChild(GameObject* s) 
{
	s->ChildOffsetFromParent = s->getPosition()- this->getPosition();
	s->distanceFromParent = sqrt((pow(s->ChildOffsetFromParent.x, 2)) + (pow(s->ChildOffsetFromParent.y, 2)));	
	s->rotationOffsetFromParent = {0, 0};
	s->initialAngleToParent = acos(0 * s->ChildOffsetFromParent.x + 1 * s->ChildOffsetFromParent.y);
}

void GameObject::Update(float msec) {
	if (parent) { 
		//worldTransform = parent->worldTransform * transforms;
		//this->setPosition(parent->getPosition() + this->getPosition());
		this->rotationOffsetFromParent = (sf::Vector2f (sin((this->parent->getRotation()+ initialAngleToParent)*3.14159 / 180), sin(((this->parent->getRotation()+ initialAngleToParent)+ 90)*3.14159 / 180)));
		this->setobjectPosition({ parent->getPosition().x + (distanceFromParent*rotationOffsetFromParent.x), parent->getPosition().y - (distanceFromParent*rotationOffsetFromParent.y) });
		this->rotateObject(parent->getRotation()-this->getRotation());
		this->Scale(parent->getScale());
		
		//parent->getTransform()*this->getTransform();
	}
	else { 
		
	}
	for (std::vector<GameObject*>::iterator i = children.begin(); i !=
		children.end(); ++i) {
		(*i)->Update(msec);
	}
}



//from actor
void GameObject::setImage(std::string image) {
	const sf::Texture *pTexture = &actorTexture;

	actorTexture.loadFromFile(image);
	sprite.setTexture(actorTexture);


	centerX = sprite.getGlobalBounds().width / 2;
	centerY = sprite.getGlobalBounds().height / 2;
	this->setOrigin(sf::Vector2f(centerX, centerY));
	sprite.setOrigin(sf::Vector2f(centerX, centerY));

	body.setTexture(pTexture);
}

void GameObject::setobjectPosition( sf::Vector2f newpos) {
	this->setPosition(newpos);
	body.setPosition(newpos);
	sprite.setPosition(newpos);

}

void GameObject::draw(sf::RenderWindow &window) {
	//window.draw(sprite);
	window.draw(body);
}

void GameObject::moveObject(sf::Vector2f m) {
	this->move(m);
	body.move(m);
	//sprite.move(m);
}

void GameObject::rotateObject(float x) {
	this->rotate(x);
	body.rotate(x);
	//sprite.rotate(x);
}

void GameObject::scaleObject(sf::Vector2f m) {
	this->scale(m);
	body.scale(m);
	sprite.scale(m);
}

void GameObject::Scale(sf::Vector2f m) {
	this->setScale(m);
	body.setScale(m);
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



