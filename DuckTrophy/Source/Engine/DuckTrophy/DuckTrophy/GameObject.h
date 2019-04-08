#pragma once
#include <vector>
#include <list>
#include <map>
#include <SFML/Graphics.hpp>
#include "Collider.h"
class GameObject :public sf::Transformable
{
public:
	GameObject();
	~GameObject(void);

	void SetTransform(const sf::Transform &matrix) { transforms = matrix; };

	void setParent(GameObject& p){ parent = &p; };
	void AddChild(GameObject* s);

	virtual void Update(float msec);
	
	std::string name;
	void setname(std::string n) { name = n; };
	//void InitializeGameObject();
	sf::Texture* objectTexture;

	void Start();
	//from actor
	void setImage(std::string image);
	void setPosition(sf::Vector2f newpos);
	void draw(sf::RenderWindow &window);

	sf::Sprite sprite;
	sf::Texture actorTexture;

	float centerX = sprite.getGlobalBounds().width / 2;
	float centerY = sprite.getGlobalBounds().height / 2;

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

	Collider getcollider() { return Collider(body); };

	void oncollision(sf::Vector2f direction);


private:
	std::map<int, GameObject*> m_Objects;
	static int nextObjectID;
	sf::RectangleShape body;

protected:
	GameObject* parent;
	sf::Transform worldTransform;
	sf::Transform transforms;
	std::vector<GameObject*>children;
};

