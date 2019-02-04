#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Actor {

private:

	Vector2f position;
	Sprite sprite;
	Texture texture;

	bool LeftPressed;
	bool RightPressed;
	bool UpPressed;
	bool DownPressed;


	float speed;

public:

	Actor();

	void stopUp();
	void stopDown();
	void stopLeft();
	void stopRight();

	Sprite getSprite();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void update(float elapsedTime);
};