// main.cpp

#include "Player.h"
#include "WorldManager.h"
#include "BattleManager.h"
#include "Monster.h"
#include "Utils.h"
#include <iostream>
#include <ctime>
#include <string>

// 캐릭터 능력치가 정해지면 능력치 값 수정
static Player SelectCharacter()
{
    std::cout << "\n========== [ 캐릭터 선택 ] ==========\n";
    std::cout << "1.A (공격형 | 멘탈 150, 집중력 100, ATK 45, DEF  5)\n ";
    std::cout << "2.B (밸런스 | 멘탈 200, 집중력  80, ATK 30, DEF 15)\n ";
    std::cout << "3.C (방어형 | 멘탈 300, 집중력  50, ATK 15, DEF 30)\n ";
    std::cout << "=====================================\n";

    int choice = Utils::GetInput(1, 3, "선택: ");

    switch (choice)
    {
    case 1: return Player("A", 150, 100, 45, 5);
    case 2: return Player("B", 200, 80, 30, 15);
    case 3: return Player("C", 300, 50, 15, 30);
    default:return Player("B", 200, 80, 30, 15);
    }
}

// 보스전 — 보스 스탯은 창욱님 Monster 작업 완료 후 수정
static bool RunFinalBoss(Player& p)
{
    std::cout << "\n";
    std::cout << "★★★  악질 사수 등장  ★★★\n";
    std::cout << "팀장님이 나타났습니다!\n";
    Utils::PrintLine('*', 46);

    Monster boss("팀장님", 300, 40, 15);

    BattleManager bm;
    return bm.StartBattle(p, boss);
}

// 메인

int main()
{
    srand((unsigned)time(nullptr));

    Utils::PrintLine('=', 30);
    std::cout << "펄없이스의 등대 - 야근하기 싫어!!!\n";
    Utils::PrintLine('=', 30);

    std::cout << "???은 펄없이스에서 근무하고 있는 이른바 사축이다.\n";
    std::cout << "늘 그의 정장 안쪽 주머니에는 사직서가...\n";
    std::cout << "오늘도 무사히 퇴근 할 수 있을까?\n";

    Player player = SelectCharacter();
    WorldManager world; 

    // 게임 루프
    bool reachedBoss = world.RunWorkLoop(player);

    if (!reachedBoss)
    {
        Utils::PrintLine('=', 30);
        std::cout << "[ 게임오버 ]\n";
        std::cout << "펄없이스에서 퇴출당했습니다.\n";
        Utils::PrintLine('=', 30);
        return 0;
    }

    // 진행도 100% 보스전
    bool vicitory = RunFinalBoss(player);

    Utils::PrintLine('=', 30);
    if (vicitory)
    {
        // 진엔딩
        std::cout << "축하합니다! 최종결재 완료!\n";
        std::cout << "당신은 전설의 월급루팡이 되었습니다!\n";
    }
    else
    {
        // 배드엔딩
        std::cout << "근무태만으로 회사에서 짤렸습니다.\n";
    }
    Utils::PrintLine('=', 30);

    return 0;
}