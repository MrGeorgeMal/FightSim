#pragma once
#ifndef ClassFileManager

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "GameMode.h"

#define ClassFileManager
#endif // !ClassFileManager

class FileManager
{
private:
	std::string pathForRead;
	std::string pathForWrite;
	std::ifstream fileForRead;
	std::ofstream fileForWrite;

	std::vector<std::string> name;
	std::vector<float> hp;				//Hit Point
	std::vector<float> dmg;				//Damage
	std::vector<int> cc;				//Crit Chanse
	std::vector<int> cm;				//Crit Multiplay

public:
	FileManager();
	~FileManager();

	bool ReadFromFile(std::string pathForRead);
	bool WriteToFile(std::string pathForWrite);

	int GetCountFighters() { return name.size(); }
	std::string GetName(int indexFigher) { return this->name[indexFigher]; }
	float GetHP(int indexFigher) { return this->hp[indexFigher]; }
	float GetDMG(int indexFigher) { return this->dmg[indexFigher]; }
	int GetCC(int indexFigher) { return this->cc[indexFigher]; }
	int GetCM(int indexFigher) { return this->cm[indexFigher]; }
};

