// Player.h

#pragma once
#include <string>
#include <iostream>

class Player {
private:

	int Level = 1;
	int exp = 0;
	int maxExp = 100;
	std::string name;
	int mental, maxMental;   // HP
	int focus, maxFocus;     // MP
	int atk;                 // 공격력
	int def;                 // 방어력
	int progress = 0;        // 진행도 (0~100%)
	int life = 3;            // 목숨
	int gold = 0;            // 골드

public:

	// get 함수
	int GetLevel() const { return Level; }
	int GetExp() const { return exp; }
	int GetMental() const { return mental; }
	int GetMaxMental() const { return maxMental; }
	int GetFocus() const { return focus; }
	int GetMaxFocus() const { return maxFocus; }
	int GetProgress() const { return progress; }
	int GetLife() const { return life; }
	int GetAtk() const { return atk; }
	int GetDef() const { return def; }
	int GetGold() const { return gold; }

	//set 함수
	//void SetExp(int exp) { this->exp = exp; }
	//void SetMaxExp(int maxExp) { this->maxExp = maxExp; }
	//void Setmental(int mental) { this->mental = mental; }
	//void SetMaxMental(int maxMental) { this->maxMental = maxMental; }
	//void SetFocus(int focus) { this->focus = focus; }
	//void SetMaxFocus(int maxFocus) { this->maxFocus = maxFocus; }
	//void SetLife(int life) { this->life = life; }
	//void SetAtk(int atk) { this->atk = atk; }
	//void SetDef(int def) { this->def = def; }
	//void SetGold(int gold) { this->gold = gold; }
	


	//add 함수
	void AddExp(int val);
	void AddMental(int val);
	void AddFocus(int val);
	void AddProgress(int val);
	void AddAtk(int val) { atk += val; }
	void AddDef(int val) { def += val; }
	void Addgold(int val) {gold += val;}
	void AddLevel() { Level += 1; }

	
	//sub 함수
	void SubMental(int val);
	void SubFocus(int val);
	void SubLife();
	void SubGold(int val);
	void SubProgress(int val);

	//전투 관련
	int getHP() const { return mental; } // Battlemanager 작업용
	void takeDamage(int damage) { SubMental(damage); }
	bool IsDead() const {return life <= 0; }

	//부활 관련
	void RestoreFullMental() {mental = maxMental;}

	// 생성자
	Player(const std::string& name,int mental, int focus, int atk, int def);

	//스탯 보여주기
	void ShowCurrentStatus();
};
