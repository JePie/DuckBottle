#include "pch.h"
#include "Windows.h"
#include <SFML/Window.hpp>
#include "tubeStd.h"
#include "GameObject.h"
#include "Initialise.h"
#include "Input.h"
#include"TransformComponent.h"
#include "PhysicsComponent.h"
#include "sceneManager.h"
#include "Bullet.h"
#include <iostream>
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
	SCENE scene = SPLASH;
	int GAME_STATE = SPLASH;
	Window.create(sf::VideoMode(resolution.x, resolution.y),
		"Slpash Screen",
		sf::Style::Default);
	GameObject *actor = new GameObject();
	actor->setImage("Duck_Trophy.png");
	actor->setobjectPosition({ 1000, 550 });
	actor->Scale({ 5, 3.3f });
	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}
		Input input;
		input.inputCheck();
		if (GAME_STATE == SPLASH)
		{
			Update::Update(dtAsSeconds);
			sec++;
			
			//actor.draw();
			Window.draw(actor->sprite);
			if (sec == 3000.0f)
			{
				GAME_STATE = MENU;
			}
		}
		if (GAME_STATE == MENU)
		{
			Window.clear();
			duck.MenuTitle.setFont(duck.font);
			duck.MenuTitle.setFillColor(sf::Color::White);
			duck.MenuTitle.setCharacterSize(30);
			duck.MenuTitle.setPosition(20, 0);
			duck.MenuTitle.setString("Tube Engine Menu");
			Window.draw(duck.MenuTitle);

			//Window.create(sf::VideoMode(resolution.x, resolution.y), duck.MenuTitle.getString, sf::Style::Default);

			duck.MenuIntroduced.setFont(duck.font);
			duck.MenuIntroduced.setFillColor(sf::Color::White);
			duck.MenuIntroduced.setCharacterSize(30);
			duck.MenuIntroduced.setPosition(resolution.x / 2, resolution.y / 2);
			duck.MenuIntroduced.setString("Press w to start game");
			Window.draw(duck.MenuIntroduced);

			if (input.isWPressed)
			{
				GAME_STATE = GAME;
			}

		}
		if (GAME_STATE == GAME)
		{
			mainWindow();
		}

		Window.display();
	}


}


void Engine::mainWindow()
{

	//Music Invoked Here
	//Audio::PlayMusic("ChillingMusic.wav");

	Window.create(sf::VideoMode(resolution.x, resolution.y), "Main", sf::Style::Default);
	WPARAM wParam = NULL;  
	
	//icon
	icon.loadFromFile("duck.png");
	Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::Clock timer;

	sf::Time dt = timer.restart();
	//Location for Positioning
	float tileSize = 50;
	float xStart = 485;
	float yStart = 65;

	//Outer Borders
	GameObject *blackWalls = new GameObject[4];

	GameObject *blackwallOne = new GameObject();
	blackWalls[0] = *blackwallOne;
	blackWalls[0].setImage("BlackBox.png");
	blackWalls[0].setBodySize({ 1920,40 });
	blackWalls[0].setBodyOrigin({ 960,20 });
	blackWalls[0].setobjectPosition({ 960,20 });

	GameObject *blackwallTwo = new GameObject();
	blackWalls[1] = *blackwallTwo;
	blackWalls[1].setImage("BlackBox.png");
	blackWalls[1].setBodySize({ 1920,40 });
	blackWalls[1].setBodyOrigin({ 960,20 });
	blackWalls[1].setobjectPosition({ 960,1060 });


	GameObject *blackwallThree = new GameObject();
	blackWalls[2] = *blackwallThree;
	blackWalls[2].setImage("BlackBox.png");
	blackWalls[2].setBodySize({ 460,1080 });
	blackWalls[2].setBodyOrigin({ 230,540 });
	blackWalls[2].setobjectPosition({ 230,540 });

	GameObject *blackwallFour = new GameObject();
	blackWalls[3] = *blackwallFour;
	blackWalls[3].setImage("BlackBox.png");
	blackWalls[3].setBodySize({ 460,1080 });
	blackWalls[3].setBodyOrigin({ 230,540 });
	blackWalls[3].setobjectPosition({ 1690,540 });


	//List of all initial actors excluding the player
	GameObject *object = new GameObject[500];
	int numOfObjects = 0;
	int numOfWalls = 0;

	bool grid[20][20];
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 20; column++) {
			grid[row][column] = false;
		}
	}

	GameObject *walls = new GameObject[500];

	for (float x = 0; x < 1; x++)
	{
		for (float y = 0; y < 20; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}

	for (float x = 0; x < 20; x++)
	{
		for (float y = 0; y < 1; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}

	for (float x = 4; x < 5; x++)
	{
		for (float y = 7; y < 10; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}


	for (float x = 9; x < 10; x++)
	{
		for (float y = 7; y < 10; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}

	for (float x = 14; x < 15; x++)
	{
		for (float y = 7; y < 10; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}

	for (float x = 19; x < 20; x++)
	{
		for (float y = 0; y < 20; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}
	// next set of walls 


	for (float x = 3; x < 8; x++)
	{
		for (float y = 12; y < 13; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}	
	
	for (float x = 12; x < 17; x++)
	{
		for (float y = 12; y < 13; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}
	//spawn walls 
	for (float x = 8; x < 9; x++)
	{
		for (float y = 18; y < 20; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}

	for (float x = 12; x < 13; x++)
	{
		for (float y = 18; y < 20; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}
	//blocks
	for (float x = 16; x < 18; x++)
	{
		for (float y = 15; y < 17; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}

	for (float x = 2; x < 4; x++)
	{
		for (float y = 15; y < 17; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}

	for (float x = 4; x < 7; x++)
	{
		for (float y = 3; y < 5; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}

	for (float x = 12; x < 15; x++)
	{
		for (float y = 3; y < 5; y++)
		{
			GameObject *brick = new GameObject();
			walls[numOfWalls] = *brick;
			walls[numOfWalls].setobjectPosition({ xStart + (tileSize*x), yStart + (tileSize*y) });
			walls[numOfWalls].setImage("GreenBrick1.png");
			numOfWalls++;
		}
	}

	GameObject *player = new GameObject();
	player->setobjectPosition({ xStart + (tileSize * 10), yStart + (tileSize * 10) });
	player->setImage("Tank.png");
	//player->AddChild(actor);
	//actor->setParent(*player);
	//actor->initialAngleToParent = 90;
	PhysicsComponent physicsEngine;


	Bullet *PBullets = new Bullet[500];
	int numOfPBullets = 0;
	int bulletTimer = 0;
	bool loop = true;

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

		if (bulletTimer > 0)
			bulletTimer--;

		//player->Scale({ -1,1});

		//scene graph ---------------------------------
		sf::Vector2f direction;

		object[1].setOrigin(sf::Vector2f(200, 200));

		//
		//if (!physicsEngine.collide) 
		//{
		//	player->velocity = sf::Vector2f(1, 1);
		//}
		//


		Input input;
		input.ProcessInput(wParam);
		input.inputCheck();

		if (input.isDownPressed) {

			player->moveObject({ 0 ,player->velocity.y * 5 });
			player->setrotation(180);
		}

		else if (input.isUpPressed) {

			player->moveObject({ 0 ,-player->velocity.y * 5 });
			player->setrotation(0);
		}

		else if (input.isLeftPressed) {

			player->moveObject({ -player->velocity.x * 5  ,0 });
			player->setrotation(270);
		}

		else if (input.isRightPressed) {

			player->moveObject({ player->velocity.x * 5  ,0 });
			player->setrotation(90);
		}

		if (input.isSPressed) {

			if (bulletTimer <= 0)
			{
				Bullet *bullet = new Bullet();
				cout << "shooooooooottt;lkasdmf;ld :::: " << bulletTimer;

				if (player->getRotation() == 0)
				{
					bullet = new Bullet(1, 5.0f, { player->getPosition().x,player->getPosition().y - 30 });
					PBullets[numOfPBullets] = *bullet;
					numOfPBullets++;
					cout << "up" << endl;
				}
				else if (player->getRotation() == 90)
				{
					bullet = new Bullet(2, 5.0f, { player->getPosition().x + 30,player->getPosition().y });
					PBullets[numOfPBullets] = *bullet;
					numOfPBullets++;
					cout << "r" << endl;
				}
				else if (player->getRotation() == 180)
				{
					bullet = new Bullet(3, 5.0f, { player->getPosition().x,player->getPosition().y + 30 });
					PBullets[numOfPBullets] = *bullet;
					numOfPBullets++;
					cout << "d" << endl;
				}
				else if (player->getRotation() == 270)
				{
					bullet = new Bullet(4, 5.0f, { player->getPosition().x - 30,player->getPosition().y });
					PBullets[numOfPBullets] = *bullet;
					numOfPBullets++;
					cout << "l" << endl;
				}
				bulletTimer = 35;
			}


			cout << "number of bullets :  " << numOfPBullets << endl;


		}
		else if (input.isWPressed) {
			player->Scale({ 1,1 });
		}
		else if (input.isAPressed) {
			player->rotateObject(-5);
		}
		else if (input.isDPressed) {
			player->rotateObject(5);
		}

		//x += timer.getElapsedTime().asSeconds()*player->velocity.x;
		//if (x > resolution.x) {
		//	x = 0;
		//}

		player->draw(Window);
		for (int i = 0; i < numOfObjects; i++)
		{
			object[i].draw(Window);
			if (player->getcollider().CheckCollision(object[i].getcollider(), direction, 1.0f)) {
				player->setobjectPosition(player->body.getPosition());
				//player->oncollision(direction);
				//physicsEngine.checkCollision(*actor, *player);
				//physicsEngine.ResolveCollision(*actor, *player);

				for (int a = i; i < numOfObjects; i++)
				{
					object[a] = object[a + 1];
				}
				numOfObjects--;
			}
		}


		for (int i = 0; i < numOfWalls; i++)
		{
			if (walls[i].stage == 0)
				walls[i].setImage("GreenBrick1.png");
			if (walls[i].stage == 1)
				walls[i].setImage("GreenBrick2.png");
			if (walls[i].stage == 2)
				walls[i].setImage("GreenBrick3.png");
			walls[i].draw(Window);
			player->getcollider().CheckCollision(walls[i].getcollider(), direction, 1.0f);
			player->setobjectPosition(player->body.getPosition());

		}


		for (int i = 0; i < 4; i++)
		{
			blackWalls[i].draw(Window);
			player->getcollider().CheckCollision(blackWalls[i].getcollider(), direction, 1.0f);
			player->setobjectPosition(player->body.getPosition());
		}

		for (int i = 0; i < numOfPBullets; i++)
		{
			PBullets[i].updateBullet();
			PBullets[i].setImage("Ball.png");
			PBullets[i].draw(Window);
			loop = true;
			for (int other = 0; other < 4 && loop == true; other++)
			{
				if (PBullets[i].getcollider().CheckCollision(blackWalls[other].getcollider(), direction, 1.0f))

				{
					for (int a = i; a < numOfPBullets; a++)
					{
						PBullets[a] = PBullets[a + 1];
					}
					numOfPBullets--;
					loop = false;
					cout << "cnumofBullets" <<numOfPBullets<< " other number--------" << other <<endl;
				}
			}

			for (int other = 0; other < numOfWalls && loop == true; other++)
			{
				if (PBullets[i].getcollider().CheckCollision(walls[other].getcollider(), direction, 1.0f))

				{
					for (int a = i; a < numOfPBullets; a++)
					{
						PBullets[a] = PBullets[a + 1];
					}
					numOfPBullets--;
					loop = false;

					//Changing wall picture or destroying wall


				 if (walls[other].stage == 2)
				{
					numOfWalls--;
					for (int a = other; a < numOfWalls; a++)
					{
						walls[a] = walls[a + 1];
					}
				}
					 else if (walls[other].stage == 0)
					{
						walls[other].stage++;
					}
					else if (walls[other].stage == 1)
					{
						walls[other].stage++;
					}		
					cout << "cnumofBullets" << numOfPBullets << " other number--------" << other << endl;
				}
			}


		}

		//Window.draw(physicsEngine.get_rectangleShape(*actor));
		//Window.draw(physicsEngine.get_rectangleShape(*player));
		Window.draw(duck.Text);
		Window.display();
	}
}