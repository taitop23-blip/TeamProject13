#include "SkillManager.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>

using namespace std;

SkillManager(string n, SkillType; t, int p, int cost, int ct;)
	: name(n), type(t), power(p), focuscost(cost), cooltime(ct), currentCoolTime(0)
{ 
}

bool SkillManager::CanUse(int currentFocus)
{
	return currentFocus >= focuscost && currentCoolTime == 0;
}

void SkillManager::Use(Player& user, Player& target)
{
	if (!CanUse(user.Focus))
	{
		cout << "스킬을 사용할 수 없습니다!" << endl;
		return;
	}

	user.Focus -= focuscost;
	currentCoolTime = cooltime;

	//공격 스킬
	if (type == SkillType::ATTACK)
	{
		if (name == "야근싫어")
		{
			cout << "야근 싫어!" << endl;
			int dmg = (user.Atk + 20) - target.Def;
			if (dmg < 0) dmg = 0;

			target.Pressure -= dmg;
			if (target.Pressure < 0) target.Pressure = 0;

			cout << dmg << " 데미지!" << endl;
		}

		else if (name == "복붙")
		{
			cout << "Ctrl+c Ctrl+v" << endl;
			int dmg = user.Atk - target.Def;
			if (dmg < 0) dmg = 0;

			target.pressure -= dmg;
			if (target.Pressure < 0) target.Pressure = 0;

			cout << dmg << " 데미지!" << endl;
		}
	}

	//방어 스킬
	else if (type == SkillType::DEFENSE)
	{
		cout << "이건 제가 안 했는데요?" << endl;
		user.Def += 10;
		cout << "방어력 +10" << endl;
	}

	//회복 스킬
	else if (type == SkillType::HEAL)
	{
		cout << "칼퇴 상상" << endl;
		user.Focus += 30;
		cout << "집중력 +30 회복!" << endl;
	}
}

void SkillManager::TickCoolTime()
{
	if (currentCoolTime > 0)
		currentCoolTime--;
}

