#pragma once

#include "Eventmanager.h"
using namespace std;
class InputClass : public EventHandler
{
public:
	InputClass();
	~InputClass();
	void Initialize();
	void Shutdown();

	void KeyDown(uintptr_t key);
	void KeyUp(uintptr_t key);

	bool IsKeyDown(uintptr_t key);
	void OnLeftMouseClick(const EventClass_LMouse_Clicked* mouseEvent);

private:

	bool keyStates[256];
	bool LMB_Clicked = false;
};

