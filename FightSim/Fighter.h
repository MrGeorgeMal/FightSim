#pragma once
#ifndef ClassFigher

#include <random>
#include <string>

#define ClassFigher
#endif // !ClassFigher

class Fighter
{
private:
	std::string name;
	float maxHP;
	float hp;
	float dmg;
	int cc;
	int cm;
	bool isDeath;
	int wins;

public:
	/*Конструктор класса Figher*/
	Fighter(std::string name, float hp, float dmg, int cc, int cm);

	/*Деструктор класса Figher*/
	~Fighter();

	float CalculateDamage();
	void HitEmeny(Fighter& enemy);
	void Reborn() { this->hp = this->maxHP; isDeath = false; }

	static int Fight(Fighter& fighter1, Fighter& fighter2, int numberRound);

	std::string GetName() { return name; }
	float GetMaxHP() { return maxHP; }
	float GetHP() { return hp; }
	float GetDMG() { return dmg; }
	int GetCC() { return cc; }
	int GetCM() { return cm; }
	bool GetIsDeath() { return isDeath; }
	int GetWins() { return wins; }

	void SetWins(int count) { this->wins = count; }
};

