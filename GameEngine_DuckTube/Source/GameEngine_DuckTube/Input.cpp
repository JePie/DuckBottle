#include "stdafx.h"
#include "Input.h"


InputClass::InputClass()
{
}
InputClass::~InputClass()
{
}
void InputClass::Initialize()
{
	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}
	registerEventFunc(this, &InputClass::OnLeftMouseClick);
}
void InputClass::Shutdown()
{

}
void InputClass::KeyDown(uintptr_t key)
{
	keyStates[key] = true;
}
void InputClass::KeyUp(uintptr_t key)
{
	keyStates[key] = false;
}
bool InputClass::IsKeyDown(uintptr_t key)
{
	return keyStates[key];
}

void InputClass::OnLeftMouseClick(const EventClass_LMouse_Clicked* mouseEvent)
{
	LMB_Clicked = true;
}