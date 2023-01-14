#include "GameMode.h"

std::vector<std::string> GameMode::nameVsName(0);
std::vector<int> GameMode::draw(0);
std::vector<int> GameMode::winFighter1(0);
std::vector<int> GameMode::winFighter2(0);

std::vector<float> GameMode::afterFightMaxHP1(0);
std::vector<float> GameMode::afterFightMinHP1(0);
std::vector<float> GameMode::afterFightAvgHP1(0);
std::vector<float> GameMode::afterFightMaxHP2(0);
std::vector<float> GameMode::afterFightMinHP2(0);
std::vector<float> GameMode::afterFightAvgHP2(0);
std::vector<int> GameMode::numberLastRoundMax(0);
std::vector<int> GameMode::numberLastRoundMin(0);
std::vector<int> GameMode::numberLastRoundAvg(0);


/**/
void GameMode::OneVsOne(Fighter& fighter1, Fighter& fighter2, int countFights) {
	for (int i = 0; i < countFights; i++) {
		int numberLastRound = Fighter::Fight(fighter1, fighter2, 0);


		if (numberLastRound > numberLastRoundMax[numberLastRoundMax.size() - 1]) {
			numberLastRoundMax[numberLastRoundMax.size() - 1] = numberLastRound;
		}
		if (numberLastRound < numberLastRoundMin[numberLastRoundMin.size() - 1]) {
			numberLastRoundMin[numberLastRoundMin.size() - 1] = numberLastRound;
		}
		numberLastRoundAvg[numberLastRoundAvg.size() - 1] += numberLastRound;


		if (fighter1.GetHP() > afterFightMaxHP1[afterFightMaxHP1.size() - 1]) {
			afterFightMaxHP1[afterFightMaxHP1.size() - 1] = fighter1.GetHP();
		}
		if (fighter1.GetHP() < afterFightMinHP1[afterFightMinHP1.size() - 1]) {
			afterFightMinHP1[afterFightMinHP1.size() - 1] = fighter1.GetHP();
		}
		afterFightAvgHP1[afterFightAvgHP1.size() - 1] += fighter1.GetHP();


		if (fighter2.GetHP() > afterFightMaxHP2[afterFightMaxHP2.size() - 1]) {
			afterFightMaxHP2[afterFightMaxHP2.size() - 1] = fighter2.GetHP();
		}
		if (fighter2.GetHP() < afterFightMinHP2[afterFightMinHP2.size() - 1]) {
			afterFightMinHP2[afterFightMinHP2.size() - 1] = fighter2.GetHP();
		}
		afterFightAvgHP2[afterFightAvgHP2.size() - 1] += fighter2.GetHP();


		fighter1.Reborn();
		fighter2.Reborn();
	}

	numberLastRoundAvg[numberLastRoundAvg.size() - 1] = numberLastRoundAvg[numberLastRoundAvg.size() - 1] / countFights;
	afterFightAvgHP1[afterFightAvgHP1.size() - 1] = afterFightAvgHP1[afterFightAvgHP1.size() - 1] / countFights;
	afterFightAvgHP2[afterFightAvgHP2.size() - 1] = afterFightAvgHP2[afterFightAvgHP2.size() - 1] / countFights;
}


/**/
void GameMode::DeathMatch(std::vector<Fighter>& fighters, int countFights) {
	for (int i = 0; i < fighters.size() - 1; i++)
	{
		for (int j = i + 1; j < fighters.size(); j++) {
			int f1f2 = std::ceil(fighters[i].GetHP() / fighters[j].GetDMG());
			int f2f1 = std::ceil(fighters[j].GetHP() / fighters[i].GetDMG());
			
			numberLastRoundMax.push_back(0);
			numberLastRoundMin.push_back(std::max(f1f2, f2f1));
			numberLastRoundAvg.push_back(0);
			afterFightMaxHP1.push_back(0);
			afterFightMinHP1.push_back(fighters[i].GetMaxHP());
			afterFightAvgHP1.push_back(0);
			afterFightMaxHP2.push_back(0);
			afterFightMinHP2.push_back(fighters[j].GetMaxHP());
			afterFightAvgHP2.push_back(0);

			OneVsOne(fighters[i], fighters[j], countFights);
			nameVsName.push_back(fighters[i].GetName() + " VS " + fighters[j].GetName());
			draw.push_back(countFights - fighters[i].GetWins() - fighters[j].GetWins());
			winFighter1.push_back(fighters[i].GetWins());
			winFighter2.push_back(fighters[j].GetWins());
			fighters[i].SetWins(0);
			fighters[j].SetWins(0);
		}
	}
}