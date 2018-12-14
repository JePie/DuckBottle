//John Paul Valdez 101055854
//Minxu Huang 101074668
//Puraj Desai 101093244

#include "stdafx.h"
#include <atlhandler.h>
#include <iostream>
#include <winnt.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>  
#include <tchar.h>  
#include <strsafe.h>
#include "Input.h"
#include <LuaPlus.h>

using namespace std;
using namespace LuaPlus;
//Initializing Function
bool IsOnlyInstance(LPCTSTR gameTitle);
bool CheckStorage(const DWORDLONG diskSpaceNeeded);
bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
DWORD ReadCPUSpeed();

//Checks if an instance of the application is already running or not.
bool IsOnlyInstance(LPCTSTR gameTitle)
{
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() != ERROR_SUCCESS) {
		HWND hWnd = FindWindow(gameTitle, NULL);
		if (hWnd) {
			// An instance of your game is already running.
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			cout << "more than one instances is running\n" << endl;
			return false;
		}
	}
	else
	{
		cout << "no multiple instances is running\n" << endl;
	}
	return true;
}

//Checks if device has required disk space needed.
bool CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	LPCTSTR lpDirectoryName = NULL;
	__int64 lpFreeBytesAvailable;
	__int64 lpTotalNumberOfBytes;
	__int64 lpTotalNumberOfFreeBytes;

	GetDiskFreeSpaceEx(lpDirectoryName, (PULARGE_INTEGER)&lpFreeBytesAvailable, (PULARGE_INTEGER)&lpTotalNumberOfBytes, (PULARGE_INTEGER)&lpTotalNumberOfFreeBytes);

	if ((DWORDLONG)lpTotalNumberOfBytes <= diskSpaceNeeded) {
		cout << "\tCheck Storage Failure: Not enough physical storage.\n" << endl;
		return false;
	}
	else {
		cout << "Disk Space Check: \n" << endl;
		cout << "\tRequested " << diskSpaceNeeded << " bytes needed." << endl;
		cout << "\tThere are " << (DWORDLONG)lpTotalNumberOfBytes << " available bytes." << endl;

		return true;
	}
}

//Displays the size of physical and virtual memory available to use.
bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded) {
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);

	cout << "\nPhysical & Virtual Memory Check:\n" << endl;
	cout << "\tRAM Requested: " << physicalRAMNeeded << "." << endl;
	cout << "\tVirtual RAM Requested: " << virtualRAMNeeded << "." << endl;
	cout << "\tThe total physical RAM available: " << status.ullAvailPhys << "." << endl;
	cout << "\tThe total virtual RAM avaialable: " << status.ullAvailVirtual << ".\n" << endl;

	if (status.ullAvailPhys < physicalRAMNeeded) {
		cout << "\tCheckMemory Failure : Not enough physical memory.\n" << endl;

		return false;
	}

	if (status.ullAvailVirtual < virtualRAMNeeded) {
		cout << "\tCheckMemory Failure : Not enough virtual memory.\n" << endl;

		return false;
	}
}

//Displays the CPU speed and architecture of the device
DWORD ReadCPUSpeed() {
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	DWORD strType = REG_SZ;
	char myBuff[256];
	HKEY hKey;
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0,
		KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS) {
		// query the key:
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)
			&dwMHz, &BufSize);
		cout << "CPU Speed aand Architecture:\n" << endl;
		cout <<"\t"<< dwMHz << " MHz CPU Speed" << endl;
	}

	long mError = RegQueryValueEx(hKey, "ProcessorNameString", NULL, &strType, (LPBYTE)&myBuff, &BufSize);

	while (mError == ERROR_MORE_DATA) {
		BufSize++;
		mError = RegQueryValueEx(hKey, "ProcessorNameString", NULL, &strType, (LPBYTE)&myBuff, &BufSize);
	}

	cout <<"\t"<< myBuff <<"\n"<< endl;

	return dwMHz;
}// The main window class name.  
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.  
static TCHAR szTitle[] = _T("Win32 Guided Tour Application");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable  

					   // The parameters to CreateWindow explained:  
					   // szWindowClass: the name of the application  
					   // szTitle: the text that appears in the title bar  
					   // WS_OVERLAPPEDWINDOW: the type of window to create  
					   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
					   // 500, 100: initial size (width, length)  
					   // NULL: the parent of this window  
					   // NULL: this application does not have a menu bar  
					   // hInstance: the first parameter from WinMain  
					   // NULL: not used in this application  
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//  
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)  
//  
//  PURPOSE:  Processes messages for the main window.  
//  
//  WM_PAINT    - Paint the main window  
//  WM_DESTROY  - post a quit message and return  
//  
//  
class ClassObserver
{
public:
	void handle(const Event& e)
	{

	}
};
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Prof !",	InputPolice->handleEvent(new EventClass_LMouse_Clicked("Hello, Prof !"));
);                 
	RECT rcClient;              
	POINT ptClientUL;              
	POINT ptClientLR;              
	static POINTS ptsBegin;       
	static POINTS ptsEnd;        
	static POINTS ptsPrevEnd;      
	static BOOL fPrevLine = FALSE; 
	wchar_t msg[32];

	TEXTMETRIC tm;            
	static DWORD dwCharX;     
	static DWORD dwCharY;      
	static DWORD dwClientX;    
	static DWORD dwClientY;   
	static DWORD dwLineLen;    
	static DWORD dwLines;       
	static int nCaretPosX = 0;  
	static int nCaretPosY = 0; 
	static int nCharWidth = 0; 
	static int cch = 0;        
	static int nCurChar = 0;    
	static PTCHAR pchInputBuf;
	int i, j;                 
	int cCR = 0;                
	int nCRIndex = 0;         
	int nVirtKey;              
	TCHAR szBuf[128];          
	TCHAR ch;                                  
	SIZE sz;                  
	COLORREF crPrevText;       
	COLORREF crPrevBk;         
	size_t* pcch= NULL;
	HRESULT hResult;
	ClassObserver classObserver;
	std::unique_ptr<InputClass> InputPolice = nullptr;
	std::string outmsg2;
	switch (message)
	{

	case WM_LBUTTONDOWN:

		// Capture mouse input. 

		SetCapture(hWnd);

		GetClientRect(hWnd, &rcClient);
		ptClientUL.x = rcClient.left;
		ptClientUL.y = rcClient.top;

		ptClientLR.x = rcClient.right + 1;
		ptClientLR.y = rcClient.bottom + 1;
		ClientToScreen(hWnd, &ptClientUL);
		ClientToScreen(hWnd, &ptClientLR);


		SetRect(&rcClient, ptClientUL.x, ptClientUL.y,
			ptClientLR.x, ptClientLR.y);
		ClipCursor(&rcClient); 

		ptsBegin = MAKEPOINTS(lParam);
		outmsg2 = "Mouse Pressed ";
		outmsg2 += "\n";
		OutputDebugStringA(outmsg2.c_str());
		return 0;

	case WM_MOUSEMOVE:


		if (wParam & MK_LBUTTON)
		{
			hdc = GetDC(hWnd);
			
			SetROP2(hdc, R2_NOTXORPEN);


			if (fPrevLine)
			{
				MoveToEx(hdc, ptsBegin.x, ptsBegin.y,
					(LPPOINT)NULL);
				LineTo(hdc, ptsPrevEnd.x, ptsPrevEnd.y);
			}


			ptsEnd = MAKEPOINTS(lParam);
			MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT)NULL);
			LineTo(hdc, ptsEnd.x, ptsEnd.y);
			

			fPrevLine = TRUE;
			ptsPrevEnd = ptsEnd;
			outmsg2 = "Mouse Moved ";
			outmsg2 += "\n";
			OutputDebugStringA(outmsg2.c_str());
			ReleaseDC(hWnd, hdc);
		}
		break;

	case WM_LBUTTONUP:


		fPrevLine = FALSE;
		ClipCursor(NULL);
		ReleaseCapture();
		
		return 0;


	case WM_CREATE:
		// Get the metrics of the current font. 

		hdc = GetDC(hWnd);
		GetTextMetrics(hdc, &tm);
		ReleaseDC(hWnd, hdc);

		// Save the average character width and height. 

		dwCharX = tm.tmAveCharWidth;
		dwCharY = tm.tmHeight;

		// Allocate a buffer to store keyboard input. 

		pchInputBuf = (LPTSTR)GlobalAlloc(GPTR,
			BUFSIZ * sizeof(TCHAR));
		
		return 0;

	case WM_SIZE:

		// Save the new width and height of the client area. 

		dwClientX = LOWORD(lParam);
		dwClientY = HIWORD(lParam);

		// Calculate the maximum width of a line and the 
		// maximum number of lines in the client area. 

		dwLineLen = dwClientX - dwCharX;
		dwLines = dwClientY / dwCharY;
		break;


	case WM_SETFOCUS:

		// Create, position, and display the caret when the 
		// window receives the keyboard focus. 

		CreateCaret(hWnd, (HBITMAP)1, 0, dwCharY);
		SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
		ShowCaret(hWnd);
		break;

	case WM_KILLFOCUS:

		// Hide and destroy the caret when the window loses the 
		// keyboard focus. 

		HideCaret(hWnd);
		DestroyCaret();
		break;

	case WM_CHAR:
		// check if current location is close enough to the
		// end of the buffer that a buffer overflow may
		// occur. If so, add null and display contents. 
		if (cch > BUFSIZ - 5)
		{
			pchInputBuf[cch] = 0x00;
			SendMessage(hWnd, WM_PAINT, 0, 0);
		}
		switch (wParam)
		{
		case 0x08:  // backspace 
		case 0x0A:  // linefeed 
		case 0x1B:  // escape 
			MessageBeep((UINT)-1);
			return 0;

		case 0x09:  // tab 

					// Convert tabs to four consecutive spaces. 

			for (i = 0; i < 4; i++)
				SendMessage(hWnd, WM_CHAR, 0x20, 0);
			return 0;

		case 0x0D:  // carriage return 

					// Record the carriage return and position the 
					// caret at the beginning of the new line.

			pchInputBuf[cch++] = 0x0D;
			nCaretPosX = 0;
			nCaretPosY += 1;
			break;

		default:    // displayable character 

			ch = (TCHAR)wParam;
			HideCaret(hWnd);

			// Retrieve the character's width and output 
			// the character. 

			hdc = GetDC(hWnd);
			GetCharWidth32(hdc, (UINT)wParam, (UINT)wParam,
				&nCharWidth);
			TextOut(hdc, nCaretPosX, nCaretPosY * dwCharY,
				&ch, 1);

			std::string outmsg1 = "Key Pressed is: ";
			outmsg1 += ch;
			outmsg1 += "\n";
			OutputDebugStringA(outmsg1.c_str());
			ReleaseDC(hWnd, hdc);

			// Store the character in the buffer.

			pchInputBuf[cch++] = ch;

			// Calculate the new horizontal position of the 
			// caret. If the position exceeds the maximum, 
			// insert a carriage return and move the caret 
			// to the beginning of the next line. 

			nCaretPosX += nCharWidth;
			if ((DWORD)nCaretPosX > dwLineLen)
			{
				nCaretPosX = 0;
				pchInputBuf[cch++] = 0x0D;
				++nCaretPosY;
			}
			nCurChar = cch;
			ShowCaret(hWnd);
			break;
		}
		SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:   // LEFT ARROW 

						// The caret can move only to the beginning of 
						// the current line. 

			if (nCaretPosX > 0)
			{
				//HideCaret(hWnd);
				ch = pchInputBuf[--nCurChar];
				hdc = GetDC(hWnd);
				GetCharWidth32(hdc, ch, ch, &nCharWidth);
				ReleaseDC(hWnd, hdc);
				nCaretPosX = max(nCaretPosX - nCharWidth,
					0);
				ShowCaret(hWnd);
			}
			break;

		case VK_RIGHT:  // RIGHT ARROW 

						// Caret moves to the right or, when a carriage 
						// return is encountered, to the beginning of 
						// the next line. 

			if (nCurChar < cch)
			{
				HideCaret(hWnd);

				// Retrieve the character to the right of 
				// the caret. If it's a carriage return, 
				// position the caret at the beginning of 
				// the next line. 

				ch = pchInputBuf[nCurChar];
				if (ch == 0x0D)
				{
					nCaretPosX = 0;
					nCaretPosY++;
				}

				// If the character isn't a carriage 
				// return, check to see whether the SHIFT 
				// key is down. If it is, invert the text 
				// colors and output the character. 

				else
				{
					hdc = GetDC(hWnd);
					nVirtKey = GetKeyState(VK_SHIFT);
					if (nVirtKey & FSHIFT)
					{
						crPrevText = SetTextColor(hdc,
							RGB(255, 255, 255));
						crPrevBk = SetBkColor(hdc,
							RGB(0, 0, 0));
						TextOut(hdc, nCaretPosX,
							nCaretPosY * dwCharY,
							&ch, 1);
						SetTextColor(hdc, crPrevText);
						SetBkColor(hdc, crPrevBk);
					}

					// Get the width of the character and 
					// calculate the new horizontal 
					// position of the caret. 

					GetCharWidth32(hdc, ch, ch, &nCharWidth);
					ReleaseDC(hWnd, hdc);
					nCaretPosX = nCaretPosX + nCharWidth;
				}
				nCurChar++;
				ShowCaret(hWnd);
				break;
			}
			break;

		case VK_UP:     // UP ARROW 
		case VK_DOWN:   // DOWN ARROW 
			MessageBeep((UINT)-1);
			return 0;

		case VK_HOME:   // HOME 

						// Set the caret's position to the upper left 
						// corner of the client area. 

			nCaretPosX = nCaretPosY = 0;
			nCurChar = 0;
			break;

		case VK_END:    // END  

						// Move the caret to the end of the text. 

			for (i = 0; i < cch; i++)
			{
				// Count the carriage returns and save the 
				// index of the last one. 

				if (pchInputBuf[i] == 0x0D)
				{
					cCR++;
					nCRIndex = i + 1;
				}
			}
			nCaretPosY = cCR;

			// Copy all text between the last carriage 
			// return and the end of the keyboard input 
			// buffer to a temporary buffer. 

			for (i = nCRIndex, j = 0; i < cch; i++, j++)
				szBuf[j] = pchInputBuf[i];
			szBuf[j] = TEXT('\0');

			// Retrieve the text extent and use it 
			// to set the horizontal position of the 
			// caret. 

			hdc = GetDC(hWnd);
			hResult = StringCchLength(szBuf, 128, pcch);
			if (FAILED(hResult))
			{
				// TODO: write error handler
			}
			GetTextExtentPoint32(hdc, szBuf, *pcch,
				&sz);
			nCaretPosX = sz.cx;
			ReleaseDC(hWnd, hdc);
			nCurChar = cch;
			break;

		default:
			break;
		}
		SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
		break;

	case WM_PAINT:
		if (cch == 0)       // nothing in input buffer 
			break;

		hdc = BeginPaint(hWnd, &ps);
		HideCaret(hWnd);

		// Set the clipping rectangle, and then draw the text 
		// into it. 

		SetRect(&rcClient, 0, 0, dwLineLen, dwClientY);
		DrawText(hdc, pchInputBuf, -1, &rcClient, DT_LEFT);
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		ShowCaret(hWnd);
		EndPaint(hWnd, &ps);
		break;

		// Process other messages. 
	case WM_DESTROY:
		PostQuitMessage(0);

		// Free the input buffer. 
		GlobalFree((HGLOBAL)pchInputBuf);
		UnregisterHotKey(hWnd, 0xAAAA);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
	test();
}
static int LS_PrintNumber(LuaState* state)
{
	LuaStack args(state);

	// Verify it is a number and print it.
	if (args[1].IsNumber()) {
		printf("%f\n", args[1].GetNumber());
	}
	// No return values.
	return 0;
}
void test()
{
	//Create state
	LuaStateOwner state;

	//With this the script can access our own C++ functions:
	state->GetGlobals().Register("PrintNumber", LS_PrintNumber);

	//Open test file:
	int iret = state->DoFile("test.lua");

	//Get a global variable:
	LuaObject sObj = state->GetGlobal("health");
	int mytest = sObj.GetInteger();

	//Update the value:
	sObj.AssignInteger(state, 30);
	//Get value again:
	mytest = sObj.GetInteger();

	//Call a function in lua:
	//LuaFunction<float> Add = state->GetGlobal("Add");
	//float myret = Add(3.14f, 0.0f);

}
