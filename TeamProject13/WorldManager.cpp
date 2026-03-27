// WorldManager.cpp

#include "WorldManager.h"
#include "Player.h"
#include "Utils.h"
#include <iostream>


void WorldManager::ShowActionMenu(const Player& p) const
{
	std::cout << "\n========[ ¾÷¹« Áß ]========" << std::endl;
	//std::cout << " ÁøÇàµµ: " << p.GetProgress() << "%\n";
	std::cout << " À§Çèµµ: " << dangerLevel;
		     // << " ¸ñ¼û " << p.GetLife() << "°³\n";
	//std::cout << " ¸àÅ» " << p.GetMental() << "/" << p.GetMaxMental()
		     // << " ÁýÁß·Â " << p.GetFocus() << "/" << p.GetMaxFocus() "\n";

	Utils::PrintLine('-', 30);
	std::cout << " 1. ¾÷¹« ÁýÁß    (ÁøÇàµµ+, ¸àÅ»-, ÁýÁß·Â(Mp)-, À§Çèµµ+)\n";
	std::cout << " 2. Ä¿ÇÇ ÃæÀü    (ÁýÁß·Â(Mp)+, ¸àÅ» ¼ÒÆø-)\n";
	std::cout << " 3. À¯Æ©ºê ½ÃÃ»  (ÁøÇàµµ-, ¸àÅ»+, À§Çèµµ++\n";
	std::cout << " 4. ¸ô·¡ ½ºÆ®·¹Äª(¸àÅ»+, ÁýÁß·Â(Mp) ¼ÒÆø+\n";
	std::cout << " 5. »óÅÂ È®ÀÎ \n";
	std::cout << " 6. »óÁ¡ °¡±â\n";
	Utils::PrintLine('-', 30);
}


void WorldManager::FocusWork(Player& p){
	
	int progressGain = Utils::GetRandom(5, 10);
	// p.AddProgress(progressGain);
	// p.SubMental(5);
	// p.SubFocus(10);
	dangerLevel += 15;

	std::cout << "\n [¾÷¹« ÁýÁß] ¿­½ÉÈ÷ ÀÏÇß½À´Ï´Ù.\n";
	std::cout << " ÁøÇàµµ +" << progressGain << " | ¸àÅ» -5 | ÁýÁß·Â -10 | À§Çèµµ +15 |\n";
}

void WorldManager::DrinkCoffee(Player& p)
{
	// p.AddFocus(20);
	// p.SubMental(3);

	std::cout << "\n [Ä¿ÇÇ ÃæÀü] ¾ÆÀÌ½º ¾Æ¸Þ¸®Ä«³ë ÂÞ¿Ò!\n";
	std::cout << " ÁýÁß·Â +20 | ¸àÅ» -3\n";
}

void WorldManager::WatchYoutube(Player& p)
{
	// p.AddProgress(-5);
	// p.AddMental(10);
	// p.SubFocus(15);
	dangerLevel += 20;

	std::cout << "\n  [À¯Æ©ºê ½ÃÃ»] Àá±ñ¸¸ º¸·Á´Ù°¡...\n";
	std::cout << "  ÁøÇàµµ -5 | ¸àÅ» +10 | ÁýÁß·Â -15 | À§Çèµµ +20\n";
}

void WorldManager::Stretching(Player& p)
{
	// p.AddMental(8);
	// p.AddFocus(5);

	std::cout << "\n  [¸ô·¡ ½ºÆ®·¹Äª] ½½Â½ ±âÁö°³¸¦ ÄÕ´Ï´Ù.\n";
	std::cout << "  ¸àÅ» +8 | ÁýÁß·Â +5\n";
}


bool WorldManager::CheckEncounter() {

	int randomValue = Utils::GetRandom(1, 100);
	bool encounter = (randomValue <= dangerLevel);

	if (encounter) {
		if (dangerLevel >= 70)
			std::cout << "\n À§Çèµµ Æø¹ß! ºô·±ÀÌ ´ç½ÅÀ» Ã£¾Æ³Â½À´Ï´Ù!\n";
		else if (dangerLevel >= 40)
			std::cout << "\n ºô·±ÀÌ ´ç½ÅÀÇ µýÁþÀ» Æ÷ÂøÇß½À´Ï´Ù!\n";
		else
			std::cout << "\n ³·Àº È®·üÀ» ¶Õ°í ºô·±°ú ¸¶ÁÖÃÆ½À´Ï´Ù!\n";
	}
	else {
		if (dangerLevel >= 50)
			std::cout << "\n ºô·±ÀÌ ´ç½ÅÀ» Áö³ªÃÄ°©´Ï´Ù.\n";
	}
	return encounter;
}


bool WorldManager::RunWorkLoop(Player& p)
{
	while (true)
	{
		// ÁøÇàµµ 100% ¡æ º¸½ºÀü ½ÅÈ£
		if (IsReadyForFinalBoss(p.GetProgress())) return true;

		// ¸àÅ» Ã¼Å©
		if (!p.IsAlive())
		{
			if (p.GetLife() > 0)
			{
				p.SubLife(1);
				std::cout << "\n  [¸àÅ» ºØ±«] µ¿·áÀÇ ÀÀ¿øÀ¸·Î ´Ù½Ã ÀÏ¾î³³´Ï´Ù!\n";
				std::cout << "  ³²Àº ¸ñ¼û: " << p.GetLife()
					<< "°³ | ÆÐ³ÎÆ¼: ÁøÇàµµ -10%\n";
				p.RestoreFullMental();
				p.AddProgress(-10);
			}
			else
			{
				// ¸ñ¼ûµµ 0 ¡æ °ÔÀÓ¿À¹ö ½ÅÈ£
				return false;
			}
		}

		ShowActionMenu(p);
		int choice = Utils::GetInput(1, 6);

		switch (choice)
		{
		case 1: FocusWork(p);   break;
		case 2: DrinkCoffee(p); break;
		case 3: WatchYoutube(p);break;
		case 4: Stretching(p);  break;
		case 5: p.ShowStatus(); continue;
		case 6: ShopManager::RunShop(p); continue;
		}

		// Çàµ¿ ÈÄ ·£´ý ÀÌº¥Æ® ³Ö±â
		

		// ºô·± Á¶¿ì ÆÇÁ¤
		if (CheckEncounter())
		{
			// ºô·± ÀÌ¸§ Ç® 
			const char* villains[] = {
				"ºÎÀå´Ô", "±âÈ¹ÀÚ", "ÆÀÀå´Ô",
			};
			std::string name = villains[Utils::GetRandom(0, 2)];

			Monster m(name, std::max(1, dangerLevel / 10 + 1));
			BattleManager bm;
			bm.StartBattle(p, m);
		}
	}
}