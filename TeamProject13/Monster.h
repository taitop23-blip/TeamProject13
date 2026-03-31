// Monster.h

#pragma once
#include "Player.h"
#include <string>

class Monster {
private:
	std::string name;
	int pressure;
	int maxPressure;
	int atk;
	int def;
	int rewardExp;
	int rewardGold;
	bool defeated = false;
public:
	Monster(std::string name, int pressure, int atk, int def, int rewardExp, int rewardGold) {
		this->name = name; this->pressure = pressure; maxPressure = pressure;
		this->atk = atk; this->def = def; this->rewardExp = rewardExp; this->rewardGold = rewardGold;
	}
	~Monster() {}
	std::string GetName() const { return name; }
	int GetPressure() const { return pressure; }
	int GetMaxPressure() const { return maxPressure; }
	int GetAtk() const { return atk; }
	int GetDef() const { return def; }
	int GetExp() const { return rewardExp; }
	int GetGold() const { return rewardGold; }
	void TakeDamage(int damage);
	void SetPressure(int pressure) { this->pressure = pressure; }
	int MonsterAction(Player& player);
	bool IsDefeated() { return defeated; }
};