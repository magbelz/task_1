#pragma hdrstop
#pragma argsused

#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "Project1PCH1.h"

using namespace std;


int __stdcall getDisk(FAT32_BootRecord* pBootRecord)
   {
	WCHAR *fileName = L"\\\\.\\M:";

	HANDLE fileHandle = CreateFileW(
		fileName,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if(fileHandle == INVALID_HANDLE_VALUE)
	{

		cout << "Invalid file handle!" << endl;
	}

	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = 0;

	unsigned long currentPosition = SetFilePointer(
		fileHandle,
		sectorOffset.LowPart,
		&sectorOffset.HighPart,
		FILE_BEGIN
	);
	if (currentPosition != sectorOffset.LowPart)
	{

		cout << "Current position is wrong!" << endl;
	}
	BYTE dataBuffer[1024];
	DWORD bytesToRead = 1024;
	DWORD bytesRead;

	bool readResult = ReadFile(
		fileHandle,
		dataBuffer,
		bytesToRead,
		&bytesRead,
		NULL
	);
	if (!readResult || bytesRead != bytesToRead)
	{
	   cout << "Read error!" << endl;
	}

	*pBootRecord = *reinterpret_cast<FAT32_BootRecord*>(dataBuffer);

	CloseHandle (fileHandle);

	return 1;
   }

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

