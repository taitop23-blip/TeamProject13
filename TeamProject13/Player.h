// Player.h

#pragma once
#include <string>

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

	//add 함수
	void AddMental(int val);
	void AddFocus(int val);
	void AddProgress(int val);
	
	//sub 함수
	void SubMental(int val);
	void SubFocus(int val);
	void SubLife() { life -= 1; }

	//전투 관련 로직
	int getHP() const { return mental; } // Battlemanager 작업용
	void takeDamage(int damage) { SubMental(damage); }
	bool IsDead() const {return life<= 0; }

	// 생성자
	Player(int mental, int focus, int atk, int def);
};
