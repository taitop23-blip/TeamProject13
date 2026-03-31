#pragma once

class Player;

class EventManager {
public:
    void ShowBonusMenu(Player& p);
    bool TriggerRandomEvent(Player& p, int& dangerLevel);

private:
    void ApplyBonus(Player& p, int choice);
};
