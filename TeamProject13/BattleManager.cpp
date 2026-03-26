// BattleManager.cpp

#include "BattleManager.h"

void BattleManager::StartBattle(Player& player, Monster& monster)
{
	while (true)
	{
		DisplayStatus(player, monster);
		DisplayMenu();

		PlayerTurn(player, monster);

		if (IsBattleOver(player, monster))
			break;

		MonsterTurn(player, monster);

		if (IsBattleOver(player, monster))
			break;
	}

	if (player.getHP() <= 0)
		ProcessDefeat(player);
	else if (monster.getHP() <= 0)
		ProcessVictory(player, monster);
}