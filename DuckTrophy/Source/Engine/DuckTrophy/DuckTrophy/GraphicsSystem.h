#pragma once
#include "tubeStd.h"
#include "base.h"
class GraphicsSystem : public base<GraphicsSystem>
{
public:
	GraphicsSystem();
	~GraphicsSystem();
	void CreateWin();
	void draw(sf::RenderWindow win);
	void update();
private:
	friend base;
};

