#pragma once
#include "FileSystemInterface.h"

class FAT32: public FileSystemInterface   //������� ���������� ��
{
 	public:
        FAT32() {};
    	~FAT32() {};
        void getDisk(string diskname);
};



