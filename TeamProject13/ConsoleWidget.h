// ConsoleWidget.h

#pragma once
#include <string>
#include <vector>
#include <functional>

class ConsoleWidget
{
public:
	static void DrawTextBox(const std::string& text);
	static void DrawMultiLineBox(const std::vector<std::string>& lines);
	static void DrawStringBox(const std::string& fullText);
	static void CaptureAndDrawBox(std::function<void()> func);
	static int GetVisualWidth(const std::string& str);


private:
	static void PrintTopBottom(int width);
};

