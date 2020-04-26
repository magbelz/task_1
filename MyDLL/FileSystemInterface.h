#pragma once
#include <iostream>

using namespace std;

class FileSystemInterface   //абстрактный класс фабричного метода
{    
	public:
        virtual void getDisk(string diskname) = 0;  //метод, выполняющийся в конкретных ФС 
};

