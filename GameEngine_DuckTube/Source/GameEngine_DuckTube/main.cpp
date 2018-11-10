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


using namespace std;

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, World!");                 
	RECT rcClient;                 // client area rectangle 
	POINT ptClientUL;              // client upper left corner 
	POINT ptClientLR;              // client lower right corner 
	static POINTS ptsBegin;        // beginning point 
	static POINTS ptsEnd;          // new endpoint 
	static POINTS ptsPrevEnd;      // previous endpoint 
	static BOOL fPrevLine = FALSE; // previous line flag 
	wchar_t msg[32];
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
			ReleaseDC(hWnd, hdc);
		}
		break;

	case WM_LBUTTONUP:


		fPrevLine = FALSE;
		ClipCursor(NULL);
		ReleaseCapture();
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SYSKEYDOWN:
		swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
		OutputDebugString((LPCSTR)msg);
		break;

	case WM_SYSCHAR:
		swprintf_s(msg, L"WM_SYSCHAR: %c\n", (wchar_t)wParam);
		OutputDebugString((LPCSTR)msg);
		break;

	case WM_SYSKEYUP:
		swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
		OutputDebugString((LPCSTR)msg);
		break;

	case WM_KEYDOWN:
		swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
		OutputDebugString((LPCSTR)msg);
		break;

	case WM_KEYUP:
		swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
		OutputDebugString((LPCSTR)msg);
		break;

	case WM_CHAR:
		swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)wParam);
		OutputDebugString((LPCSTR)msg);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.  
		// For this introduction, we just print out "Hello, World!"  
		// in the top left corner.  
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End application-specific layout section.  

		EndPaint(hWnd, &ps);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
