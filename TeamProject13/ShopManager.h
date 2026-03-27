#pragma once
#include "Player.h"
#include "Item.h"
#include <vector>

class Item;

class ShopManager {
private:
	std::vector<Item> shopInventory; // Item class vector. price, itemName 정보 필요 
public:
	ShopManager() {}	// Item class의 instance 생성 시, shopInventory 채울 예정 
	~ShopManager() {}
	void displayItems();     	// 상점 물품 출력
	void buyItem(Player& player);	// 구매, 플레이어 인벤토리에 아이템 추가
//	void sellItem(Player& player);	// 판매, 아직 구현 미정, 구현 시 플레이어 인벤토리 아이템 소멸  
	void shopConsole(Player& player);			// 상점 조작 콘솔 
};

