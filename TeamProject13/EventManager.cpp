#include "EventManager.h"
#include "Player.h"
#include "Utils.h"

// [수정/추가사항] std::max 등의 함수를 사용하기 위해 <algorithm> 헤더 추가
#include <algorithm>
#include <iostream>

void EventManager::ShowBonusMenu(Player& p)
{
    // [수정/추가사항] 하드코딩된 구분선("---") 대신 Utils::PrintLine 함수를 사용하여 출력 형식을 깔끔하게 개선
    Utils::PrintLine('=', 46);
    // [수정/추가사항] 기존의 단순한 텍스트(간식/커피 등) 대신, 명확한 보상 수치(멘탈/집중력/진행도)를 보여주도록 메뉴 수정
    std::cout << "[레벨 보너스] 원하는 보상을 하나 선택하세요.\n";
    std::cout << "1. 멘탈 회복 (+20)\n";
    std::cout << "2. 집중력 회복 (+20)\n";
    std::cout << "3. 진행도 상승 (+10)\n";
    Utils::PrintLine('=', 46);

    // [수정/추가사항] 변수를 const로 선언하여 안전성을 높이고, 입력 안내 문구에 콜론(:)과 공백을 추가하여 가독성 개선
    const int choice = Utils::GetInput(1, 3, "보너스 선택: ");
    ApplyBonus(p, choice);
}

// [수정/추가사항] 헤더에 선언만 되어 있던 ApplyBonus 함수의 구현부 전체 추가 (실제 플레이어 스탯 증감 로직 적용)
void EventManager::ApplyBonus(Player& p, int choice)
{
    switch (choice) {
    case 1:
        p.AddMental(20);
        std::cout << "멘탈이 20 회복되었습니다.\n";
        break;
    case 2:
        p.AddFocus(20);
        std::cout << "집중력이 20 회복되었습니다.\n";
        break;
    case 3:
        p.AddProgress(10);
        std::cout << "진행도가 10 상승했습니다.\n";
        break;
    }
}

// [수정/추가사항] LNK2019 링킹 에러를 해결하기 위해 TriggerRandomEvent (랜덤 이벤트) 구현부 전체 추가
bool EventManager::TriggerRandomEvent(Player& p, int& dangerLevel)
{
    if (Utils::GetRandom(1, 100) > 25) return false;

    Utils::PrintLine('-', 46);
    switch (Utils::GetRandom(1, 4)) {
    case 1:
        std::cout << "[랜덤 이벤트] 간식 카트가 도착했습니다!\n";
        p.AddMental(8);
        p.AddFocus(8);
        dangerLevel = std::max(0, dangerLevel - 5);
        std::cout << "멘탈 +8, 집중력 +8, 위험도 -5\n";
        break;
    case 2:
        std::cout << "[랜덤 이벤트] 급한 수정 요청이 들어왔습니다!\n";
        p.SubMental(10);
        p.SubFocus(6);
        dangerLevel = std::min(100, dangerLevel + 12);
        std::cout << "멘탈 -10, 집중력 -6, 위험도 +12\n";
        break;
    case 3:
        std::cout << "[랜덤 이벤트] 동료가 자료를 도와줬습니다.\n";
        p.AddProgress(6);
        dangerLevel = std::max(0, dangerLevel - 10);
        std::cout << "진행도 +6, 위험도 -10\n";
        break;
    case 4:
        std::cout << "[랜덤 이벤트] 특별 수당을 받았습니다!\n";
        p.AddGold(120);
        std::cout << "골드 +120\n";
        break;
    }
    Utils::PrintLine('-', 46);
    return true;
}