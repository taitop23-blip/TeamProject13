#include "EventManager.h"
#include "Player.h"
#include <iostream>
#include "Utils.h"

//º¸³Ê½º ¸Þ´º Ãâ·Â
void EventManager::ShowBonusMenu(Player& p)
{
	std::cout << " -----------------\n";
	std::cout << "1. °£½ÄÈ¹µæ\n";
	std::cout << "2. Ä¿ÇÇÈ¹µæ\n";
	std::cout << "3. ÇÖ½Ä½º È¹µæ\n";
	std::cout << " -----------------\n";

	int choice = Utils::GetInput(1, 3, "º¸³Ê½º ¼±ÅÃ");
	ApplyBonus(p, choice);
}