#include <iostream>
#include <vector>
#include "ShopManager.h"
#include "Utils.h"

// [수정/추가사항 1] 주석 처리되어 있던 생성자를 활성화하고, ItemType 열거형을 사용해 상점 판매 물품을 초기화하도록 수정
ShopManager::ShopManager() {
    shopInventory.push_back(Item(ItemType::COFFEE));
    shopInventory.push_back(Item(ItemType::HOTSIX));
    shopInventory.push_back(Item(ItemType::KEYBOARD));
    shopInventory.push_back(Item(ItemType::MOUSE));
    shopInventory.push_back(Item(ItemType::POPPY_PHOTO));
}

// [수정/추가사항 2] 복잡했던 iterator 대신 직관적인 for문과 size_t를 사용하여 상점 물품 목록 출력 로직 개선
void ShopManager::DisplayItems() {
    Utils::PrintLine('=');
    std::cout << "여어~ 요즘 일은 어때?\n\n";

    for (std::size_t i = 0; i < shopInventory.size(); ++i) {
        const Item& item = shopInventory[i];
        // [수정/추가사항 3] Item 클래스에 새로 추가된 GetName, GetPrice, GetDescription 함수를 활용해 상세 정보 출력
        std::cout << i + 1 << ": " << item.GetName()
            << " | 가격: " << item.GetPrice() << "G"
            << " | " << item.GetDescription() << "\n";
    }
    Utils::PrintLine('=');
}

// [수정/추가사항 4] 구매 로직 전면 재구현: 예외 처리 및 플레이어 골드 연동
void ShopManager::BuyItem(Player& player) {
    std::cout << "오늘은 뭘 사가려나?\n";
    // Utils::GetInput을 사용하여 문자 입력 등 잘못된 입력에 대한 에러 방지
    int select = Utils::GetInput(0, static_cast<int>(shopInventory.size()), "구매할 상품 번호(0: 이전): ");

    if (select == 0) {
        return;
    }

    // 입력받은 번호를 인덱스로 변환 (입력값 - 1)
    const Item& selectedItem = shopInventory[static_cast<std::size_t>(select - 1)];
    // [수정/추가사항 5] 플레이어의 현재 골드(GetGold)와 아이템 가격(GetPrice)을 비교하여 구매 가능 여부 판별
    if (!player.SpendGold(selectedItem.GetPrice())) {
        std::cout << "돈이 모자란 것 같은데?\n\n";
        return;
    }

    // [수정/추가사항 6] 구매 성공 시 플레이어의 골드를 차감하고(SubGold), 인벤토리에 아이템 추가(AddItem)
    player.AddItem(selectedItem);
    std::cout << selectedItem.GetPrice() << "G를 지불했습니다.\n";
    std::cout << "매번 고마워. 쉬엄쉬엄하라구.\n\n";
}

// [수정/추가사항 7] 판매 로직 전면 재구현: 플레이어 인벤토리 연동 및 판매가 계산 로직 추가
void ShopManager::SellItem(Player& player) {
    // 플레이어 인벤토리가 비어있는지 확인 (HasItems 함수가 Player 클래스에 추가되어 있어야 함)
    if (!player.HasItems()) {
        std::cout << "팔 물건이 없는데? 다음에 또 오라구.\n";
        return;
    }

    std::cout << "무슨 물건을 팔려고?\n";
    player.PrintInventory();

    const int maxChoice = static_cast<int>(player.GetInventory().size());
    int select = Utils::GetInput(0, maxChoice, "판매할 아이템 번호(0: 이전): ");
    if (select == 0) {
        return;
    }

    // [수정/추가사항 8] 플레이어 인벤토리에서 아이템 포인터를 가져와 유효성 검사
    const Item* selectedItem = player.GetItem(static_cast<std::size_t>(select - 1));
    if (!selectedItem) {
        std::cout << "그런 물건은 없다고.\n";
        return;
    }

    // [수정/추가사항 9] 판매 가격 책정 로직: 원가의 절반(50%) 가격으로 판매하며, 최소 1G 보장
    const int sellPrice = std::max(1, selectedItem->GetPrice() / 2);
    std::cout << selectedItem->GetName() << "을(를) " << sellPrice << "G에 판매했습니다.\n";
    // [수정/추가사항 10] 판매 완료 후 플레이어에게 골드 지급 및 인벤토리에서 아이템 삭제
    player.AddGold(sellPrice);
    player.RemoveItem(static_cast<std::size_t>(select - 1));
}

void ShopManager::ShopConsole(Player& player) {
    while (1) {
        std::cout << "\n[현재 골드] " << player.GetGold() << "G\n";
        DisplayItems();
        std::cout << "1) 물건을 산다. 2) 물건을 판다. 3) 떠난다.\n";
        int select = Utils::GetInput(1, 3, "번호 선택: ");

        switch (select) {
        case 1: BuyItem(player); break;
        case 2: SellItem(player); break;
        case 3:
            std::cout << "다음에 또 오라구!\n";
            return;
        }
    }
}
