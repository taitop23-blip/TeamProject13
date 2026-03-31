// Player.h

#pragma once

#include <string>
#include <vector>
#include "Item.h"

class Player {
private:
    int level;
    int exp;
    int maxExp;
    std::string name;

    int mental;
    int maxMental;
    int focus;
    int maxFocus;
    int atk;
    int def;

    int progress;
    int life;
    int gold;

    int tempAtkBonus;
    int tempDefBonus;
    std::vector<Item> inventory;



public:
    Player();
    Player(const std::string& name, int mental, int focus, int atk, int def);

    //Get
    const std::string& GetName() const { return name; }
    int GetLevel() const { return level; }
    int GetExp() const { return exp; }
    int GetMaxExp() const { return maxExp; }
    int GetMental() const { return mental; }
    int GetMaxMental() const { return maxMental; }
    int GetFocus() const { return focus; }
    int GetMaxFocus() const { return maxFocus; }
    int GetProgress() const { return progress; }
    int GetLife() const { return life; }
    int GetGold() const { return gold; }
    int GetAtk() const { return atk + tempAtkBonus; }
    int GetDef() const { return def + tempDefBonus; }
    int GetBaseAtk() const { return atk; }
    int GetBaseDef() const { return def; }

    //Add
    void AddMental(int val);
    void AddFocus(int val);
    void AddProgress(int val);
    void AddGold(int val);
    void AddExp(int val);
    void AddAtk(int val);
    void AddDef(int val);
    void AddLife(); //


    //Set
    void SubMental(int val);
    void SubFocus(int val);
    void SubLife();
    void SubGold(int val);
    void SubProgress(int val);
    bool SpendGold(int val);

    int getHP() const { return mental; }
    void takeDamage(int damage) { SubMental(damage); }
    bool IsDead() const { return life <= 0; }
    bool HasCollapsed() const { return mental <= 0; }

    void RestoreFullMental();
    void RestoreFullFocus();
    void RestoreAll();
    void RecoverAfterCollapse();

    void AddTemporaryAtk(int val);
    void AddTemporaryDef(int val);
    void ClearTemporaryBattleBonuses();

    // 스킬 보너스 능력치 초기화 함수
    void AddTempDef(int val);
    void ResetTempStats();
    int GetTotalDef() const;

    void AddItem(const Item& item);
    bool HasItems() const { return !inventory.empty(); }
    const std::vector<Item>& GetInventory() const { return inventory; }
    const Item* GetItem(std::size_t index) const;
    bool RemoveItem(std::size_t index);
    void PrintInventory() const;
    void ShowCurrentStatus() const;
    bool TryAutoRevive();
};
