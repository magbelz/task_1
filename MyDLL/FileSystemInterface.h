#pragma once
#include <iostream>

using namespace std;

class FileSystemInterface   //����������� ����� ���������� ������
{    
	public:
        virtual void getDisk(string diskname) = 0;  //�����, ������������� � ���������� �� 
};

