// Utils.cpp 구분선/ 랜덤 함수

#include "Utils.h"
#include <iostream>
#include <random>

void Utils::PrintLine(char ch, int len)
{
    for (int i = 0; i < len; ++i) std::cout << ch;
    std::cout << "\n";
}

int Utils::GetRandom(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

int Utils::GetInput(int min, int max, const std::string& prompt)
{
    int val;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> val && val >= min && val <= max) return val;
        std::cout << "  [오류] " << min << "~" << max << " 사이 숫자를 입력하세요.\n";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
}