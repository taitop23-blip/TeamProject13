// Monster.h

#pragma once
#include <string>

class Monster {
private:
	std::string name;
	int pressure;
	int maxPressure;
	int atk;
	int def;
public:
	Monster(std::string name, int pressure, int atk, int def) { this->name = name; this->pressure = pressure; maxPressure = pressure; 
																this->atk = atk; this->def = def; }
	~Monster() {}
	std::string getName() const{ return name; }
	int getPressure() const{ return pressure; }
	int getMaxPressure() const{ return maxPressure; }
	int getAtk() const{ return atk; }
	int getDef() const{ return def; }
	void takeDamage(int damage) { pressure -= damage; }
};