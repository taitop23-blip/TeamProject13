// BattleManager.h

#pragma once

#include "Player.h"
#include "Monster.h"
#include "SkillManager.h"

#include <vector>

enum class BattleResult
{
    Victory,
    Collapse,
    Defeat,
    RunAway,
    Revived
};

class BattleManager
{
private:
    SkillManager* skillManager;
    bool isRunningAway;
    std::vector<SkillManager> skills;

public:
    BattleManager();

    void SetSkillManager(SkillManager* sm);

    BattleResult StartBattle(Player& player, Monster& monster);

private:
    void DisplayStatus(const Player& player, const Monster& monster);
    void DisplayMenu();
    void DisplaySkillMenu(const Player& player) const;

    void PlayerTurn(Player& player, Monster& monster);
    bool UseSkill(Player& player, Monster& monster);
    bool UseItem(Player& player);

    void MonsterTurn(Player& player, Monster& monster);

    bool IsBattleOver(const Player& player, const Monster& monster);

    void ProcessCollapse(Player& player, Monster& monster);
    void ProcessDefeat(Player& player, Monster& monster);
    void ProcessVictory(Player& player, Monster& monster);
    void ProcessRunAway(Player& player, Monster& monster);
    Item CreateRewardItem(const Monster& monster) const;
};

