#pragma once

class Player;

class EventManager {
public:
    void ShowBonusMenu(Player& p);
    void TriggerRandomEvent(Player& p, int& dangerLevel);

private:
    void ApplyBonus(Player& p, int choice);
};
