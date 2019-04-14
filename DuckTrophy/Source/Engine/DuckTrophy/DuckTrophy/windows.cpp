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
		GameObject actor;
		actor.setImage("Duck_Trophy.png");
		actor.setobjectPosition({ 1000, 550 });
		actor.Scale({ 5, 3.3f });
		//actor.draw();
		Window.draw(actor.sprite);
		Window.display();
	}


}



void Engine::mainWindow() 
{
	
	//Music Invoked Here
	//Audio::PlayMusic("ChillingMusic.wav");

	Window.create(sf::VideoMode(resolution.x, resolution.y),"Main",sf::Style::Default);
	WPARAM wParam = NULL;
	
	sf::Clock timer;

	sf::Time dt = timer.restart();

	GameObject *actor = new GameObject();

	GameObject *player = new GameObject();
	

	actor->setobjectPosition({ 500, 500 });
	player->setobjectPosition({ 900, 500 });

	//actor->AddChild(player);

	//player->setParent(*actor);

	actor->setImage("duck.png");

	player->setImage("duck.png");

	PhysicsComponent physicsEngine;
	while (Window.isOpen())
	{


		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
			//if (event.type == sf::Event::KeyReleased)
			//	physicsEngine.inAir = false;
		}
		//time
		dtAsSeconds = dt.asSeconds();
		duck.Text.setString("timer: " + std::to_string(timer.getElapsedTime().asSeconds()));
		TransformComponent actorTransform;

		Window.clear(sf::Color::Blue);

		//player->Scale({ -1,1});

		//scene graph ---------------------------------
		sf::Vector2f direction;
		
		actor->setOrigin(sf::Vector2f(200, 200));
	
		//player->Update(timer.getElapsedTime().asSeconds());

		//player->setobjectPosition({ actor->getPosition().x + 500, actor->getPosition().y + 50 });
		
	
		if (actor->getcollider().CheckCollision(player->getcollider(), direction, 1.0f)) {
			actor->oncollision(direction);
			
		}


		//physics
		//physicsEngine.setAABB(*player);
		//physicsEngine.setAABB(*actor);
		//physicsEngine.fall(actor);
		physicsEngine.checkCollision(*actor, *player);
		//physicsEngine.ResolveCollision(*actor, *player);

		//
		//if (!physicsEngine.collide) 
		//{
		//	player->velocity = sf::Vector2f(1, 1);
		//}
		//

		//icon
		icon.loadFromFile("duck.png");
		Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		Input input;
		input.ProcessInput(wParam);
		input.inputCheck();

		if (input.isDownPressed) {
			actor->moveObject({ 0 ,actor->velocity.y*10 });
		}

		else if (input.isUpPressed) {
			actor->moveObject({ 0 ,-actor->velocity.y * 10 });
			//physicsEngine.inAir = true;
		}

		else if (input.isLeftPressed) {
			actor->moveObject({ -actor->velocity.x * 10  ,0 });
			//actor.Scale({ -1,1 });
		}

		else if (input.isRightPressed) {
			actor->moveObject({ actor->velocity.x * 10  ,0 });
			//actor.Scale({ 1,1 });
		}

		if (input.isSPressed) {
			actor->Scale({2,2});
		}
		else if (input.isWPressed) {
			actor->Scale({ 1,1 });
		}
		else if (input.isAPressed) {
			actor->rotateObject(-5);
		}
		else if (input.isDPressed) {
			actor->rotateObject(5);
		}

		//x += timer.getElapsedTime().asSeconds()*player->velocity.x;
		//if (x > resolution.x) {
		//	x = 0;
		//}

		player->draw(Window);
		actor->draw(Window);
		//Window.draw(physicsEngine.get_rectangleShape(*actor));
		//Window.draw(physicsEngine.get_rectangleShape(*player));
		Window.draw(duck.Text);
		Window.display();
	}
}
