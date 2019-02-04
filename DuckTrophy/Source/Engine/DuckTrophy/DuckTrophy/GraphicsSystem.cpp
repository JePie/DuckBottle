#include "pch.h"
#include "GraphicsSystem.h"
#include "windows.h"
#include"Initialise.h"
#include "tubeStd.h"
GraphicsSystem::GraphicsSystem()
{
}


GraphicsSystem::~GraphicsSystem()
{
}
void GraphicsSystem::CreateWin() {
	Engine::Instance()->InitializeWindow();
}
void GraphicsSystem::draw(sf::RenderWindow win) {
	//duck.Window.draw();
	win.display();
}