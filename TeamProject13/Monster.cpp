#include "Monster.h"

void Monster::TakeDamage(int damage) {
	if (damage >= pressure) {
		pressure = 0;
		defeated = true;
		return;
	}
	pressure -= damage;
}
void Monster::MonsterAction(Player& player) { 
	int playerDef = player.GetDef();
	int damage = atk - playerDef;
	player.SubMental(damage);
}
Monster DepartmentManager("ºÎÀå´Ô", 50, 20, 30, 50, 500);
Monster Designer("±âÈ¹ÀÚ", 20, 50, 20, 50, 500);
Monster Boss("ÆÀÀå´Ô", 100, 50, 50, 100, 1000);