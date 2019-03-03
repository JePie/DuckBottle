#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
class GameObject
{
public:
	GameObject() { parent = NULL; };
	~GameObject(void);

	void SetTransform(const sf::Transform &matrix) { transform = matrix; };

	void setParent(GameObject& p){ parent = &p; };
	void AddChild(GameObject* s);

	virtual void Update(float msec);
	
	std::string name;
	void setname(std::string n) { name = n; };
	//void InitializeGameObject();
	sf::Texture objectTexture;

	sf::Vector2f position;
	sf::Vector2f velocity = sf::Vector2f(1,1);
	float bounciness = 1;
	float mass = 1;
	
	////actor
	//void setImage(std::string image);
	//void setPosition(float x, float y);
	//void draw();
	//void Scale(float x, float y);
	//sf::Sprite actor;
	//sf::Texture actorTexture;

protected:
	GameObject* parent;
	sf::Transform worldTransform;
	sf::Transform transform;
	std::vector<GameObject*>children;
};

