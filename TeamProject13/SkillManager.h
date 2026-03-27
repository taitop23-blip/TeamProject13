// SkillManager.h

#pragma once
#include "Player.h"
#include <iostream>
#include <string>

enum class SkillType  //스킬타입 선언
{
	ATTACK, DEFENSE, HEAL
};

class SkillManager //Skill 클래스
{
public:
	std::string name;
	SkillType type;

	int power;
	int focuscost;
	int cooltime;
	int currentCoolTime;

	SkillManager(std::string n, SkillType t, int p, int cost, int ct); //스킬 생성자

	bool CanUse(int currentfocus); //스킬 사용가능여부 확인
	void Use(Player& user, Player& target); //스킬 실행 함수
	void TickCoolTime(); //턴 끝날 때 호출하여 스킬 쿨타임 감소 체크
};

