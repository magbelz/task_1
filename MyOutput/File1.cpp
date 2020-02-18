#pragma hdrstop
#pragma argsused
#include <tchar.h>
#ifdef _WIN32
#include <iostream>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "../MyDLL/Project1PCH1.h"

using namespace std;

 int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE MyDLL;
	typedef int(__stdcall*pfgetDisk)(FAT32_BootRecord* pBootRecord);
	pfgetDisk getDisk;

	if ((MyDLL = LoadLibrary("Project1")) == NULL) {
		 cout << "Cannot load DLL" << endl;
		 cin.get();
		 return 0;
	}

	if ((getDisk = (pfgetDisk)GetProcAddress(MyDLL, "getDisk")) == NULL) {
		 cout << "Cannot find DLL function" << endl;
		 cin.get();
		 return 0;
	}


	FAT32_BootRecord boot_rec;
	getDisk(&boot_rec);
	cout << "OEM Name: " << boot_rec.BS_OEMName << endl;
	cout << "Bytes per sector: " << boot_rec.BS_BytsPerSec << endl;
	cout << "Reserved sectors count: " << boot_rec.BS_RsvdSecCnt << endl;
	cin.get();

	FreeLibrary(MyDLL);
	return 0;
}
