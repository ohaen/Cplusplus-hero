#include "FileM.h"

void FileM::WriteFile(string fileName, int gold)
{
	ofstream fout(fileName);

	fout << gold;

}

void FileM::ReadFile(string fileName)
{
	ifstream fin(fileName);


	fin >> saveGold;
}
