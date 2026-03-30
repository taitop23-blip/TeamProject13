#include "WorldManager.h"
#include "Monster.h"
#include "BattleManager.h"
#include "Player.h"
#include "Utils.h"
#include "ConsoleWidget.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <conio.h>

WorldManager::WorldManager()
    : dangerLevel(0), isFinalBossAppeared(false), bonusLvl3(false), bonusLvl6(false), bonusLvl9(false) {
}

void WorldManager::ShowActionMenu(const Player& p) const
{
    ConsoleWidget::CaptureAndDrawBox([&]() {
        std::cout << "\n======================[ 업무 중 ]======================" << std::endl;
        std::cout << "[사무실] 진행도 " << p.GetProgress()
            << "% | 위험도 " << dangerLevel
            << " | 라이프 " << p.GetLife()
            << " | 골드 " << p.GetGold() << "G\n";
        std::cout << "멘탈 " << p.GetMental() << "/" << p.GetMaxMental()
            << " | 집중력 " << p.GetFocus() << "/" << p.GetMaxFocus();
        std::cout << " | LV" << p.GetLevel() << " 경험치 " << p.GetExp() << "/" << p.GetMaxExp() << std::endl;
       
        Utils::PrintLine('-', 55);
        std::cout << " 1. 업무 집중    (진행도+, 멘탈-, 집중력-, 위험도+)\n";
        std::cout << " 2. 커피 충전    (집중력+, 멘탈 소폭-)\n";
        std::cout << " 3. 유튜브 시청  (진행도-, 멘탈+, 집중력-, 위험도++)\n";
        std::cout << " 4. 몰래 스트레칭(멘탈+, 집중력 소폭+)\n";
        std::cout << " 5. 사내 매점 가기\n";
        std::cout << " 6. 상태/인벤토리 보기\n";
        std::cout << " 7. 게임 종료\n";
        Utils::PrintLine('-', 55);
        });
}

void WorldManager::ShowGameObjective() const
{
    ConsoleWidget::CaptureAndDrawBox([&]() {
        std::cout << "======================== [ 게임 목표 ] ========================\n";
        std::cout << "\n";
        std::cout << " 1. 최종 목표 : 무사히 업무를 마치고 '정시 퇴근' 하십시오!\n";
        std::cout << "\n";
        std::cout << " 2. 상태 관리 : 업무를 하면 [멘탈]과 [집중력]이 깎입니다.\n";
        std::cout << "                스트레스로 멘탈이 바닥나면 과로사(게임오버)!\n";
        std::cout << "\n";
        std::cout << " 3. 돌발 전투 : 업무 중이거나 농땡이를 피울 때, 예고 없이\n";
        std::cout << "                회사 내 빌런이 등장해 전투가 벌어집니다.\n";
        std::cout << "\n";
        std::cout << " 4. 최종 보스 : 진행도가 100%가 되면 [최종보스 팀장님]이 나타납니다!\n";
        std::cout << "\n";
        std::cout << " 5. 게임 승리 : 퇴근 직전 [팀장님]의 최종 결재를 넘어\n";
        std::cout << "                무사히 야근 지옥에서 살아남으세요!\n";
        std::cout << "\n";
        std::cout << "===============================================================\n";
        });

    std::cout << "\n   [ 숙지했습니다. (아무 키나 눌러 다음으로 이동) ]";
    _getch();
}

void WorldManager::ShowStatus(const Player& p) const
{
    ConsoleWidget::CaptureAndDrawBox([&]() {
        Utils::PrintLine('=', 50);
        std::cout << "[상태창]\n";
        std::cout << "이름: " << p.GetName() << " | 레벨: " << p.GetLevel()
            << " | 경험치: " << p.GetExp() << "/" << p.GetMaxExp() << "\n";
        std::cout << "멘탈: " << p.GetMental() << "/" << p.GetMaxMental()
            << " | 집중력: " << p.GetFocus() << "/" << p.GetMaxFocus() << "\n";
        std::cout << "공격력: " << p.GetAtk() << " | 방어력: " << p.GetDef()
            << " | 라이프: " << p.GetLife() << "\n";
        std::cout << "진행도: " << p.GetProgress() << "% | 골드: " << p.GetGold()
            << "G | 위험도: " << dangerLevel << "\n";
        Utils::PrintLine('=', 50);
        });
    p.PrintInventory();
}

void WorldManager::FocusWork(Player& p)
{
    int progressGain = Utils::GetRandom(5, 10);
    p.AddProgress(progressGain);
    p.SubMental(5);
    p.SubFocus(10);
    dangerLevel = std::min(100, dangerLevel + 15);
    ConsoleWidget::CaptureAndDrawBox([&]() {
        system("cls");
        std::cout << "\n[업무 집중] 열심히 일했습니다.\n";
        std::cout << "진행도 +" << progressGain << " | 멘탈 -5 | 집중력 -10 | 위험도 +15\n";
        });
}

void WorldManager::DrinkCoffee(Player& p)
{
    p.AddFocus(20);
    p.SubMental(3);
    ConsoleWidget::CaptureAndDrawBox([&]() {
        system("cls");
        std::cout << "\n[커피 충전] 아이스 아메리카노 쭈왑!\n";
        std::cout << "집중력 +20 | 멘탈 -3\n";
        });
}

void WorldManager::WatchYoutube(Player& p)
{
    p.AddProgress(-5);
    p.AddMental(10);
    p.SubFocus(15);
    dangerLevel = std::min(100, dangerLevel + 20);
    ConsoleWidget::CaptureAndDrawBox([&]() {
        system("cls");
        std::cout << "\n[유튜브 시청] 잠깐만 보려다가...\n";
        std::cout << "진행도 -5 | 멘탈 +10 | 집중력 -15 | 위험도 +20\n";
        });
}

void WorldManager::Stretching(Player& p)
{
    p.AddMental(8);
    p.AddFocus(5);
    ConsoleWidget::CaptureAndDrawBox([&]() {
        system("cls");
        std::cout << "\n[몰래 스트레칭] 슬쩍 기지개를 켭니다.\n";
        std::cout << "멘탈 +8 | 집중력 +5\n";
        });
}

bool WorldManager::CheckEncounter()
{
    int randomValue = Utils::GetRandom(1, 100);
    bool encounter = (randomValue <= dangerLevel);

    if (encounter) {
        std::cout << "\n[경고] 수상한 기척이 느껴집니다... 누군가 다가옵니다!\n";
    }
    else if (dangerLevel >= 50) {
        std::cout << "주변 시선이 신경 쓰이지만 아직 들키진 않았습니다.\n";
    }

    return encounter;
}

Monster WorldManager::CreateEncounterMonster(const Player& p) const
{
    const std::vector<std::string> names = {
        "부장님", "기획자"
    };

    const int levelScale = p.GetLevel() * 3;
    const int progressScale = p.GetProgress() / 6;
    const int basePressure = 48 + levelScale + progressScale + dangerLevel / 3;
    const int baseAtk = 12 + p.GetLevel() * 2 + dangerLevel / 12;
    const int baseDef = 5 + p.GetLevel() + dangerLevel / 20;
    const int expReward = 32 + p.GetLevel() * 9;
    const int goldReward = 100 + dangerLevel * 3;

    const std::string& selectedName = names[static_cast<std::size_t>(Utils::GetRandom(0, static_cast<int>(names.size()) - 1))];
    return Monster(selectedName, basePressure, baseAtk, baseDef, expReward, goldReward);
}

bool WorldManager::IsReadyForFinalBoss(int currentProgress)
{
    if (currentProgress >= maxProgress && !isFinalBossAppeared) {
        isFinalBossAppeared = true;
        return true;
    }
    return false;
}


void WorldManager::CheckLevelBonus(Player& p)
{
    if (!bonusLvl3 && p.GetLevel() >= 3) {
        bonusLvl3 = true;
        eventManager.ShowBonusMenu(p);
    }
    if (!bonusLvl6 && p.GetLevel() >= 6) {
        bonusLvl6 = true;
        eventManager.ShowBonusMenu(p);
    }
    if (!bonusLvl9 && p.GetLevel() >= 9) {
        bonusLvl9 = true;
        eventManager.ShowBonusMenu(p);
    }
}

void WorldManager::HandleCollapse(Player& p, const char* reason)
{
    std::cout << "\n[붕괴] " << reason << "\n";
    p.SubLife();
    p.AddProgress(-5);
    if (!p.IsDead()) {
        p.RecoverAfterCollapse();
        dangerLevel = std::max(0, dangerLevel - 10);
        std::cout << "잠깐 멍 때리다 정신을 차렸습니다. 남은 라이프: " << p.GetLife() << "\n";
    }
}

bool WorldManager::RunWorkLoop(Player& p)
{
    while (true) {
        if (IsReadyForFinalBoss(p.GetProgress())) {
            return true;
        }

        if (p.IsDead()) {
            return false;
        }

        if (p.HasCollapsed()) {
            HandleCollapse(p, "멘탈이 완전히 바닥났습니다.");
            if (p.IsDead()) {
                return false;
            }
        }

        CheckLevelBonus(p);
        ShowActionMenu(p);

        const int choice = Utils::GetInput(1, 7, "선택: ");
        switch (choice) {
        case 1:
            FocusWork(p);
            break;
        case 2:
            DrinkCoffee(p);
            break;
        case 3:
            WatchYoutube(p);
            break;
        case 4:
            Stretching(p);
            break;
        case 5:
            shopManager.ShopConsole(p);
            break;
        case 6:
            ShowStatus(p);
            break;
        case 7:
            return false;
        }

        if (choice >= 1 && choice <= 4) {
            if (p.HasCollapsed()) {
                continue;
            }

            eventManager.TriggerRandomEvent(p, dangerLevel);
            if (p.HasCollapsed()) {
                continue;
            }

            if (CheckEncounter()) {
                Monster enemy = CreateEncounterMonster(p);
                BattleManager battleManager;
                battleManager.StartBattle(p, enemy);
                dangerLevel = std::max(0, dangerLevel - 25);

                if (p.IsDead()) {
                    return false;
                }
            }
        }
    }
}
