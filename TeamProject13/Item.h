#pragma once
#include <string>

class Player; // 전방 선언

class Item {
protected:
    std::string name;
    int price;

public:
    Item(std::string n, int p) : name(n), price(p) {}
    virtual ~Item() {}

    // 순수 가상 함수: 자식들(Weapon, Potion)이 각자 구현해야 함
    virtual void use(Player* player) = 0;

    std::string GetName() const { return name; }
    int GetPrice() const { return price; }
};