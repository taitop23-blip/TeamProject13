// Player.cpp

#include "Player.h"
// [수정/추가사항 1] 유틸리티 함수(Utils)와 std::clamp(값 범위 제한)를 사용하기 위해 헤더 추가
#include "Utils.h"

#include <algorithm>
#include <iostream>

// [수정/추가사항 2] 플레이어 객체 생성 시 기본 스탯(레벨, 체력, 골드 등)을 설정하는 기본 생성자 구현
Player::Player()
    : level(1), exp(0), maxExp(100), name("Player"),
      mental(100), maxMental(100), focus(50), maxFocus(50),
      atk(10), def(5), progress(0), life(3), gold(0),
      tempAtkBonus(0), tempDefBonus(0)
{
}

// [수정/추가사항 3] 이름을 비롯한 주요 스탯을 외부에서 입력받아 초기화할 수 있는 오버로딩 생성자 구현
Player::Player(const std::string& name, int mental, int focus, int atk, int def)
    : level(1), exp(0), maxExp(100), name(name),
      mental(mental), maxMental(mental), focus(focus), maxFocus(focus),
      atk(atk), def(def), progress(0), life(3), gold(500),
      tempAtkBonus(0), tempDefBonus(0)
{
}

// [수정/추가사항 4] 기존의 복잡했던 if문(최대치/최소치 초과 방지 로직)을 std::clamp를 사용하여 한 줄로 깔끔하게 최적화

// std::clamp(v, lo, hi);
// v: 검사할 값, 
// lo: 허용되는 최소값 (Lower bound), 
// hi: 허용되는 최대값 (Upper bound)

void Player::AddMental(int val)
{
    // 현재 멘탈에 val을 더한 값이 0 ~ maxMental 사이를 벗어나지 않도록 강제 고정
    mental = std::clamp(mental + val, 0, maxMental);
}

void Player::AddFocus(int val)
{
    focus = std::clamp(focus + val, 0, maxFocus);
}

void Player::AddProgress(int val)
{
    progress = std::clamp(progress + val, 0, 100);
}

// (SubMental 등 나머지 스탯 관련 함수들도 std::clamp를 사용하거나 유사한 방식으로 최적화됨)


// =========================================================
// [수정/추가사항 5] 상점 및 아이템 사용을 위한 인벤토리 기능 대거 추가
// =========================================================

void Player::AddGold(int val)
{
    gold = std::max(0, gold + val);
}

void Player::AddExp(int val)
{
    if (val <= 0) {
        return;
    }

    exp += val;
    while (exp >= maxExp) {
        exp -= maxExp;
        level++;
        maxExp += 50;
        maxMental += 10;
        maxFocus += 5;
        atk += 2;
        def += 2;
        mental = maxMental;
        focus = maxFocus;
    }
}

void Player::AddAtk(int val)
{
    atk = std::max(0, atk + val);
}

void Player::AddDef(int val)
{
    def = std::max(0, def + val);
}

void Player::SubMental(int val)
{
    mental = std::max(0, mental - val);
}

void Player::SubFocus(int val)
{
    focus = std::max(0, focus - val);
}

void Player::SubLife()
{
    life = std::max(0, life - 1);
}

void Player::SubGold(int val)
{
    gold = std::max(0, gold - val);
}

void Player::SubProgress(int val)
{
    progress = std::max(0, progress - val);
}

bool Player::SpendGold(int val)
{
    if (gold < val) {
        return false;
    }

    gold -= val;
    return true;
}

void Player::AddTempDef(int val) 
{
    tempDefBonus += val;
}

void Player::RestoreFullMental()
{
    mental = maxMental;
}

void Player::RestoreFullFocus()
{
    focus = maxFocus;
}

void Player::RestoreAll()
{
    RestoreFullMental();
    RestoreFullFocus();
    ClearTemporaryBattleBonuses();
}

void Player::RecoverAfterCollapse()
{
    mental = std::max(1, maxMental / 2);
    focus = std::max(1, maxFocus / 2);
    ClearTemporaryBattleBonuses();
}

void Player::AddTemporaryAtk(int val)
{
    tempAtkBonus += val;
}

void Player::AddTemporaryDef(int val)
{
    tempDefBonus += val;
}

void Player::ClearTemporaryBattleBonuses()
{
    tempAtkBonus = 0;
    tempDefBonus = 0;
}

void Player::AddItem(const Item& item)
{
    inventory.push_back(item);
    std::cout << item.GetName() << " 아이템을 획득했습니다.\n";
}

const Item* Player::GetItem(std::size_t index) const
{
    // 인덱스 범위 초과 에러 방지 안전장치
    if (index >= inventory.size()) {
        return nullptr;
    }
    return &inventory[index];
}

bool Player::RemoveItem(std::size_t index)
{
    if (index >= inventory.size()) {
        return false;
    }

    inventory.erase(inventory.begin() + static_cast<std::ptrdiff_t>(index));
    return true;
}

// [수정/추가사항 6] LNK2019 링킹 에러의 원인이었던 인벤토리 출력(PrintInventory) 함수 구현 완료
void Player::PrintInventory() const
{
    std::cout << "\n[인벤토리]\n";
    if (inventory.empty()) {
        std::cout << "보유한 아이템이 없습니다.\n";
        return;
    }

    for (std::size_t i = 0; i < inventory.size(); ++i) {
        std::cout << i + 1 << ". " << inventory[i].GetName() << "\n";
    }
}

// [수정/추가사항 7] 플레이어의 현재 스탯과 진행 상황을 한눈에 보여주는 상태창 출력 함수 구현 완료
void Player::ShowCurrentStatus() const
{
    Utils::PrintLine('=', 44);
    std::cout << "[플레이어 상태]\n";
    std::cout << "이름: " << name << "\n";
    std::cout << "레벨: " << level << " (EXP " << exp << "/" << maxExp << ")\n";
    std::cout << "멘탈: " << mental << "/" << maxMental << "\n";
    std::cout << "집중력: " << focus << "/" << maxFocus << "\n";
    std::cout << "공격력: " << GetAtk() << "\n";
    std::cout << "방어력: " << GetDef() << "\n";
    std::cout << "진행도: " << progress << "%\n";
    std::cout << "라이프: " << life << "\n";
    std::cout << "골드: " << gold << "G\n";
    Utils::PrintLine('=', 44);
}

void Player::ResetTempStats() {
    tempAtkBonus = 0;
    tempDefBonus = 0;
}
