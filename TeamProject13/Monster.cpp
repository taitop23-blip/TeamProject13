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
    // [수정/추가사항 1] 데미지 하한선 설정
    // 플레이어의 방어력이 공격력보다 높을 때 데미지가 음수로 계산되어, 
    // 오히려 플레이어의 멘탈이 회복되는 버그를 방지하기 위해 최소 데미지를 0으로 고정
    if (damage < 0) {
        damage = 0;
    }
    player.SubMental(damage);
}

Monster DepartmentManager("부장님", 50, 20, 30, 50, 500);
Monster Designer("기획자", 20, 50, 20, 50, 500);
Monster Boss("팀장님", 100, 50, 50, 100, 1000);
