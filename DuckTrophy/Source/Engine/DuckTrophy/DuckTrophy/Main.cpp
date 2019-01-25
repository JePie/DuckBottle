/*###############################################################
#																#
#		Copyright 2019 Duck Trophy All Rights Reserved.			#
# Developed by Puraj Desai, John Paul Valdez and Minxu Huang    #
#                                                               #
################################################################*/

#include "pch.h"
#include <iostream>
#include<SFML/Graphics.hpp>
#include "Initialise.h"

using namespace sf;

int main()
{
	duckTubeEngine duck;
	duck.HasFreeDiskSpace();
	RenderWindow window(VideoMode(500, 500), "TubeEngine: SFML works!");
	CircleShape shape(150.f);
	shape.setFillColor(Color::Red);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	
	return 0;
}
