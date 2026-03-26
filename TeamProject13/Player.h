// Player.h

#pragma once
#include <string>

class Player {
private:
	std::string name;
	int mental, maxMantal;   // HP
	int focus, maxFocus;     // MP
	int atk;                 // 공격력
	int def;                 // 방어력
	int progress = 0;        // 진행도 (0~100%)
	int life = 3;            // 목숨
};
