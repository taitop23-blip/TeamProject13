// Utils.cpp 구분선/ 랜덤 함수
// Utils.cpp

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