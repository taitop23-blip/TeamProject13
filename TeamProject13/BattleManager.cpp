// BattleManager.cpp

#include "BattleManager.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <windows.h>

static void WaitForEnter()
{
	std::cout << "\n계속하려면 Enter를 누르세요...";
	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	std::cin.get();
}

void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void PrintBar(int current, int max, int fillColor, int emptyColor, int barWidth = 20)
{
	if (max <= 0) return;

	float ratio = (float)current / max;
	int filled = (int)(ratio * barWidth);

	std::cout << "[";

	for (int i = 0; i < barWidth; ++i)
	{
		if (i < filled)
		{
			SetColor(fillColor);
			std::cout << "█";
		}
		else
		{
			SetColor(emptyColor);
			std::cout << "█";
		}
	}

	SetColor(7);
	std::cout << "]";
}

// [수정/추가사항] LNK2019 (unresolved external symbol) 링킹 에러 해결을 위해 생성자 구현부 추가
BattleManager::BattleManager()
	: skillManager(nullptr), isRunningAway(false)
{
	skills.push_back(SkillManager("야근싫어", SkillType::ATTACK, 20, 10, 2));
	skills.push_back(SkillManager("복붙", SkillType::ATTACK, 15, 8, 1));
	skills.push_back(SkillManager("방어스킬", SkillType::DEFENSE, 10, 5, 2));
	skills.push_back(SkillManager("회복스킬", SkillType::HEAL, 25, 12, 3));
}

BattleResult BattleManager::StartBattle(Player& player, Monster& monster)
{
	isRunningAway = false;

	while (!IsBattleOver(player, monster))
	{
		system("cls");

		DisplayStatus(player, monster);
		DisplayMenu();

		PlayerTurn(player, monster);
		if (IsBattleOver(player, monster)) break;

		WaitForEnter();

		system("cls");
		MonsterTurn(player, monster);

		WaitForEnter();

		if (player.GetMental() <= 0)
		{
			player.SubLife();

			if (player.GetLife() <= 0)
			{
				if (player.TryAutoRevive())
				{
					player.ResetTempStats();
					return BattleResult::Revived;
				}
				ProcessDefeat(player, monster);
				return BattleResult::Defeat;
			}
			ProcessCollapse(player, monster);
			player.ResetTempStats();
			return BattleResult::Collapse;
		}
		
	}
	player.ResetTempStats();

	if (player.GetMental() <= 0) {
		ProcessDefeat(player, monster);
		return BattleResult::Defeat;
	}
	else {
		if (!isRunningAway) {
			ProcessVictory(player, monster);
			return BattleResult::Victory;
		}
		else {
			ProcessRunAway(player, monster);
			return BattleResult::RunAway;
		}
	}
}

void BattleManager::DisplayStatus(const Player& player, const Monster& monster)
{
	std::cout << "\n=================[ 빌 런 ]=================\n\n";

	std::cout << monster.GetName() << "이 등장했습니다.\n";
	std::cout << std::left << std::setw(10) << "압박감"
		<< " : " << std::right << std::setw(3) << monster.GetPressure() << " / "
		<< std::setw(3) << monster.GetMaxPressure() << "  ";

	PrintBar(monster.GetPressure(), monster.GetMaxPressure(), 10, 12);

	std::cout << '\n';

	std::cout << "\n===========================================\n";


	std::cout << "\n================[ 플레이어 ]================\n\n";

	std::cout << player.GetName() << '\n';  // 플레이어 이름 추가
	// [수정/추가사항] 한글 인코딩 에러(C2001: newline in constant) 방지를 위해 문자열 형태 및 여백 수정 ("/" -> " / ")

	std::cout << std::left << std::setw(10) << "멘탈"
		<< " : " << std::right << std::setw(3) << player.GetMental() << " / "
		<< std::setw(3) << player.GetMaxMental() << "  ";

	PrintBar(player.GetMental(), player.GetMaxMental(), 10, 12);
	std::cout << '\n';

	std::cout << std::left << std::setw(11) << "집중력"
		<< " : " << std::right << std::setw(3) << player.GetFocus() << " / "
		<< std::setw(3) << player.GetMaxFocus() << "  ";

	PrintBar(player.GetFocus(), player.GetMaxFocus(), 9, 14);
	std::cout << '\n';

	int life = player.GetLife();

	std::cout << std::left << std::setw(10) << "뽀삐사진" << " : ";
	for (int i = 0; i < life; i++)
	{
		std::cout << "♥ ";
	}
	std::cout << '\n';

	std::cout << "\n===========================================\n";
}

void BattleManager::DisplayMenu()
{
	std::cout << "\n============[행동 선택]============\n";
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
		int damage = player.GetAtk() - monster.GetDef();

		if (damage < 0)
			damage = 0;

		monster.TakeDamage(damage);

		std::cout << "여기 정리 자료 있습니다!\n";
		std::cout << monster.GetName() << "에게 압박감이 " << damage << "만큼 감소했습니다.\n";

		std::cout << monster.GetName() << "의 현재 압박감 : " << monster.GetPressure() << " / " << monster.GetMaxPressure() << '\n';
		return;
	}

	case 2:
		system("cls");
		DisplayStatus(player, monster);
		DisplaySkillMenu(player);

		if (UseSkill(player, monster))
		{
			return;
		}
		else
		{
			system("cls");
			DisplayStatus(player, monster);
			DisplayMenu();
			break;
		}

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
			WaitForEnter();
		}
		else
		{
			std::cout << monster.GetName() << " : 어디가나 당장 이리와!\n";
		}
		return;
	}
	default:
		std::cout << "선택 방식이 잘못되었습니다.. 다시 입력해주세요.\n";
		DisplayMenu();
		break;
	}
}

void BattleManager::DisplaySkillMenu(const Player& player) const
{
	std::cout << "\n================[ 스 킬 창 ]================\n\n";
	std::cout << "1. 야근 싫어\n";
	std::cout << "2. 복붙\n";
	std::cout << "3. 방어스킬\n";
	std::cout << "4. 회복스킬\n";
	std::cout << "0. 뒤로가기\n";
	std::cout << "\n============================================\n";
	std::cout << "사용할 스킬을 선택하세요 : ";
}

bool BattleManager::UseSkill(Player& player, Monster& monster)
{
	int choice;
	
	while (true)
	{
		std::cin >> choice;

		switch (choice)
		{
			case 1:
				skills[0].Use(player, monster);
				if (monster.IsDefeated() || monster.GetPressure() <= 0)
					WaitForEnter();
				return true;

			case 2:
				skills[1].Use(player, monster);
				if (monster.IsDefeated() || monster.GetPressure() <= 0)
					WaitForEnter();
				return true;

			case 3:
				skills[2].Use(player, monster);
				return true;

			case 4:
				skills[3].Use(player, monster);
				return true;

			case 0:
				std::cout << "스킬 사용이 취소되었습니다.\n";
				return false;

			default:
				std::cout << "잘못된 입력입니다. 스킬을 다시 선택해주세요. : ";
				break;
		}
	}
}

bool BattleManager::UseItem(Player& player)
{
	if (!player.HasItems())
	{
		std::cout << "사용할 아이템이 없습니다.\n";
		return false;
	}

	player.PrintInventory();

	int choice;
	std::cout << "\n사용할 아이템 번호 선택 (0 : 취소) : ";
	std::cin >> choice;

	if (choice == 0)
	{
		std::cout << "아이템 사용이 취소되었습니다.\n";
		return false;
	}

	const Item* item = player.GetItem(choice - 1);

	if (item == nullptr)
	{
		std::cout << "잘못된 선택입니다.\n";
		return false;
	}

	std::cout << item->GetName() << " 사용!\n";

	// 아이템 효과 적용
	player.AddMental(item->GetMentalRecovery());
	player.AddFocus(item->GetFocusRecovery());
	player.AddProgress(item->GetProgressBonus());

	if (item->GetLifeBonus() > 0)
	{
		player.AddLife();
	}

	player.RemoveItem(choice - 1);
	return true;
}

void BattleManager::MonsterTurn(Player& player, Monster& monster)
{
	std::cout << "\n[ 몬스터 턴 ]\n";
	std::cout << monster.GetName() << "이(가) 잔소리를 시작합니다.\n";

	int damage = monster.MonsterAction(player);

	std::cout << player.GetName() << "이(가) " << damage << "만큼 멘탈이 피해를 받았습니다!!\n";
	std::cout << "현재 멘탈 : " << player.GetMental() << " / " << player.GetMaxMental() << "  ";

	PrintBar(player.GetMental(), player.GetMaxMental(), 10, 12);
	std::cout << '\n';

	// [수정/추가사항] 몬스터 턴 종료 시 플레이어 스킬의 쿨타임(CoolTime)을 감소시키는 로직 추가
	for (SkillManager& skill : skills) {
		skill.TickCoolTime();
	}
}

bool BattleManager::IsBattleOver(const Player& player, const Monster& monster)
{
	if (monster.GetPressure() <= 0)
		return true;

	if (player.GetMental() <= 0)
		return true;

	if (isRunningAway)
		return true;

	return false;
}

void BattleManager::ProcessCollapse(Player& player, Monster& monster)
{
	std::cout << "멘탈이 " << player.GetMental() << "이 되었습니다.\n";
	std::cout << monster.GetName() << "에게 잔소리를 심하게 들었습니다.\n";
	std::cout << monster.GetName() << "이(가) 자기 자리로 돌아갑니다.\n";
	std::cout << player.GetName() << "이(가) 사직서를 꺼내드는 순간...\n";
	std::cout << "그 때--\n 멍! 멍!멍!\n";
	std::cout << "....뽀삐가 떠올랐습니다.";
	std::cout << "그래... 사료 사야지...\n";
	std::cout << "당신은 눈물을 닦고 다시 일을 시작합니다.\n";

	std::cout << "뽀삐사진을 1개 잃었습니다.\n";

	player.AddProgress(-10);
	std::cout << "진행도가 10 감소했습니다.\n";

	player.RecoverAfterCollapse();

	WaitForEnter();
}

void BattleManager::ProcessDefeat(Player& player, Monster& monster)
{
	std::cout << player.GetName() << "의 멘탈이 완전히 무저졌습니다.\n";
	std::cout << monster.GetName() << "의 압박을 버티지 못했습니다.\n";
	std::cout << "더 이상 일을 이어갈 수 없습니다....\n";
}

void BattleManager::ProcessVictory(Player& player, Monster& monster)
{
	// [수정/추가사항] 주석 처리되어 있던 경험치 및 보상 로직 활성화
	int expReward = monster.GetExp();
	int goldReward = monster.GetGold();

	player.AddExp(expReward);
	player.AddGold(goldReward);

	system("cls");

	std::cout << "============================\n";
	std::cout << "[ 전투 승리! ]\n";
	std::cout << "============================\n";

	std::cout << "휴.. " << monster.GetName() << "에게서 무사히 버텨냈습니다.\n";

	std::cout << "[ 보상 획득 ]\n";

	std::cout << "+ 경험치 + : " << expReward << "획득!\n";
	std::cout << "+ 야근수당 + : " << goldReward <<"원 획득!\n";
	
	// 아이템 랜덤 드랍
	int dropRoll = rand() % 100 + 1;

	if (dropRoll <= 40)
	{
		int itemRoll = rand() % 5;

		Item rewardItem;

		switch (itemRoll)
		{
			case 0:
				rewardItem = Item(ItemType::POPPY_PHOTO);
				break;
			case 1:
				rewardItem = Item(ItemType::COFFEE);
				break;
			case 2:
				rewardItem = Item(ItemType::HOTSIX);
				break;
			case 3:
				rewardItem = Item(ItemType::KEYBOARD);
				break;
			case 4:
				rewardItem = Item(ItemType::MOUSE);
				break;
		}
		player.AddItem(rewardItem);
	}
	else
	{
		std::cout << "아이템은 드랍되지 않았습니다.\n";
	}

	std::cout << "============================\n";

	WaitForEnter();

	system("cls");
}

void BattleManager::ProcessRunAway(Player& player, Monster& monster)
{
	std::cout << "============================\n";
	std::cout << "[ 도망 성공! ]\n";
	std::cout << "============================\n";

	std::cout << "간신히 " << monster.GetName() << "의 시야에서 벗어났습니다.\n";
	std::cout << player.GetName() << "이(가) 숨을 고르며 다시 업무 자리로 돌아갑니다.\n";

	std::cout << "============================\n";

	WaitForEnter();
}