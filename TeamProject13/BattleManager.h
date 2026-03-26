// BattleManager.h

#pragma once

#include "Player.h"
#include "Monster.h"
#include "SkillManager.h"


class BattleManager
{
	private:
		SkillManager* skillManager;

	public:
		BattleManager();

		void SetSkillManager(SkillManager* sm);

		void StartBattle(Player& player, Monster& monster);

	private:
		void DisplayStatus(const Player& player, const Monster& monster);
		void DisplayMenu();
		void PlayerTurn(Player& player, Monster& monster);
		void MonsterTurn(Player& player, Monster& monster);

		bool IsBattleOver(const Player& player, const Monster& monster);

		void ProcessVictory(Player& player, Monster& monster);
		void ProcessDefeat(Player& player);
};

