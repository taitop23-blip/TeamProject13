// BattleManager.cpp

#include "BattleManager.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

bool BattleManager::StartBattle(Player& player, Monster& monster)
{
	isRunningAway = false;

	while (!IsBattleOver(player, monster))
	{
		DisplayStatus(player, monster);
		DisplayMenu();

		PlayerTurn(player, monster);
		if (IsBattleOver(player, monster)) break;

		MonsterTurn(player, monster);
	}
	if (player.GetMental() <= 0) {
		ProcessDefeat(player, monster);
		return false;
	}
	else {
		if (!isRunningAway) {
			ProcessVictory(player, monster);
		}
		else {
			ProcessRunAway(player, monster);
		}
		return true;
	}
}

void BattleManager::DisplayStatus(const Player& player, const Monster& monster)
{
	std::cout << "===============================\n";
	std::cout << "[플레이어]\n";
	std::cout << std::left << std::setw(10) << "멘탈" 
		<< " : " << std::right << std::setw(3) << player.GetMental() << "/"
		<< std::setw(3) << player.GetMaxMental() << '\n';

	std::cout << std::left << std::setw(10) << "집중력"
		<< " : " << std::right << std::setw(3) << player.GetFocus() << "/"
		<< std::setw(3) << player.GetMaxFocus() << '\n';

	int life = player.GetLife();

	std::cout << std::left << std::setw(10) << "뽀삐사진" << " : ";
		for (int i = 0; i < life; i++)
		{
			std::cout << "*";
		}
	std::cout << '\n';

	std::cout << "[빌런]\n";
	std::cout << std::left << std::setw(10) << "압박감"
		<< " : " << std::right << std::setw(3) << monster.getPressure() << "/"
		<< std::setw(3) << monster.getMaxPressure() << '\n';

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
		{
			int damage = player.GetAtk() - monster.getDef();

			if (damage < 0)
				damage = 0;

			monster.takeDamage(damage);

			std::cout << "여기 정리 자료 있습니다!\n";
			std::cout << monster.getName() << "에게 압박감이 " << damage << "만큼 감소했습니다.\n";

			std::cout << monster.getName() << "의 현재 압박감 : " << monster.getPressure() << " / " << monster.getMaxPressure() << '\n';
			return;
		}
			

		case 2:
			if (skillManager)
				skillManager->Use(player, monster);
			break;

		case 3:
			if (UseItem(player))
			{
				return;
			}
			DisplayMenu();
			break;

		case 4:
		{
			std::cout << "도망을 시전합니다.....\n";

			int chance = rand() % 100;

			if (chance < 60)
			{
				std::cout << "(지금이다!!!!!)\n";
				isRunningAway = true;
			}
			else
			{
				std::cout << monster.getName() << " : 어디가나 당장 이리와!\n";
			}
			return;
		}
		default:
			std::cout << "선택 방식이 잘못되었습니다.. 다시 입력해주세요.\n";
			DisplayMenu();
			break;
	}
}

bool BattleManager::UseItem(Player& player)
{
	int choice;

	std::cout << "\n===============[ 아이템 창 ]===============\n";
	std::cout << "1. 커피\n";
	std::cout << "2. 핫식스\n";
	std::cout << "3. 몬스터에이드\n";
	std::cout << "4. 게이밍 레이저 키보드\n";
	std::cout << "5. DeathAdder V3 Pro 마우스\n";
	std::cout << "0. 선택 취소\n";
	std::cout << "=============================================\n";
	std::cout << "사용할 아이템을 선택하세요 : \n";
	std::cin >> choice;

	switch (choice)
	{
		case 1:
			std::cout << "커피를 마셨습니다.\n";
			player.AddMental(10);
			return true;

		case 2:
			std::cout << "핫식스를 마셨습니다.\n";
			player.AddMental(20);
			return true;

		case 3:
			std::cout << "몬스터에이드를 마셨습니다.\n";
			player.AddFocus(10);
			return true;

		case 4:
			std::cout << "게이밍 레이저 키보드를 사용했습니다.\n";
			player.AddProgress(15);
			return true;

		case 5:
			std::cout << "DeathAdder V3 Pro 마우스를 사용했습니다.\n";
			player.AddProgress(25);
			return true;

		case 0:
			std::cout << "선택을 취소하셨습니다.\n";
			return false;

		default:
			std::cout << "잘못된 아이템 선택입니다. 다시 선택해주세요.\n";
			break;
	}
}

void BattleManager::MonsterTurn(Player& player, Monster& monster)
{
	std::cout << "\n[ 몬스터 턴 ]\n";
	std::cout << monster.getName() << "이(가) 잔소리를 시작합니다.\n";

	int damage = monster.getAtk() - player.GetDef();

	if (damage < 0)
		damage = 0;

	player.takeDamage(damage);

	std::cout << damage << "의 만큼 멘탈이 피해를 받았습니다!!\n";
	std::cout << "현재 멘탈 : " << player.GetMental() << " / " << player.GetMaxMental() << "\n";
}

bool BattleManager::IsBattleOver(const Player& player, const Monster& monster)
{
	if (monster.getPressure() <= 0)
		return true;

	if (player.GetMental() <= 0)
		return true;

	if (isRunningAway)
		return true;

	return false;
}

void BattleManager::ProcessDefeat(Player& player, Monster& monster)
{
	std::cout << "멘탈이 " << player.GetMental() << "이 되었습니다.\n";
	std::cout << monster.getName() << "에게 잔소리를 심하게 들었습니다.\n";
	std::cout << monster.getName() << "이(가) 자기 자리로 돌아갑니다.\n";
	std::cout << "사직서를 꺼내드는 순간...\n";
	std::cout << "그 때--\n 멍! 멍!멍!\n";
	std::cout << "....뽀삐가 떠올랐습니다.";
	std::cout << "그래... 사료 사야지...\n";
	std::cout << "당신은 눈물을 닦고 다시 일을 시작합니다.\n";

	player.SubLife();

	std::cout << "뽀삐사진을 1개 잃었습니다.\n";
	
	player.AddProgress(-10);
	std::cout << "진행도가 10 감소했습니다.\n";
}

void BattleManager::ProcessVictory(Player& player, Monster& monster)
{
	//int expReward = 30;
	//int goldReward = 500;

	std::cout << "============================\n";
	std::cout << "[ 전투 승리! ]\n";
	std::cout << "============================\n";

	std::cout << "휴.. " << monster.getName() << "에게서 무사히 버텨냈습니다.\n";

	std::cout << "[ 보상 획득 ]\n";

	std::cout << "+ 경험치 + : 30\n";
	std::cout << "+ 야근수당 + : 500원\n";
	//std::cout << "+ 아이템 + : " << "???" << "\n";					//구현 중

	std::cout << "============================\n";

	//player.AddExp(expReward);
	//player.AddGold(goldReward);
}

void BattleManager::ProcessRunAway(Player& player, Monster& monster)
{
	std::cout << "============================\n";
	std::cout << "[ 도망 성공! ]\n";
	std::cout << "============================\n";

	std::cout << "간신히 " << monster.getName() << "의 시야에서 벗어났습니다.\n";
	std::cout << "숨을 고르며 다시 업무 자리로 돌아갑니다.\n";

	std::cout << "============================\n";
}
