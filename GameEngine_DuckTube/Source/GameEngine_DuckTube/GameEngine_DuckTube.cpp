//John Paul Valdez 101055854
//Minxu Huang 101074668
//Puraj Desai 101093244

#include "stdafx.h"
#include <atlhandler.h>
#include <iostream>

using namespace std;

bool instancess(LPCTSTR Mutex) {

	HANDLE handles = CreateMutex(NULL, TRUE, Mutex);
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		cout << "more than one instances is running" << endl;
		return false;
	}
	else
	{
		cout << "no multiple instances is running" << endl;
	}
	return true;
	CloseHandle(handles);
}


int main()
{

	ULARGE_INTEGER FreeSpaceAvailable;
	ULARGE_INTEGER TotalSpace;
	ULARGE_INTEGER TotalFreeSpace;

	::GetDiskFreeSpaceEx(_T("c:\\"),                 
		&FreeSpaceAvailable,
		&TotalSpace,
		&TotalFreeSpace);

	const LONGLONG nGBFactor =1024*1024*1024; // gb 

	// get free space in GB.
	double dGBFreSpace
		= (double)(LONGLONG)TotalFreeSpace.QuadPart / nGBFactor;
	long neededSpace = 300;

	//outputs
	instancess("Hello world");
	cout << dGBFreSpace << endl;
	if (dGBFreSpace * 1000 < neededSpace) {
		cout << "Not enough free space!"<<endl;
	}
	else if (dGBFreSpace * 1000 > neededSpace) {
		cout << "There is enough free space!" << endl;
	}
	return 0;
}
