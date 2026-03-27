#include "Player.h"

// add함수

void Player::AddExp(int val)
{
	exp += val;
	if (exp > maxExp)
	{
		exp = maxExp;
	}
}
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
void Player::SubLife()
{
	life -= 1;
	if (life < 0)
	{
		life = 0;
	}
}
void Player::SubGold(int val)
{
	gold += val;
	if (gold < 0)
	{
		gold = 0;
	}
}
void Player::SubProgress(int val)
{
	progress -= val;
	if (progress < 0)
	{
		progress = 0;
	}
}

// 생성자
Player::Player(const std::string& name, int mental, int focus, int atk, int def)
	: Level(1), exp(0), name(name), mental(mental),
	focus(focus), atk(atk), def(def)
{
	this->mental = mental;
	this->maxMental = mental;

	this->focus = focus;
	this->maxFocus = focus;
}

void Player::ShowCurrentStatus()
{
	std::cout << "===================================================\n";
	std::cout << name << "의 능력치\n" << "멘탈(HP): " << GetMental() << std::endl << "집중력(MP): " << GetFocus()<<std::endl << "업무 효율 : " << GetAtk()<<std::endl << "스트레스 저항 : " << GetDef()<<std::endl << "소지 골드 : " << GetGold()<<std::endl;
	std::cout << std::endl << "===================================================\n";
}




