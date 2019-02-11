/*###############################################################
#																#
#		Copyright 2019 Duck Trophy All Rights Reserved.			#
# Developed by Puraj Desai, John Paul Valdez and Minxu Huang    #
#                                                               #
################################################################*/
#include "pch.h"
#include "Initialise.h"
#include <iostream>
#include <windows.h>
#include "windows.h"
#include <string>
#include <sstream>
#include<SFML/Graphics.hpp>
#include"tubeStd.h"

using namespace std;
duckTubeEngine::~duckTubeEngine()
{

}


void duckTubeEngine::Run()
{
	Engine engine;
	while (engine.Window.isOpen())
	{
		sf::Event event;
		while (engine.Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				engine.Window.close();
			}
		}

	}
}


duckTubeEngine::duckTubeEngine()
{


}


bool duckTubeEngine::Initialize()
{
	if (!SystemRequirements())
		return false;
	else {
		CheckMemory();
		HasFreeDiskSpace();
		ReadCPUSpeed();
		GraphicsSystem::Instance()->CreateWin();
	}
	return true;
}



bool duckTubeEngine::SystemRequirements()
{
	if (!HasFreeDiskSpace())
		return false;

	return true;
}
bool  duckTubeEngine::CheckMemory() {
	bool result = false;
	DWORDLONG physicalRAMNeeded = 512;
	DWORDLONG virtualRAMNeeded = 1024;
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	std::string msgTxt;

	cout << "\nPhysical & Virtual Memory Check:\n" << endl;
	cout << "\tRAM Requested: " << physicalRAMNeeded << "." << endl;
	cout << "\tVirtual RAM Requested: " << virtualRAMNeeded << "." << endl;
	cout << "\tThe total physical RAM available: " << status.ullAvailPhys << "." << endl;
	cout << "\tThe total virtual RAM avaialable: " << status.ullAvailVirtual << ".\n" << endl;

	if (status.ullAvailPhys < physicalRAMNeeded) {
		cout << "\tMemory Check Failure : Not enough physical memory.\n" << endl;

		result = false;
	}

	if (status.ullAvailVirtual < virtualRAMNeeded) {
		cout << "\tMemory Check Failure : Not enough virtual memory.\n" << endl;

		result = false;
	}
	result = true;
	return result;
}
bool duckTubeEngine::ReadCPUSpeed() {
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	DWORD strType = REG_SZ;
	char myBuff[256];
	HKEY hKey;
	bool result = false;
	std::string msgTxt;
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0,
		KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS) {
		// query the key:
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)
			&dwMHz, &BufSize);
		cout << "CPU Speed aand Architecture:\n" << endl;
		cout << "\t" << dwMHz << " MHz CPU Speed" << endl;
	}

	long mError = RegQueryValueEx(hKey, "ProcessorNameString", NULL, &strType, (LPBYTE)&myBuff, &BufSize);

	while (mError == ERROR_MORE_DATA) {
		BufSize++;
		mError = RegQueryValueEx(hKey, "ProcessorNameString", NULL, &strType, (LPBYTE)&myBuff, &BufSize);
	}

	cout << "\t" << myBuff << "\n" << endl;

	return result;
}

bool duckTubeEngine::HasFreeDiskSpace()
{

	bool result = false;
	int requiredSpace = 300; //program space spec requirement in MB.
	ULARGE_INTEGER ulFreeSpace;
	ULARGE_INTEGER ulTotalSpace;
	ULARGE_INTEGER ulTotalFreeSpace;
	std::string msgTxt;

	GetDiskFreeSpaceEx("C:", &ulFreeSpace, &ulTotalSpace, &ulTotalFreeSpace);

	int totalFreeSpaceInMb = (ulTotalFreeSpace.QuadPart / (1024 * 1024));

	if (requiredSpace > totalFreeSpaceInMb) {
		cout << "\tCheck Storage Failure: Not enough physical storage.\n" << endl;
		result = false;
	}
	else {
		cout << "Disk Space Check: \n" << endl;
		cout << "\tRequested " << requiredSpace << " bytes needed." << endl;
		cout << "\tThere are " << (DWORDLONG)totalFreeSpaceInMb << " available bytes." << endl;

		result = true;
	}

	return result;
}