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
	void input();
	void  Run();
	bool  HasFreeDiskSpace();
	bool ReadCPUSpeed();
	bool CheckMemory();
	sf::Text welcomeText;
	sf::Font font;

private:
	friend base<duckTubeEngine>;
	duckTubeEngine(const duckTubeEngine &_copy) = delete; 

	bool  SystemRequirements();

	
};