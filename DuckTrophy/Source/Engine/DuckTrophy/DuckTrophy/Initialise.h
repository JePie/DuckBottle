/*###############################################################
#																#
#		Copyright 2019 Duck Trophy All Rights Reserved.			#
# Developed by Puraj Desai, John Paul Valdez and Minxu Huang    #
#                                                               #
################################################################*/

#pragma once
#include "tubeStd.h"

class duckTubeEngine : public base<duckTubeEngine>
{
public:
	duckTubeEngine();
	~duckTubeEngine();

	bool Initialize();

	void  Run(sf::RenderWindow Window);
	bool ReadCPUSpeed();
	bool  HasFreeDiskSpace();

private:
	friend base<duckTubeEngine>;
	duckTubeEngine(const duckTubeEngine &_copy) = delete; 

	bool  SystemRequirements();
	
};