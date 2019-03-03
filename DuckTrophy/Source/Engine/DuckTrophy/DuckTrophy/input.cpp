#include "pch.h"
#include "Input.h"

Input::Input()
{
}


Input::~Input()
{
}

void Input::MouseMove(LPARAM lParam) {
	ptsBegin = MAKEPOINTS(lParam);
}
void Input::RightButtonDown() {
	pt.x = ptsBegin.x;
	pt.y = ptsBegin.y;
	storedKey = "Right click ";
	storedKey += std::to_string(pt.x);
	storedKey += " ";
	storedKey += std::to_string(pt.y);
	toPrint = storedKey.c_str();
	myBool = true;
}
void Input::LeftMouseUp() {
	pt.x = ptsBegin.x;
	pt.y = ptsBegin.y;
	storedKey = "Left click up ";
	storedKey += std::to_string(pt.x);
	storedKey += " ";
	storedKey += std::to_string(pt.y);
	toPrint = storedKey.c_str();
	storedPointEndX = pt.x;
	storedPointEndY = pt.y;
	myBool = true;
	readyToDrawLine = true;
}
void Input::LeftMouseDown() {
	pt.x = ptsBegin.x;
	pt.y = ptsBegin.y;

	if (PtInRect(&arrayofRects[0], pt))
	{

		if (!pointsBeginX.empty()) {
			deleteline = true;

		}
	}
	if (PtInRect(&arrayofRects[1], pt))
	{

		color = 2;

	}
	if (PtInRect(&arrayofRects[2], pt))
	{
		color = 1;

	}
	//reset line points
	storedPointBeginX = 0;
	storedPointBeginY = 0;
	storedPointEndX = 0;
	storedPointEndY = 0;
	storedKey = "Left click ";
	storedKey += std::to_string(pt.x);
	storedKey += " ";
	storedKey += std::to_string(pt.y);
	toPrint = storedKey.c_str();
	storedPointBeginX = pt.x;
	storedPointBeginY = pt.y;
	//myBool = true;
	//InvalidateRect(hWnd, rect, 1);
}
void Input::ProcessInput(WPARAM wParam) {
	myBool = true;
	value = (LPCSTR)&wParam;
	storedKey = (std::string)value;
	toPrint = storedKey.c_str();

	//cout << wParam << endl;
	//For Spacial Keydowns
	if (wParam == 17)
	{
		storedKey = "Control ";
		toPrint = storedKey.c_str();
	}
	else if (wParam == 32)
	{
		storedKey = "Space ";
		toPrint = storedKey.c_str();
	}
	else if (wParam == 16)
	{
		storedKey = "Shift ";
		toPrint = storedKey.c_str();
	}
	else if (wParam == 19)
	{
		storedKey = "Space ";
		toPrint = storedKey.c_str();
	}
	else if (wParam == 20)
	{
		storedKey = "Caps Lock ";
		toPrint = storedKey.c_str();
	}
	else if (wParam == 9)
	{
		storedKey = "TAB";
		toPrint = storedKey.c_str();
	}
}





void Input::inputCheck(sf::Keyboard key)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		isWPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		isAPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		isSPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		isDPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		isLeftPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		isUpPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		isDownPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		isRightPressed = true;
	}
}
//void Input::KeyboardHandler(UINT message, WPARAM wParam)
//{
//	wchar_t msg[32];
//	switch (message)
//	{
//	case WM_SYSKEYDOWN:
//		swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
//		OutputDebugString((LPCSTR)msg);
//		break;
//
//	case WM_SYSCHAR:
//		swprintf_s(msg, L"WM_SYSCHAR: %c\n", (wchar_t)wParam);
//		OutputDebugString((LPCSTR)msg);
//		break;
//
//	case WM_SYSKEYUP:
//		swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
//		OutputDebugString((LPCSTR)msg);
//		break;
//
//	case WM_KEYDOWN:
//		swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
//		OutputDebugString((LPCSTR)msg);
//		break;
//
//	case WM_KEYUP:
//		swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
//		OutputDebugString((LPCSTR)msg);
//		break;
//
//	case WM_CHAR:
//		swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)wParam);
//		OutputDebugString((LPCSTR)msg);
//		break;
//
//	}
//}
//
//void Input::MouseHandler(UINT message, WPARAM wParam)
//{
//	wchar_t msg[38];
//	switch (message)
//	{
//	case WM_LBUTTONDOWN:
//		swprintf_s(msg, L"WM_LBUTTONDOWN: Left Mouse Down\n", wParam);
//		OutputDebugString((LPCSTR)msg);
//		break;
//
//	case WM_LBUTTONUP:
//		swprintf_s(msg, L"WM_LBUTTONDOWN: Left Mouse Up\n", wParam);
//		OutputDebugString((LPCSTR)msg);
//		break;
//
//	case WM_MBUTTONDOWN:
//		swprintf_s(msg, L"WM_LBUTTONDOWN: Middle Mouse Down\n", wParam);
//		OutputDebugString((LPCSTR)msg);
//		break;
//
//	case WM_MBUTTONUP:
//		swprintf_s(msg, L"WM_LBUTTONDOWN: Middle Mouse Up\n", wParam);
//		OutputDebugString((LPCSTR)msg);
//		break;
//
//	case WM_RBUTTONDOWN:
//		swprintf_s(msg, L"WM_LBUTTONDOWN: Right Mouse Down\n", wParam);
//		OutputDebugString((LPCSTR)msg);
//		break;
//
//	case WM_RBUTTONUP:
//		swprintf_s(msg, L"WM_LBUTTONDOWN: Right Mouse Up\n", wParam);
//		OutputDebugString((LPCSTR)msg);
//		break;
//	}
//}