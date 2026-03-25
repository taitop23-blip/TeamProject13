#pragma once
#include <string>

class Monster {
private:
    std::string name;
    int hp, maxHp, atk, def;

public:
    Monster(std::string n, int playerLevel);

    int GetAtk() const { return atk; }
    void TakeDamage(int damage) {
        int finalDamage = damage - def;
        if (finalDamage < 0) finalDamage = 0;
        hp -= finalDamage;
    }
};