//#include <iostream>
//#include "ShopManager.h"
//#include "Utils.h"
//void ShopManager::displayItems() {
//	Utils::PrintLine('=');
//	std::cout << "여어~ 요즘 일은 어때?" << std::endl << std::endl;
//
//	std::vector<Item>::iterator it;
//	int index = 1;
//	for (it = shopInventory.begin(); it != shopInventory.end(); ++it) {	// 상품 목록 출력 
//		std::cout << index << ": " << it->getName() << "  ";
//		std::cout << "가격: " << it->getPrice() << "원" << std::endl;
//		++index;
//	}
//}
//void ShopManager::buyItem(Player& player) {
//	int select;
//	std::cout << "구매할 상품 번호를 입력: ";
//	std::cin >> select;
//	select -= 1; // 선택한 물품의 인덱스와 벡터의 해당 물건 인덱스 동기화
//
//	int itemPrice = shopInventory[select].getPrice();
//	std::string itemName = shopInventory[select].getName();
//	if (player.getGold() < itemPrice) {		// 소지금이 물품가액보다 작으면 종료 
//		std::cout << "돈이 모자른것 같은데?" << std::endl << std::endl;
//		return;
//	}
//	player.subGold(itemPrice);
//	PlayerInventory.pushItem(itemName, itemPrice); // 플레이어 인벤토리 클래스 내 인벤토리 벡터에 item 임시 객체 push
//
//	std::cout << "매번 고마워. 쉬엄쉬엄하라구." << std::endl << std::endl;
//	return;
//}
//void ShopManager::shopConsole(Player& player) {
//	displayItems();
//
//	while (1) {
//		int select;
//		std::cout << "1) 물건을 산다. 2) 떠난다" << std::endl;
//		std::cout << "번호 선택: ";
//		std::cin >> select;
//
//		switch (select) {
//		case 1:
//			buyItem(player);
//			break;
//		case 2:
//			std::cout << "다음에 또 오라구!" << std::endl;
//			return;
//		}
//	}
//
//}