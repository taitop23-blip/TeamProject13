// WorldManager.cpp

#include "WorldManager.h"
#include "Monster.h"
#include "BattleManager.h"
#include "Player.h"
#include "Utils.h"
#include <iostream>


void WorldManager::ShowActionMenu(const Player& p) const
{
	std::cout << "\n========[ 업무 중 ]========" << std::endl;
	std::cout << " 진행도: " << p.GetProgress() << "%\n";
	std::cout << " 위험도: " << dangerLevel
		      << " 목숨 " << p.GetLife() << "개\n";
	std::cout << " 멘탈 " << p.GetMental() << "/" << p.GetMaxMental()
		      << " 집중력 " << p.GetFocus() << "/" << p.GetMaxFocus() << "\n";

	Utils::PrintLine('-', 30);
	std::cout << " 1. 업무 집중    (진행도+, 멘탈-, 집중력(Mp)-, 위험도+)\n";
	std::cout << " 2. 커피 충전    (집중력(Mp)+, 멘탈 소폭-)\n";
	std::cout << " 3. 유튜브 시청  (진행도-, 멘탈+, 위험도++\n";
	std::cout << " 4. 몰래 스트레칭(멘탈+, 집중력(Mp) 소폭+\n";
	std::cout << " 5. 상태 확인 \n";
	std::cout << " 6. 상점 가기\n";
	Utils::PrintLine('-', 30);
}


void WorldManager::FocusWork(Player& p){
	
	int progressGain = Utils::GetRandom(5, 10);
	p.AddProgress(progressGain);
	p.SubMental(5);
	p.SubFocus(10);
	dangerLevel += 15;

	std::cout << "\n [업무 집중] 열심히 일했습니다.\n";
	std::cout << " 진행도 +" << progressGain << " | 멘탈 -5 | 집중력 -10 | 위험도 +15 |\n";
}

void WorldManager::DrinkCoffee(Player& p)
{
	p.AddFocus(20);
	p.SubMental(3);

	std::cout << "\n [커피 충전] 아이스 아메리카노 쭈왑!\n";
	std::cout << " 집중력 +20 | 멘탈 -3\n";
}

void WorldManager::WatchYoutube(Player& p)
{
	p.AddProgress(-5);
	p.AddMental(10);
	p.SubFocus(15);
	dangerLevel += 20;

	std::cout << "\n  [유튜브 시청] 잠깐만 보려다가...\n";
	std::cout << "  진행도 -5 | 멘탈 +10 | 집중력 -15 | 위험도 +20\n";
}

void WorldManager::Stretching(Player& p)
{
	p.AddMental(8);
	p.AddFocus(5);

	std::cout << "\n  [몰래 스트레칭] 슬쩍 기지개를 켭니다.\n";
	std::cout << "  멘탈 +8 | 집중력 +5\n";
}


bool WorldManager::CheckEncounter() {

	int randomValue = Utils::GetRandom(1, 100);
	bool encounter = (randomValue <= dangerLevel);

	if (encounter) {
		if (dangerLevel >= 70)
			std::cout << "\n 위험도 폭발! 빌런이 당신을 찾아냈습니다!\n";
		else if (dangerLevel >= 40)
			std::cout << "\n 빌런이 당신의 딴짓을 포착했습니다!\n";
		else
			std::cout << "\n 낮은 확률을 뚫고 빌런과 마주쳤습니다!\n";
	}
	else {
		if (dangerLevel >= 50)
			std::cout << "\n 빌런이 당신을 지나쳐갑니다.\n";
	}
	return encounter;
}


bool WorldManager::RunWorkLoop(Player& p)
{
	while (true)
	{
		// 진행도 100% → 보스전 신호
		if (IsReadyForFinalBoss(p.GetProgress())) return true;

		// 멘탈 체크 
		if (p.GetMental() <= 0)
		{
			if (p.GetLife() > 0)
			{
				p.RestoreFullMental();

				std::cout << "\n [시스템] 멘탈을 부여잡고 다시 자리에 앉습니다. (남은 뽀삐사진: " << p.GetLife() << "개)\n";
			}
			else
			{
				return false; // 목숨이 0이면 루프 탈출
			}
		}

		ShowActionMenu(p);

		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1: FocusWork(p); break;
		case 2: DrinkCoffee(p); break;
		case 3: WatchYoutube(p); break;
		case 4: Stretching(p); break;
		//case 5: continue; // 상태 확인 (추후 구현)
		//case 6: continue; // 상점 가기 (추후 구현)
		default: std::cout << " 올바른 번호를 입력하세요.\n"; continue;
		}

		// 빌런 조우 판정
		if (CheckEncounter())
		{
			const char* villains[] = {
				"부장님", "기획자", "팀장님"
			};
			std::string name = villains[Utils::GetRandom(0, 2)];

			int pressure = std::max(30, 20 + dangerLevel);
			int atk = std::max(10, 5 + (dangerLevel / 5));
			int def = std::max(5, dangerLevel / 10);

			Monster m(name, pressure, atk, def);

			BattleManager bm;
			bm.StartBattle(p, m);
		}
	}

	return false;
}