#include "SkillManager.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>

// [수정/추가사항 1] 기존 .cpp 파일 내부에 중복으로 작성되어 컴파일 에러(C2011)를 유발하던 
// enum SkillType { ... } 정의를 삭제하고, 헤더 파일의 선언을 정상적으로 연동했습니다.

// [수정/추가사항 2] 향후 프로젝트 규모가 커질 때 발생할 수 있는 이름 충돌을 방지하기 위해, 
// 'using namespace std;'를 제거하고 객체마다 'std::'를 명시적으로 붙여 코드를 더 견고하게 만들었습니다.

SkillManager::SkillManager(std::string n, SkillType t, int p, int cost, int ct)
    : name(n), type(t), power(p), focuscost(cost), cooltime(ct), currentCoolTime(0)
{
}

bool SkillManager::CanUse(int currentFocus)
{
    return currentFocus >= focuscost && currentCoolTime == 0;
}

void SkillManager::Use(Player& user, Monster& target)
{
    if (!CanUse(user.GetFocus()))
    {
        std::cout << "스킬을 사용할 수 없습니다! (집중력 부족 또는 쿨타임 중)\n";
        return;
    }

    user.SubFocus(focuscost);
    currentCoolTime = cooltime;

    // [수정/추가사항 3] 열거형 값에 접근할 때 범위를 명확히 지정하여 (예: ATTACK -> SkillType::ATTACK) 
    // 컴파일러가 식별자를 찾지 못하던 에러(C2065)를 완전히 해결했습니다.

    // 공격 스킬 처리
    if (type == SkillType::ATTACK)
    {
        if (name == "야근싫어")
        {
            std::cout << "야근 싫어!\n";
            int dmg = (user.GetAtk() + 20) - target.GetDef();
            if (dmg < 0) dmg = 0;

            target.TakeDamage(dmg);
            std::cout << dmg << " 데미지!\n";
        }
        else if (name == "복붙")
        {
            std::cout << "Ctrl+c Ctrl+v\n";
            int dmg = user.GetAtk() - target.GetDef();
            if (dmg < 0) dmg = 0;

            target.TakeDamage(dmg);
            std::cout << dmg << " 데미지!\n";
        }
    }

    // (이하 DEFENSE, HEAL 등 다른 스킬 로직도 동일하게 std:: 명시 및 구조 개선)
 
    // 방어 스킬 처리
    else if (type == SkillType::DEFENSE)
    {
        std::cout << name << " 스킬을 사용했습니다! 방어력이 증가합니다.\n";
        user.AddDef(power);
    }
    // 회복 스킬 처리
    else if (type == SkillType::HEAL)
    {
        std::cout << name << " 스킬을 사용했습니다! 멘탈을 회복합니다.\n";
        user.AddMental(power);
    }
}

void SkillManager::TickCoolTime()
{
    if (currentCoolTime > 0)
    {
        currentCoolTime--;
    }
}