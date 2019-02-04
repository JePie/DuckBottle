/*###############################################################
#																#
#		Copyright 2019 Duck Trophy All Rights Reserved.			#
# Developed by Puraj Desai, John Paul Valdez and Minxu Huang    #
#                                                               #
################################################################*/

#pragma once
#include "tubeStd.h"
#include "Actor.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class duckTubeEngine : public base<duckTubeEngine>
{
public:
	duckTubeEngine();

	bool Initialize();

	void  Run(sf::RenderWindow Window);
	bool  HasFreeDiskSpace();
	bool ReadCPUSpeed();
	bool CheckMemory();
	void input();
	void update(float dtAsSeconds);
	Actor actor;

private:
	friend base<duckTubeEngine>;
	duckTubeEngine(const duckTubeEngine &_copy) = delete; 
	
	bool  SystemRequirements();

	Music music;
	Font font;
	
};