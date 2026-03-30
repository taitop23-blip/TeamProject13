#pragma once
#include <string>
#include <iostream>
#include <vector>

enum class ItemType //아이템 타입
{
    NONE,
    POPPY_PHOTO,
    COFFEE,
    HOTSIX,
    KEYBOARD,
    MOUSE
};

class Item
{
    std::string name;
    ItemType type;
    std::string description;
    int ProgressBonus;

    // [수정/추가사항] 상점 시스템 등에 활용하기 위해 아이템 '가격(price)' 변수 추가
    int price;

    //능력치 추가
    int LifeBonus;
    int MentalRecovery;
    int FocusRecovery;
    int AtkBonus;
    int DefBonus;

public:
    // [수정/추가사항] 매개변수 없이 객체를 생성할 수 있도록 기본 매개변수(ItemType::NONE) 설정
    Item(ItemType t = ItemType::NONE)
    {
        type = t;

        switch (type)
        {
        case ItemType::NONE:
            name = "없음";
            // [수정/추가사항] 각 아이템 케이스마다 가격(price) 초기화 값 적용
            description = "빈 아이템";
            price = 0;
            LifeBonus = 0;
            MentalRecovery = 0;
            FocusRecovery = 0;
            AtkBonus = 0;
            DefBonus = 0;
            break;

        case ItemType::POPPY_PHOTO:
            name = "뽀삐 사진";
            description = "목숨이 하나 늘어난다.";
            price = 700;
            LifeBonus = 1;
            MentalRecovery = 0;
            FocusRecovery = 0;
            AtkBonus = 0;
            DefBonus = 0;
            break;

        case ItemType::COFFEE:
            name = "커피";
            description = "멘탈이 30 회복됩니다.";
            price = 120;
            LifeBonus = 0;
            MentalRecovery = 30;
            FocusRecovery = 0;
            AtkBonus = 0;
            DefBonus = 0;
            break;

        case ItemType::HOTSIX:
            name = "핫식스";
            description = "집중력이 20 회복됩니다.";
            price = 180;
            LifeBonus = 0;
            MentalRecovery = 0;
            FocusRecovery = 20;
            AtkBonus = 0;
            DefBonus = 0;
            break;

        case ItemType::KEYBOARD:
            name = "키보드";
            description = "업무 효율이 대폭 증가한다. (진행도 +25)";
            price = 800;
            LifeBonus = 0;
            MentalRecovery = 0;
            FocusRecovery = 0;
            AtkBonus = 0;
            DefBonus = 0;
            ProgressBonus = 25; // [수정/추가사항] 진행도 대폭 증가
            break;

        case ItemType::MOUSE:
            name = "마우스";
            description = "업무 효율이 소폭 증가한다. (진행도 +10)";
            price = 400;
            LifeBonus = 0;
            MentalRecovery = 0;
            FocusRecovery = 0;
            AtkBonus = 0;
            DefBonus = 0;
            ProgressBonus = 10; // [수정/추가사항] 진행도 소폭 증가
            break;
        }
    }

    ItemType GetType() const
    {
        return type;
    }

    std::string GetName() const
    {
        return name;
    }

    // [수정/추가사항] 외부에서 아이템 정보를 읽어올 수 있도록 각종 Get 함수(Getter) 대거 추가
    std::string GetDescription() const
    {
        return description;
    }

    int GetPrice() const
    {
        return price;
    }

    int GetLifeBonus() const
    {
        return LifeBonus;
    }

    int GetMentalRecovery() const
    {
        return MentalRecovery;
    }

    int GetFocusRecovery() const
    {
        return FocusRecovery;
    }

    int GetAtkBonus() const
    {
        return AtkBonus;
    }

    int GetDefBonus() const
    {
        return DefBonus;
    }

    int GetProgressBonus() const
    {
        return ProgressBonus;
    }
};

class Inventory
{
private:
    std::vector<Item> items;

public:
    // 아이템 추가
    void AddItem(const Item& item)
    {
        items.push_back(item);
        // [수정/추가사항] 아이템을 얻었을 때 어떤 아이템을 획득했는지 화면에 출력하는 안내 문구 추가
        std::cout << item.GetName() << " 획득!\n";
    }

    // 인벤토리 출력
    void ShowInventory()
    {
        std::cout << "\n[ 인벤토리 ]\n";

        // [수정/추가사항] 인벤토리가 비어있을 때 에러가 나지 않도록 예외 처리 로직 추가
        if (items.empty())
        {
            std::cout << "아이템이 없습니다.\n";
            return;
        }

        // [수정/추가사항] 보유 중인 아이템 목록을 보기 좋게 번호, 이름, 설명과 함께 출력하도록 반복문 구현
        for (size_t i = 0; i < items.size(); i++)
        {
            std::cout << i + 1 << ". " << items[i].GetName() << " - "
                      << items[i].GetDescription() << "\n";
        }
    }

    // 아이템 사용
    Item UseItem(int index)
    {
        if (index < 0 || index >= static_cast<int>(items.size()))
        {
            std::cout << "잘못된 선택!\n";
            return Item(ItemType::NONE);
        }

        Item selected = items[index];
        items.erase(items.begin() + index);

        return selected;
    }

    bool IsEmpty()
    {
        return items.empty();
    }
};
