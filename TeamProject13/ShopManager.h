#pragma once

#include "Player.h"
#include "Item.h"
#include <vector>



class Item;

class ShopManager {
private:
	std::vector<Item> shopInventory; 
public:
	ShopManager(); 	
	~ShopManager() {}
	void DisplayItems();     	// 상점 물품 출력
	void BuyItem(Player& player);	// 구매, 플레이어 인벤토리에 아이템 추가
	void SellItem(Player& player);	// 판매, 플레이어 인벤토리의 아이템 소멸  
	void ShopConsole(Player& player);			// 상점 조작 콘솔 
};



