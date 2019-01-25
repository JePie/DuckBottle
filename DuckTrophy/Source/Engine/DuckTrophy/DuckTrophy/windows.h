#pragma once
#include "base.h"
#include <SFML/Window.hpp>

class Window : public base<Window>
{
private:
	sf::Window* window;

private:
	friend base;
	Window();

	void InitializeWindow(int screenWidth = 800, int screenHeight = 600, bool isFullScreen = false);

	void Shutdown();

public:
	sf::Window* GetWindow() const;

	void NotifyCloseRequest();
};
