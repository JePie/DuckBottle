
#include "pch.h"
#include"tubeStd.h"
#include "Initialise.h"
#include <iostream>

void duckTubeEngine::input()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		//close Window Method to invoke
	}

	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
	{
		actor.moveLeft();
		std::cout << "a / left";
	}
	else
	{
		actor.stopLeft();
	}

	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
	{
		actor.moveRight();
	}
	else
	{
		actor.stopRight();
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
	{
		actor.moveUp();
	}
	else
	{
		actor.stopUp();
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
	{
		actor.moveDown();
	}
	else
	{
		actor.stopDown();
	}

}