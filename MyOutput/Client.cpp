#pragma hdrstop
#pragma argsused
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include "../MyDLL/FileSystemFactory.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string diskname;
    cout << "Enter disk letter (f.e. C:\\\\ or D:/): " ;
	cin >> diskname;
    
    char NameBuffer[MAX_PATH];
	char SysNameBuffer[MAX_PATH];
	DWORD VSNumber;
	DWORD MCLength;
	DWORD FileSF;
    //��������� ���� �� - ������ char
	GetVolumeInformation(diskname.c_str(), NameBuffer, sizeof(NameBuffer), &VSNumber, &MCLength,
    &FileSF, SysNameBuffer, sizeof(SysNameBuffer));
    cout << "Detected file system: " << SysNameBuffer << endl;
    
	typedef Factory* (*getFileSystem)(); //��������� �������
    //��������� dll
    //����������� �������� �� ��������
	HINSTANCE DLL = LoadLibrary("Project1.dll"); 
    if (DLL != NULL) 
    {
     	getFileSystem FS_Factory = (getFileSystem)GetProcAddress(DLL, "getFileSystemFactory");
        if (!FS_Factory) 
        {
        	cout << "Cannot find DLL function" << endl;
            FreeLibrary(DLL);
            cin.get();
            return 0;
        }
        else 
        {	
        	Factory* FSF = FS_Factory(); //�������������� �����
            FileSystemInterface* FileSystem = FSF->getFS(SysNameBuffer); //����� ������� � �������� ���� ��
            if (!FileSystem) {
                cout << "We couldn't get information for specified file system. Sorry!" << endl;  //���� �� ��� �� �����������
                FreeLibrary(DLL);
                system("pause");
                return 0;
            }
            else
            //� ������ ���� ����� ��� �� ������ ���������� �������� ����� ����� � ����� ����������
            {
                diskname.resize(2);
                FileSystem->getDisk(diskname);
                cin.get();
                FreeLibrary(DLL);
            }
        }
    }
    else
    {
		cout << "Cannot load DLL" << endl;
        cin.get();                            
        return 0;
    }

	return 0;
}
