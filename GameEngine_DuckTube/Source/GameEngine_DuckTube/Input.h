#pragma once

using namespace std;
class InputClass
{
public:
	InputClass();
	~InputClass();
	void Initialize();
	void Shutdown();

	void KeyDown(uintptr_t key);
	void KeyUp(uintptr_t key);

	bool IsKeyDown(uintptr_t key);

private:
	bool keyStates[256];
};

