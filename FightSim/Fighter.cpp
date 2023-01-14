#include "Fighter.h"

/*Конструктор класса Fighter*/
Fighter::Fighter(std::string name, float hp, float dmg, int cc, int cm) {
	this->name = name;
	this->maxHP = hp;
	this->hp = hp;
	this->dmg = dmg;
	this->cc = cc;
	this->cm = cm;
	isDeath = false;
	wins = 0;
}


/*Деструктор класса Fighter*/
Fighter::~Fighter() {

}


/*Расчет силы удара с учетем шанса и силы критического попадания*/
float Fighter::CalculateDamage() {
	std::random_device device;
	std::mt19937 range(device());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 100);
	
	if (dist6(range) <= cc && cc != 0) { return (dmg * cm); }
	else { return dmg; }
}


/*Метод удара противника*/
void Fighter::HitEmeny(Fighter& enemy) {
	enemy.hp -= CalculateDamage();
	if (enemy.hp <= 0) { enemy.isDeath = true; }
}


/*Статический метод боя между двумя бойцами*/
int Fighter::Fight(Fighter& fighter1, Fighter& fighter2, int numberRound) {
	fighter1.HitEmeny(fighter2);
	fighter2.HitEmeny(fighter1);
	numberRound++;

	if (!fighter1.isDeath && fighter2.isDeath) {
		fighter1.wins++;
	}
	if (fighter1.isDeath && !fighter2.isDeath) {
		fighter2.wins++;
	}

	if (fighter1.isDeath || fighter2.isDeath) {
		return numberRound;
	}

	return Fight(fighter1, fighter2, numberRound);
}
