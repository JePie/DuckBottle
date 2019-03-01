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

	//Font Invoked here
	duck.font.loadFromFile("blackjack.otf");
	duck.welcomeText.setFont(duck.font);
	duck.welcomeText.setFillColor(sf::Color::White);
	duck.welcomeText.setCharacterSize(30);
	duck.welcomeText.setPosition(20, 0);

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

	Window.create(sf::VideoMode(resolution.x, resolution.y),"Slpash Screen",sf::Style::Default);
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
void Engine::mainWindow()
{

	//Music Invoked Here
	Audio::PlayMusic("ChillingMusic.wav");

	Window.create(sf::VideoMode(resolution.x, resolution.y), "Main", sf::Style::Default);
	WPARAM wParam = NULL;
	sf::Clock timer;
	timer.restart();
	duck.welcomeText.setString("timer: " +timer.getElapsedTime().asSeconds());

	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}
		GameObject actor;
		Window.clear(sf::Color::Red);
		actor.setImage("duck.png");
		actor.setPosition(x, 50);
		//actor.draw();

		//Setting up the icon
		icon.loadFromFile("duck.png");
		Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		Update::Update(dtAsSeconds);
		Input input;
		input.ProcessInput(wParam);
		x += 10;
		if (x > resolution.x) {
			x = 0;
		}

		//draw stuff
		Window.draw(actor.actor);
		Window.draw(duck.welcomeText);
		Window.display();
	}
}
