#pragma once
#include "FAT32.h"
#include <string>

using namespace std;

class Factory {   //����������� ������� (������� ������)
public:
	virtual FileSystemInterface* getFS(const string name) = 0;
};

