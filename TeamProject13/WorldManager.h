#pragma once

#include "EventManager.h"
#include "Monster.h"
#include "ShopManager.h"

class Player;

class WorldManager {
private:
    int dangerLevel;
    const int maxProgress = 100;
    bool isFinalBossAppeared;
    bool bonusLvl3;
    bool bonusLvl6;
    bool bonusLvl9;
    EventManager eventManager;
    ShopManager shopManager;

    void ShowActionMenu(const Player& p) const;
    void ShowStatus(const Player& p) const;
    Monster CreateEncounterMonster(const Player& p) const;
    void HandleCollapse(Player& p, const char* reason);
    void CheckLevelBonus(Player& p);

public:
    WorldManager();
    bool RunWorkLoop(Player& p);
    void FocusWork(Player& p);
    void DrinkCoffee(Player& p);
    void WatchYoutube(Player& p);
    void Stretching(Player& p);
    bool CheckEncounter();
    void ResetDanger() { dangerLevel = 0; }
    int GetDanger() const { return dangerLevel; }
    bool IsReadyForFinalBoss(int currentProgress);
    void ShowGameObjective() const;
};
