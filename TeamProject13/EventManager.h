#pragma once
#include <string>
#include "Player.h"

class EventManager //이벤트 매니저 클래스
{
public:
	void ShowBonusMenu(Player& p);

private:
	void ApplyBonus(Player& p, int choice);
};

