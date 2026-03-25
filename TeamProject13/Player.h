#pragma once
#include <string>
#include <vector>

class Item; // 전방 선언

class Player {
private:
    std::string name;
    // 창욱님의 브레인스토밍 반영 (HP, MP, 공격, 방어, 속도)
    int hp, maxHp;
    int mp, maxMp;
    int atk, def, speed;

    // 성장 및 재화
    int level, exp, gold;

    // 에너지 시스템 나중에 Mana 또는 Cost로 이름 바꾸기 가능
    int currentEnergy, maxEnergy;

    // 다형성 인벤토리
    std::vector<Item*> inventory;

public:
    Player(std::string n) : name(n), level(1), exp(0), gold(0) {
        hp = maxHp = 100;
        mp = maxMp = 50;
        atk = 10; def = 5; speed = 10;
        maxEnergy = 3; currentEnergy = 3;
    }

    void Heal(int amount) {
        hp += amount;
        if (hp > maxHp) hp = maxHp;
    }

    void AddItem(Item* item) { inventory.push_back(item); }
    void UseEnergy(int amount) { currentEnergy -= amount; }

    // Getter 함수들
    int GetLevel() const { return level; }
    int GetHp() const { return hp; }
    int GetAtk() const { return atk; }
    int GetEnergy() const { return currentEnergy; }
};