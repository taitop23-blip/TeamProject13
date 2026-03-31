#include "Monster.h"

void Monster::TakeDamage(int damage) {
    if (damage >= pressure) {
        pressure = 0;
        defeated = true;
        return;
    }
    pressure -= damage;
}

int Monster::MonsterAction(Player& player) {
    int playerDef = player.GetDef();
    int damage = atk - playerDef;

    if (damage < 0) {
        damage = 0;
    }

    player.SubMental(damage);
    return damage;
}