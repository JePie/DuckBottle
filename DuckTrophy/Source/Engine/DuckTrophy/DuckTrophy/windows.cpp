#include "pch.h"
#include "Windows.h"
#include <SFML/Window.hpp>
#include "tubeStd.h"
#include "GameObject.h"
#include "Initialise.h"
#include "Input.h"

Engine::Engine()
{
}
float sec;
int x = 0;
duckTubeEngine duck;

void Engine::InitializeWindow()
{
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;
	SlpashScreen();
	sf::Texture s = sf::Texture();


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
	

	Window.create(sf::VideoMode(resolution.x, resolution.y),
		"Slpash Screen",
		sf::Style::Default);
	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}

		Update::Update(dtAsSeconds);
		sec++;
		if (sec == 3000.0f)
		{

			mainWindow();
		}
		GameObject actor;
		actor.setImage("Duck_Trophy.png");
		actor.setPosition(0, 0);
		actor.Scale(5, 3.5f);
		//actor.draw();
		Window.draw(actor.actor);
		Window.display();
	}


}
void Engine::mainWindow() {
	Window.create(sf::VideoMode(resolution.x, resolution.y),
		"Main",
		sf::Style::Default);
	
	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}
		GameObject actor;
		GameObject child;

		Window.clear(sf::Color::Red);
		actor.setImage("duck.png");
		actor.setPosition(x, 50);
		//actor.draw();
		Window.draw(actor.actor);

		
		child.setImage("duck.png");
		child.setPosition(0, 150);
		child.setParent(actor);
		//actor.draw();
		Window.draw(child.actor);

		music.loadFromFile("ChillingMusic.wav");
		sound.setBuffer(music);
		sound.setVolume(50.f);
		sound.setLoop(true);
		//sound.play();


		icon.loadFromFile("duck.png");
		Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		Update::Update(dtAsSeconds);
		Input input;
		x += 10;
		if (x > resolution.x) {
			x = 0;
		}

		Window.display();
	}
}
