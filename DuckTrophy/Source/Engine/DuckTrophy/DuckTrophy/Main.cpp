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
	
	duckTubeEngine::Instance()->Initialize();
	duckTubeEngine::Instance()->Run();
	return 0;
}
