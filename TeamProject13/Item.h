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

	//능력치 추가
	int LifeBonus;
	int MentalRecovery;
	int FocusRecovery;
	int AtkBonus;
	int DefBonus;

public:
	Item(ItemType t)
	{
		type = t;

		switch (type)
		{
		case ItemType::NONE:
			name = "없음";
			description = "빈 아이템";
			LifeBonus = 0;
			MentalRecovery = 0;
			FocusRecovery = 0;
			AtkBonus = 0;
			DefBonus = 0;
			break;
			
		case ItemType::POPPY_PHOTO:
			name = "뽀삐 사진";
			description = "목숨이 하나 늘어난다.";
			LifeBonus = 1;
			MentalRecovery = 0;
			FocusRecovery = 0;
			AtkBonus = 0;
			DefBonus = 0;
			break;

		case ItemType::COFFEE:
			name = "커피";
			description = "멘탈이 증가한다.";
			LifeBonus = 0;
			MentalRecovery = 30;
			FocusRecovery = 0;
			AtkBonus = 0;
			DefBonus = 0;
			break;

		case ItemType::HOTSIX:
			name = "핫식스";
			description = "집중력이 증가한다.";
			LifeBonus = 0;
			MentalRecovery = 0;
			FocusRecovery = 20;
			AtkBonus = 0;
			DefBonus = 0;
			break;

		case ItemType::KEYBOARD:
			name = "키보드";
			description = "공격력이 증가한다.";
			LifeBonus = 0;
			MentalRecovery = 0;
			FocusRecovery = 0;
			AtkBonus = 20;
			DefBonus = 0;
			break;

		case ItemType::MOUSE:
			name = "마우스";
			description = "방어력이 증가한다.";
			LifeBonus = 0;
			MentalRecovery = 0;
			FocusRecovery = 0;
			AtkBonus = 0;
			DefBonus = 10;
			break;
		}
    }
	std::string GetName() const 
	{ 
		return name; 
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
		std::cout << item.GetName() << " 획득!\n";
	}

	// 인벤토리 출력
	void ShowInventory()
	{
		std::cout << "\n[ 인벤토리 ]\n";

		if (items.empty())
		{
			std::cout << "아이템이 없습니다.\n";
			return;
		}

		for (size_t i = 0; i < items.size(); i++)
		{
			std::cout << i + 1 << ". " << items[i].GetName() << "\n";
		}
	}

	// 아이템 사용
	Item UseItem(int index)
	{
		if (index >= static_cast<int>(items.size()))
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