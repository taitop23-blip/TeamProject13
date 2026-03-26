// Utils.h
// 담당: 공용 - 수정 금지
// 역할: 랜덤, 콘솔 출력 관련 공용 도구 모음

#pragma once
#include <string>

class Utils
{
public:
	// 구분선 출력 ex) Utils::PrintLine('=', 42)
	static void PrintLine(char ch = '-', int len = 42);

	// 난수 생성 함수 추가 ex) Utils::GetRandom(1, 100)
	static int GetRandom(int min, int max);
};

