#include "Player.h"
#include "WorldManager.h"
#include "BattleManager.h"
#include "Monster.h"
#include "Utils.h"
#include "ConsoleWidget.h"

#ifdef _WIN32
#include <windows.h>
#endif
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <ctime>
#include <string>
#include <conio.h>


static void SetupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    std::setlocale(LC_ALL, ".UTF-8");
}

enum class ConsoleColor {
    WHITE = 7,
    GREEN = 10,
    CYAN = 11,
    RED = 12,
    YELLOW = 14,
    BRIGHT_WHITE = 15
};

void SetColor(ConsoleColor color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color);
}

class SoundManager {
public:
    static void PlayBGM(const std::string& fileName, int volume = 200) { // 기본 볼륨을 200으로 설정
        mciSendStringA("stop mybgm", NULL, 0, NULL);
        mciSendStringA("close mybgm", NULL, 0, NULL);

        std::string openCmd = "open \"" + fileName + "\" type mpegvideo alias mybgm";
        mciSendStringA(openCmd.c_str(), NULL, 0, NULL);

        // (볼륨 설정)
        std::string volCmd = "setaudio mybgm volume to " + std::to_string(volume);
        mciSendStringA(volCmd.c_str(), NULL, 0, NULL);

        mciSendStringA("play mybgm repeat", NULL, 0, NULL);
    }

    static void StopBGM() {
        mciSendStringA("stop mybgm", NULL, 0, NULL);
        mciSendStringA("close mybgm", NULL, 0, NULL);
    }
};

static Player SelectCharacter()
{
    ConsoleWidget::CaptureAndDrawBox([&]() {
        std::cout << "\n======================= [ 캐릭터 선택 ] =======================\n";
        std::cout << "1. A형 사원 (공격형 | 멘탈 170, 집중력 95, ATK 34, DEF 10)\n";
        std::cout << "2. B형 사원 (밸런스 | 멘탈 210, 집중력 85, ATK 28, DEF 15)\n";
        std::cout << "3. C형 사원 (방어형 | 멘탈 250, 집중력 70, ATK 22, DEF 22)\n";
        std::cout << "===============================================================\n";
        });

        int choice = Utils::GetInput(1, 3, "선택: ");
        switch (choice) {
        case 1: return Player("A형 사원", 170, 95, 34, 10);
        case 2: return Player("B형 사원", 210, 85, 28, 15);
        case 3: return Player("C형 사원", 250, 70, 22, 22);
        default: return Player("B형 사원", 210, 85, 28, 15);
        }
}

static bool RunFinalBoss(Player& p)
{
    p.RestoreAll();
    p.AddItem(Item(ItemType::HOTSIX));
    p.AddItem(Item(ItemType::KEYBOARD));

    system("cls");
    ConsoleWidget::CaptureAndDrawBox([&]() {
        SetColor(ConsoleColor::YELLOW);
        std::cout << "\n [ 긴급: 최종 결재 서류 준비 완료 ]\n";
        SetColor(ConsoleColor::WHITE);
        std::cout << "\n최종 결재를 앞두고 모든 자료를 다시 정리했습니다.\n";
        std::cout << "멘탈과 집중력이 완전히 회복되었고, 마지막 대비용 아이템도 챙겼습니다.\n";

        SetColor(ConsoleColor::RED);
        Utils::PrintLine('*', 46);
        std::cout << "★★★ 최종 보스 등장 : 팀장님 ★★★\n";
        Utils::PrintLine('*', 46);
        SetColor(ConsoleColor::WHITE);
        });

    Monster boss("팀장님", 260, 32, 14, 120, 500);
    BattleManager bm;
    return bm.StartBattle(p, boss);
}

int main()
{
    SoundManager::PlayBGM("13-01 Back in my days.wav");

    SetupConsoleEncoding();
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    {
        ConsoleWidget::CaptureAndDrawBox([&]() {
            Utils::PrintLine('=', 50);
            std::cout << "-------펄없이스의 등대 - 야근하기 싫어!!!-------\n";
            Utils::PrintLine('=', 50);

            std::cout << "???는 펄없이스에서 근무하고 있는 이른바 사축이다.\n";
            std::cout << "늘 그의 정장 안쪽 주머니에는 사직서가...\n";
            std::cout << "오늘도 무사히 퇴근 할 수 있을까?\n";
            });
    }

    std::cout << "\n   아무 키나 누르면 캐릭터 선택으로 넘어갑니다...";
    _getch(); // 사용자가 키를 하나 누를 때까지 여기서 멈춰있습니다.

    system("cls");
    Player player = SelectCharacter();
    system("cls");

    WorldManager world;

    bool reachedBoss = world.RunWorkLoop(player);

    if (!reachedBoss) {
        if (player.IsDead()) {
            Utils::PrintLine('=', 30);
            std::cout << "[ 게임오버 ]\n";
            std::cout << "펄없이스에서 퇴출당했습니다.\n";
        }
        else {
            std::cout << "오늘은 여기까지. 조용히 자리를 정리하고 퇴근합니다.\n";
        }
        Utils::PrintLine('=', 30);
        return 0;
    }

    bool victory = RunFinalBoss(player);

    Utils::PrintLine('=', 30);
    if (victory)
    {
        std::cout << "[진엔딩]\n";
        std::cout << "축하합니다! 최종결재 완료!\n";
        std::cout << "당신은 전설의 월급루팡이 되었습니다!\n";
    }
    else
    {
        std::cout << "[배드엔딩]\n";
        std::cout << "근무태만으로 회사에서 짤렸습니다.\n";
    }
    Utils::PrintLine('=', 30);

    return 0;
}
