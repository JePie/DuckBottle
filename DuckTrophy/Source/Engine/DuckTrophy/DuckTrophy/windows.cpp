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
float x = 0;
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
		actor.setPosition({ 0, 0 });
		actor.Scale({ 5, 3.3f });
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
		//time
		dtAsSeconds = dt.asSeconds();
		duck.Text.setString("timer: " + std::to_string(timer.getElapsedTime().asSeconds()));
		TransformComponent actorTransform;

		Actor actor;
		Window.clear(sf::Color::Red);
		actor.setImage("duck.png");
		actor.setPosition({ 0, 50 });
		actor.moveObject({ x,0 });
		//actor.draw();


		Actor player;
		player.setImage("duck.png");
		player.setPosition({ 1800, 50 });
		player.moveObject({ -x,0 });
		player.Scale({ -1,1});
		player.setParent(actor);

		//physics
		physicsEngine.setAABB(player);
		physicsEngine.setAABB(actor);
		physicsEngine.fall(player, timer.getElapsedTime().asSeconds());
		physicsEngine.fall(actor, timer.getElapsedTime().asSeconds());
		physicsEngine.checkCollision(player, actor);

		//icon
		icon.loadFromFile("duck.png");
		Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		Update::Update(dtAsSeconds);
		Input input;
		input.ProcessInput(wParam);

		x += timer.getElapsedTime().asSeconds()*player.velocity.x;
		if (x > resolution.x) {
			x = 0;
		}
		if (physicsEngine.inAir == true) {
			player.moveObject({ player.velocity.x, player.velocity.y*timer.getElapsedTime().asSeconds() * 100 });
		}
		else if (physicsEngine.inAir &&player.getPosition().y > 150) {
			player.velocity = sf::Vector2f(0, 0);
			player.setPosition({ 1800,player.velocity.y });
			physicsEngine.inAir = false;
		}
		else {
			physicsEngine.inAir = true;
		}
		//draw stuff
		player.draw(Window);
		actor.draw(Window);
		Window.draw(duck.Text);
		Window.display();
	}
}
