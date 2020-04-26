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
    //получение типа ФС - строка char
	GetVolumeInformation(diskname.c_str(), NameBuffer, sizeof(NameBuffer), &VSNumber, &MCLength,
    &FileSF, SysNameBuffer, sizeof(SysNameBuffer));
    cout << "Detected file system: " << SysNameBuffer << endl;
    
	typedef Factory* (*getFileSystem)(); //указатель функции
    //загружаем dll
    //реализована проверка на загрузку
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
        	Factory* FSF = FS_Factory(); //инициализируем класс
            FileSystemInterface* FileSystem = FSF->getFS(SysNameBuffer); //вызов функции и передача типа ФС
            if (!FileSystem) {
                cout << "We couldn't get information for specified file system. Sorry!" << endl;  //если ФС еще не разработана
                FreeLibrary(DLL);
                system("pause");
                return 0;
            }
            else
            //в случае если класс для ФС найден происходит передача буквы диска и вывод информации
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
