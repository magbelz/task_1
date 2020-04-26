#pragma once
#pragma hdrstop
#pragma argsused
#include "FileSystemFactory.h"
#include <string>

using namespace std;

class FileSystemFactory: public Factory  //выбор конкретной фабрики ФС
{
	public:
		FileSystemInterface* getFS(const string name)
        {
        	FileSystemInterface* fs;
            if (name == "FAT32")
            {   
                fs = new FAT32;
            }
            else if (name == "NTFS")
            {
//              Not implemented yet
                fs = NULL;
            }
            else
            {
//          	Exit for unknown file systems  
                fs = NULL;
            }
            return fs;
        }
};

   // экпортируем класс
extern "C" __declspec(dllexport) Factory* __stdcall getFileSystemFactory()
{
    return new FileSystemFactory;
}


extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

