#include "Player.h"

// add함수
void Player::AddMental(int val)
{
	mental += val;
	if (mental > maxMental)
	{
		mental = maxMental;
	}
}

void Player::AddFocus(int val)
{
	focus += val;
	if (focus > maxFocus)
	{
		focus = maxFocus;
	}
}

void Player::AddProgress(int val)
{
	progress += val;
	if (progress > 100)
	{
		progress = 100;
	}
}

//sub 함수
void Player::SubMental(int val)
{
	mental -= val;
	if (mental < 0)
	{
		mental = 0;
	}
}


void Player::SubFocus(int val)
{
	focus -= val;
	if (focus < 0)
	{
		focus = 0;
	}
}

// 생성자
Player::Player(int mental, int focus, int atk, int def)
{
	this->mental = mental;
	this->maxMental = mental;

	this->focus = focus;
	this->maxFocus = focus;

	this->atk = atk;
	this->def = def;
}

void Player::ShowCurrentStatus()
{
	std::cout << "===================================================\n";
	std::cout << name << "의 능력치\n" << "멘탈(HP): " << GetMental() << " 집중력(MP): " << GetFocus() << " 업무 효율 : " << GetAtk() << " 스트레스 저항 : " << GetDef() << " 소지 골드 : " << GetGold();
	std::cout << std::endl << "===================================================\n";
}




