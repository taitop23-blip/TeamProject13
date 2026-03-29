//#include <iostream>
//#include "ShopManager.h"
//#include "Utils.h"
//ShopManager::ShopManager() {
//	shopInventory.push_back(Coffee);
//	shopInventory.push_back(Hotsix);
//	shopInventory.push_back(Keyboard);
//}
//void ShopManager::DisplayItems() {
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
//void ShopManager::BuyItem(Player& player) {
//	int select, min = 0, max = shopInventory.size();
//	std::cout << "오늘은 뭘 사가려나?" << std::endl;
//	while (1) {
//		std::cout << "구매할 상품 번호를 입력(0 입력 시 이전 선택지): ";
//		if (std::cin >> select && select >= min && select <= max)
//			break;
//		std::cout << "이봐, 그런 물건은 없다고." << std::endl;
//		std::cin.clear();
//		std::cin.ignore(1000, '\n');
//	}
//
//	if (select == 0) {
//		std::cout << "다음에 봐" << std::endl;
//		return;
//	}
//
//	select -= 1; // 선택한 물품의 인덱스와 벡터의 해당 물건 인덱스 동기화
//
//	int count;
//	std::cout << "몇 개 살건데?" << std::endl;
//	while (1) {
//		std::cout << "구매 개수 입력: ";
//		if (std::cin >> count)
//			break;
//		std::cout << "숫자를 말하라고!!" << std::endl;
//		std::cin.clear();
//		std::cin.ignore(1000, '\n');
//	}
//
//	int itemPrice = shopInventory[select].getPrice() * count;
//	std::string itemName = shopInventory[select].getName();
//	if (player.GetGold() < itemPrice) {		// 소지금이 물품가액보다 작으면 종료 
//		std::cout << "돈이 모자른것 같은데?" << std::endl << std::endl;
//		return;
//	}
//	player.SubGold(itemPrice);
//
//	int index;
//	bool isExist = PlayerInventory.SearchItem(itemName, index); // Inventory 벡터에서 구매한 아이템과 동일한 원소가 존재하는지 검색, 존재할 시 true반환 및 참조로 받은 index에 원소 index 대입
//	if (isExist)
//		PlayerInventory.AddStock(index, count); // true이면, 원소의 개수만 1 추가
//	else
//		PlayerInventory.pushItem(itemName, itemPrice, count); // false이면, 플레이어 인벤토리 클래스 내 인벤토리 벡터에 item 임시 객체 push
//
//	std::cout << "매번 고마워. 쉬엄쉬엄하라구." << std::endl << std::endl;
//}
//void ShopManager::SellItem(Player& player) {
//	bool isEmpty = PlayerInventory.IsEmpty();
//	if (isEmpty) {
//		std::cout << "너 가진 물건이 없잖아" << std::endl;
//		return;
//	}
//
//	int min = 0, max;
//	PlayerInventory.DisplayAll(max); // 플레이어 인벤토리의 모든 아이템 이름과 가격 출력, 각 출력은 인덱스가 있음. 또한 참조로 받은 max에 값 대입
//
//	int select;
//	std::cout << "어디보자, 뭘 팔고 싶은데?" << std::endl;
//	while (1) {
//		std::cout << "판매할 상품 번호를 입력(0 입력 시 이전 선택지): ";
//		if (std::cin >> select && select >= min && select <= max)
//			break;
//		std::cout << "네가 가진 물건 중에서 선택하라구" << std::endl;
//		std::cin.clear();
//		std::cin.ignore(1000, '\n');
//	}
//
//	if (select == 0) {
//		std::cout << "다음에 봐" << std::endl;
//		return;
//	}
//
//	select -= 1; // 선택 물품의 인덱스와 벡터의 해당 물건 인덱스 동기화
//
//	int count;
//	int itemStock = PlayerInventory.GetStock(select); // 실제로 플레이어가 가지고 있는 물건의 개수
//	std::cout << "몇 개 팔건데?" << std::endl;
//	while (1) {
//		std::cout << "판매 개수: ";
//		if (std::cin >> count)
//			break;
//		std::cout << "숫자를 입력하라고!!" << std::endl;
//		std::cin.clear();
//		std::cin.ignore(1000, '\n');
//	}
//
//	if (count == 0) {
//		std::cout << "장난치냐!" << std::endl;
//		return;
//	}
//	if (count > itemStock) {
//		std::cout << "넌 그 물건을 그렇게 많이 가지고 있지 않아." << std::endl;
//		return;
//	}
//
//	int itemPrice = PlayerInventory.getPrice(select) * count; // Inventory 클래스의 인벤토리 벡터의 인덱스가 select인 원소의 price를 get
//	player.Addgold(itemPrice);
//
//	std::string itemName = PlayerInventory.getName(select);
//	if (itemStock == count)
//		PlayerInventory.eraseItem(select); // Inventory 클래스의 인벤토리 벡터의 인덱스가 select인 원소를 erase
//	else
//		PlayerInventory.SubStock(select, count); 
//
//	std::cout << "물건 잘 받았어." << std::endl;
//}
//void ShopManager::ShopConsole(Player& player) {
//	DisplayItems();
//
//	while (1) {
//		int select;
//		std::cout << "1) 물건을 산다. 2) 물건을 판다. 3) 떠난다." << std::endl;
//		std::string msg = "번호 선택: ";
//		select = Utils::GetInput(1, 3, msg);
//
//		switch (select) {
//		case 1:
//			BuyItem(player);
//			break;
//		case 2:
//			SellItem(player);
//			break;
//		case 3:
//			std::cout << "다음에 또 오라구!" << std::endl;
//			return;
//		}
//	}
//
//}