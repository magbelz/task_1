#pragma once
#include "FileSystemInterface.h"

class FAT32: public FileSystemInterface   //фабрика конкретной ФС
{
 	public:
        FAT32() {};
    	~FAT32() {};
        void getDisk(string diskname);
};



