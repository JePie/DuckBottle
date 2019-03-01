#pragma once
#include "base.h"
#include <SFML/Window.hpp>
#include "tubeStd.h"

class Engine : public base<Engine>
{
private:
	sf::Window* window;
	sf::Sprite Background;
	sf::Texture BackgroundTex;
	sf::Image icon;
	sf::Clock clock;
	float dtAsSeconds;
	sf::Vector2f resolution;

private:
	friend base;

	void Shutdown();

public:
	Engine();

	sf::Window* GetWindow() const;
	void InitializeWindow();
	void NotifyCloseRequest();
	void SlpashScreen();
	void mainWindow();
	sf::RenderWindow Window;
	sf::Music music;

};
