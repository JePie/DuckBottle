#include "pch.h"
#include "Windows.h"
#include <SFML/Window.hpp>
#include "tubeStd.h"
#include "GameObject.h"
#include "Initialise.h"
#include "Input.h"
#include"TransformComponent.h"
#include "PhysicsComponent.h"

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
	duck.Text.setFont(duck.font);
	duck.Text.setFillColor(sf::Color::White);
	duck.Text.setCharacterSize(30);
	duck.Text.setPosition(20, 0);

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
		Actor actor;
		actor.setImage("Duck_Trophy.png");
		actor.setPosition(0, 0);
		actor.Scale(5, 3.3f);
		//actor.draw();
		Window.draw(actor.sprite);
		Window.display();
	}


}
void Engine::mainWindow() 
{
	
	//Music Invoked Here
	Audio::PlayMusic("ChillingMusic.wav");

	Window.create(sf::VideoMode(resolution.x, resolution.y),"Main",sf::Style::Default);
	WPARAM wParam = NULL;
	
	sf::Clock timer;

	sf::Time dt = timer.restart();

	PhysicsComponent physicsEngine;

	while (Window.isOpen())
	{

		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}
		dtAsSeconds = dt.asSeconds();

		Actor actor;
		TransformComponent actorTransform;
		Window.clear(sf::Color::Red);
		actor.setImage("duck.png");
		actor.setPosition(x, 50);
		//actor.draw();
		duck.Text.setString("timer: "+ std::to_string(timer.getElapsedTime().asSeconds()));

		icon.loadFromFile("duck.png");
		Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		Actor player;
		player.setImage("duck.png");
		player.setPosition(1800, 0);
		player.moveObject(-x, 0);
		player.scaleObject(-1,1);
		player.setParent(actor);

		physicsEngine.setAABB(player);
		physicsEngine.setAABB(actor);
		physicsEngine.checkCollision(player, actor);
		physicsEngine.ResolveCollision(player, actor);

		Update::Update(dtAsSeconds);
		Input input;
		input.ProcessInput(wParam);

		if (physicsEngine.Distance(player.getPosition(),actor.getPosition())<0) {
			duck.Text.setString("collided");
		}
		else {
			duck.Text.setString("nope");
		}

		x += player.velocity.x*timer.getElapsedTime().asSeconds();
		if (x > resolution.x) {
			x = 0;
		}
		//draw stuff
		Window.draw(player.sprite);
		Window.draw(actor.sprite);
		Window.draw(duck.Text);
		Window.display();
	}
}
