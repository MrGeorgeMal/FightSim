#pragma once
#include <vector>
#include "Fighter.h"

class GameMode
{
private:
	static std::vector<std::string> nameVsName;
	static std::vector<int> draw;
	static std::vector<int> winFighter1;
	static std::vector<int> winFighter2;

	static std::vector<float> afterFightMaxHP1;
	static std::vector<float> afterFightMinHP1;
	static std::vector<float> afterFightAvgHP1;
	static std::vector<float> afterFightMaxHP2;
	static std::vector<float> afterFightMinHP2;
	static std::vector<float> afterFightAvgHP2;
	static std::vector<int> numberLastRoundMax;
	static std::vector<int> numberLastRoundMin;
	static std::vector<int> numberLastRoundAvg;

public:
	static void OneVsOne(Fighter& fighter1, Fighter& fighter2, int countFights);
	static void DeathMatch(std::vector<Fighter>& fighters, int countFights);

	static std::vector<std::string> GetNameVsName() { return nameVsName; }
	static std::vector<int> GetDraw() { return draw; }
	static std::vector<int> GetWinFighter1() { return winFighter1; }
	static std::vector<int> GetWinFighter2() { return winFighter2; }
	static std::vector<float> GetAfterFightMaxHP1() { return afterFightMaxHP1; }
	static std::vector<float> GetAfterFightMinHP1() { return afterFightMinHP1; }
	static std::vector<float> GetAfterFightAvgHP1() { return afterFightAvgHP1; }
	static std::vector<float> GetAfterFightMaxHP2() { return afterFightMaxHP2; }
	static std::vector<float> GetAfterFightMinHP2() { return afterFightMinHP2; }
	static std::vector<float> GetAfterFightAvgHP2() { return afterFightAvgHP2; }
	static std::vector<int> GetNumberLastRoundMax() { return numberLastRoundMax; }
	static std::vector<int> GetNumberLastRoundMin() { return numberLastRoundMin; }
	static std::vector<int> GetNumberLastRoundAvg() { return numberLastRoundAvg; }
};

