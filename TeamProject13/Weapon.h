#pragma once
#include "Item.h"
#include <iostream>

enum class WeaponType { Sword, Shield, DoubleStab, MagicStaff };

class Weapon : public Item {
private:
    int power;
    int cost;
    WeaponType type;

public:
    Weapon(std::string n, int p, WeaponType t, int c, int pr = 0)
        : Item(n, pr), power(p), type(t), cost(c) {
    }

    // 무기 사용 로직 (장착 또는 즉시 공격)
    virtual void use(Player* player) override {
        std::cout << name << "을(를) 사용하여 공격을 준비합니다! (코스트: " << cost << ")\n";
    }

    int GetPower() const { return power; }
    int GetCost() const { return cost; }
};