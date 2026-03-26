// BattleManager.cpp

#include "BattleManager.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

void BattleManager::StartBattle(Player& player, Monster& monster)
{
	isRunningAway = false;

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

void BattleManager::DisplayStatus(const Player& player, const Monster& monster)
{
	std::cout << "===============================\n";
	std::cout << "[플레이어]\n";
	std::cout << std::left << std::setw(10) << "멘탈" << ": " << std::right << std::setw(3) << "???" << "/" << std::setw(3) << "???" << '\n';
	std::cout << std::left << std::setw(10) << "집중력" << ": " << std::right << std::setw(3) << "???" << "/" << std::setw(3) << "???" << '\n';

	std::cout << "[빌런]\n";
	std::cout << std::left << std::setw(10) << "압박감" << ": " << std::right << std::setw(3) << "???" << "/" << std::setw(3) << "???" << '\n';
	std::cout << std::left << std::setw(10) << "위험도" << ": " << std::right << std::setw(3) << "???" << "/" << std::setw(3) << "???" << '\n';

	std::cout << "===============================\n";
}

void BattleManager::DisplayMenu()
{
	std::cout << "============[행동 선택]============\n";
	std::cout << " 1. 자료제출\n";
	std::cout << " 2. 스킬\n";
	std::cout << " 3. 아이템\n";
	std::cout << " 4. 눈치보고 런..\n";
	std::cout << "==================================\n";
	std::cout << " > 어떤 방식을 선택하시겠습니까? : ";
}

void BattleManager::PlayerTurn(Player& player, Monster& monster)
{
	int choice;
	std::cin >> choice;

	switch (choice)
	{
		case 1:
			std::cout << "여기 정리 자료 있습니다.!\n";
			std::cout << "빌런 이름" << "????" << "의 데미지를 주었습니다.\n";
			break;

		case 2:
			if (skillManager)
				skillManager->UseSkill(player, monster);
			break;

		case 3:
			std::cout << "미구현 선택입니다.\n";
			//if (item)
			//	item->UseItem(player, monster);
			break;

		case 4:
			std::cout << "도망을 시전합니다.....\n";

			int chance = rand() % 100;

			if (chance < 60)
			{
				std::cout << "(지금이다!!!!!)\n";
				isRunningAway = true;
			}
			else
			{
				std::cout << "빌런 이름 : 어디가나 당장 이리와!\n";
			}
			break;

		default:
			std::cout << "선택 방식이 잘못되었습니다.. 다시 입력해주세요.\n";
			break;
	}
}