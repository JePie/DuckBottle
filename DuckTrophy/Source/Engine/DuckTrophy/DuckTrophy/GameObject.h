#pragma once
#include "tubeStd.h"
#include <vector>
class GameObject
{
public:
	GameObject() { parent = NULL; };
	~GameObject(void);

	void SetTransform(const sf::Transform &matrix) { transform = matrix; };

	void setParent(GameObject& p); //{ parent = s; };
	void AddChild(GameObject* s);

	virtual void Update(float msec);
	
	std::string name;
	void setname(std::string n) { name = n; };
	void InitializeGameObject();
	sf::Texture objectTexture;
protected:
	GameObject* parent;
	sf::Transform worldTransform;
	sf::Transform transform;
	std::vector<GameObject*>children;
};

