#pragma once
#include "GameObject.h"

class Component
{
public:
	Component();
	virtual void Update();
	void addComponent();
	~Component();
};

