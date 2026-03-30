// ConsoleWidget.cpp

#include "ConsoleWidget.h"
#include <iostream>
#include <algorithm>
#include <sstream>

void ConsoleWidget::PrintTopBottom(int width)
{
    std::cout << "█";
    for (int i = 0; i < width + 2; ++i) std::cout << "█";
    std::cout << "█\n";
}

int ConsoleWidget::GetVisualWidth(const std::string& str)
{
    int width = 0;
    for (size_t i = 0; i < str.length(); ) {
        // ASCII 문자인 경우 (0~127)
        if ((unsigned char)str[i] < 128) {
            width += 1;
            i += 1;
        }
        // 한글 등 멀티바이트 문자인 경우
        else {
            width += 2; // 시각적으로는 2칸 차지

            if ((unsigned char)str[i] >= 224) i += 3;      // UTF-8
            else if ((unsigned char)str[i] >= 192) i += 2; // UTF-8 2바이트
            else i += 1; // CP949 등 기타
        }
    }
    return width;
}
void ConsoleWidget::DrawMultiLineBox(const std::vector<std::string>& lines)
{
    if (lines.empty()) return;

    // 1. 가장 긴 줄의 시각적 너비 구하기
    int maxWidth = 0;
    for (const auto& line : lines) {
        int vWidth = GetVisualWidth(line);
        if (vWidth > maxWidth) maxWidth = vWidth;
    }

    // 2. 전체 박스의 '내부 너비' 계산 (글자 + 좌우 여백 2칸씩)
    int paddingX = 2;
    int innerWidth = maxWidth + (paddingX * 2);

    // 3. 윗 테두리 █가 1칸이므로 내부너비 + 양쪽벽(2) 만큼 그대로 찍음
    std::cout << "\n ";
    for (int i = 0; i < innerWidth + 2; ++i) {
        std::cout << "█";
    }
    std::cout << "\n";

    // 4. 상단 빈 줄 (천장 공백)
    std::cout << " █"; // 왼쪽 벽 (1칸)
    for (int i = 0; i < innerWidth; ++i) {
        std::cout << " ";
    }
    std::cout << "█\n"; // 오른쪽 벽 (1칸)

    // 5. 내용 출력
    for (const auto& line : lines) {
        int vWidth = GetVisualWidth(line);

        // 왼쪽 벽(█) + 왼쪽 공백 2칸
        std::cout << " █  " << line;

        // 남은 공백 계산 = (최대너비 - 현재글자너비) + 오른쪽 공백 2칸
        int spacesToFill = (maxWidth - vWidth) + paddingX;
        for (int i = 0; i < spacesToFill; ++i) {
            std::cout << " ";
        }
        std::cout << "█\n"; // 오른쪽 벽
    }

    // 6. 하단 빈 줄 (바닥 공백)
    std::cout << " █";
    for (int i = 0; i < innerWidth; ++i) {
        std::cout << " ";
    }
    std::cout << "█\n";

    // 7. 아래 테두리
    std::cout << " ";
    for (int i = 0; i < innerWidth + 2; ++i) {
        std::cout << "█";
    }
    std::cout << "\n\n";
}

void ConsoleWidget::DrawStringBox(const std::string& fullText)
{
    std::stringstream ss(fullText);
    std::string segment;
    std::vector<std::string> lines;

    // 전체 텍스트를 줄바꿈(\n) 기준으로 잘라서 vector에 담기
    while (std::getline(ss, segment)) {
        if (!segment.empty() && segment.back() == '\r') segment.pop_back(); // 윈도우 줄바꿈 처리
        lines.push_back(segment);
    }
    DrawMultiLineBox(lines);
}

void ConsoleWidget::CaptureAndDrawBox(std::function<void()> func)
{
    std::stringstream buffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(); 
    std::cout.rdbuf(buffer.rdbuf());                  

    func();

    std::cout.rdbuf(oldCoutBuffer);

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(buffer, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    DrawMultiLineBox(lines);
}


void ConsoleWidget::DrawTextBox(const std::string& text)
{
    std::vector<std::string> vec = { text };
    DrawMultiLineBox(vec);
}



