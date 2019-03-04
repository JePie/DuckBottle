#pragma once
#include "tubeStd.h"
#include <vector>
#include "Component.h"
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
	void InitializeGameObject();
	sf::Texture objectTexture;

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

