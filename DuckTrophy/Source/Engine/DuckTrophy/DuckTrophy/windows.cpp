#include "pch.h"
#include "Windows.h"


Window::Window()
{
	InitializeWindow();
}

void Window::InitializeWindow(int _screenWidth, int _screenHeight, bool _isFullScreen)
{
	
	window = new sf::Window(sf::VideoMode(_screenWidth, _screenHeight), "Duck Tube Engine");
}


sf::Window* Window::GetWindow() const
{

	return window;
}


void Window::NotifyCloseRequest()
{

	window->close();
}

