// BattleManager.h

#pragma once

#include "Player.h"
#include "Monster.h"
#include "SkillManager.h"


class BattleManager
{
	private:
		SkillManager* skillManager;

		bool isRunningAway;

	public:
		BattleManager();

		void SetSkillManager(SkillManager* sm);

		bool StartBattle(Player& player, Monster& monster);

	private:
		void DisplayStatus(const Player& player, const Monster& monster);	// 전투시 플레이어와 몬스터의 상태표시
		void DisplayMenu();													// 플레이어의 선택지
		void PlayerTurn(Player& player, Monster& monster);					// 배틀 플레이어의 턴
		void MonsterTurn(Player& player, Monster& monster);					// 배틀 빌런의 턴

		bool IsBattleOver(const Player& player, const Monster& monster);	// 배틀 종료

		void ProcessDefeat(Player& player, Monster& monster);				// 플레이어가 패배
		void ProcessVictory(Player& player, Monster& monster);				// 플레이어가 승리 또는 빌런의 승리
		void ProcessRunAway(Player& player, Monster& monster);												// 도망 처리
};

