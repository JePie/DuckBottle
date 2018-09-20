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
}
int main()
{
	LPCTSTR engineName = "Tube.";
	IsOnlyInstance(engineName);
	DWORDLONG spaceNeeded = 3000000000;
	CheckStorage(spaceNeeded);
	DWORDLONG ramNeeded = 800000000;
	DWORDLONG vRamNeeded = 160000000;
	CheckMemory(ramNeeded, vRamNeeded);
	ReadCPUSpeed();

	system("pause");

	return 0;
}
