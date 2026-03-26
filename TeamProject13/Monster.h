// Monster.h

#pragma once
#include <string>

class Monster {
private:
	std::string name;
	int pressure;
public:
	Monster(std::string name, int pressure) { this->name = name; this->pressure = pressure; }
	~Monster() {}
	std::string getName() { return name; }
	int getHP() { return pressure; }
	void takeDamage(int damage) { pressure -= damage; }
};