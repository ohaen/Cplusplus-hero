#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class FileM
{
public:
	int saveGold;
	
	void WriteFile(string fileName, int gold);
	void ReadFile(string fileName);


};

