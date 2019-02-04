#include "pch.h"
#include "Windows.h"
#include <SFML/Window.hpp>
#include "tubeStd.h"
#include "GameObject.h"
#include "Initialise.h"

Engine::Engine()
{
}
float sec;
int x = 0;
duckTubeEngine duck;
void Engine::InitializeWindow()
{
	SlpashScreen();
	sf::Texture s = sf::Texture();
	if (!s.loadFromFile("duck.png")) {
		printf("ERROR\n");
	}
	//s.create(500, 500);
	Background.setTexture(BackgroundTex);
	icon.loadFromFile("duck.ico");
	duck.Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

}

sf::Window* Engine::GetWindow() const
{

	return window;
}


void Engine::NotifyCloseRequest()
{

	window->close();
}

void Engine::SlpashScreen() {
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;

	duck.Window.create(sf::VideoMode(resolution.x, resolution.y),
		"Slpash Screen",
		sf::Style::Default);

	while (duck.Window.isOpen())
	{
		sf::Time dt = clock.restart();
		sf::Event event;
		while (duck.Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				duck.Window.close();
		}
		dtAsSeconds = dt.asSeconds();
		update(dtAsSeconds);
		duck.Window.display();
	}


}

void Engine::mainWindow() {
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;
	sf::CircleShape shape(150.f);
	shape.setFillColor(sf::Color::Blue);
	duck.Window.create(sf::VideoMode(resolution.x, resolution.y),
		"Main",
		sf::Style::Default);
	while (duck.Window.isOpen())
	{
		sf::Time dt = clock.restart();
		sf::Event event;
		while (duck.Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				duck.Window.close();
		}

		dtAsSeconds = dt.asSeconds();
		duck.Window.clear(sf::Color::Red);
	
		duck.Window.draw(shape);
		shape.setPosition(x,0);
		
		update(dtAsSeconds);
		duck.Window.display();
	}
}
void Engine::update(float dtAsSec)
{
	x++;
	if (x > resolution.x) {
		x = 0;
	}
	sec++;

	if (sec == 3000.0f)
	{

		mainWindow();
	}
}
