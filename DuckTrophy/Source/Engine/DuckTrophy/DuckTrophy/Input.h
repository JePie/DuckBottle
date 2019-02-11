#pragma once
// Windows Header Files
#include "tubeStd.h"



class Input
{
public:
	Input();
	~Input();

	void KeyboardHandler(UINT message, WPARAM wParam);
	void MouseHandler(UINT message, WPARAM wParam);

};

