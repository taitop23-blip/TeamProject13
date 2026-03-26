// WorldManager.h

#pragma once

class Player;
class WorldManager
{
private:
    int dangerLevel;
    const int maxProgress = 100;
    bool isFinalBossAppeared = false;

public:
    WorldManager() : dangerLevel(0), isFinalBossAppeared(false) {}

    // ¾÷¹« ÁýÁß (ÁøÇàµµ¡è, ¸àÅ»¡é, À§Çèµµ¡è)
    void FocusWork(Player& p);

    // Ä¿ÇÇ ÃæÀü (ÁýÁß·Â¡è, ¸àÅ» ¼ÒÆø¡é)
    void DrinkCoffee(Player& p);

    // À¯Æ©ºê º¸±â (ÁøÇàµµ¡é, ¸àÅ»¡è, À§Çèµµ¡è)
    void WatchYoutube(Player& p);

    // ¸ô·¡ ½ºÆ®·¹Äª (¸àÅ» ¼ÒÆø¡è, ÁýÁß·Â ¼ÒÆø¡è)
    void Stretching(Player& p);

    // À§Çèµµ Ã¼Å© ¹× ºô·± ¼ÒÈ¯ ÆÇ´Ü
    bool CheckEncounter();

    void ResetDanger() { dangerLevel = 0; }
    int GetDanger() const { return dangerLevel; }

    // ÁøÇàµµ 100% Ã¼Å© ¹× ÃÖÁ¾ º¸½º Æ®¸®°Å
    bool IsReadyForFinalBoss(int currentProgress) {
        if (currentProgress >= maxProgress && !isFinalBossAppeared) {
            isFinalBossAppeared = true;
            return true;
        }
        return false;
    }

    void ResetFinalBoss() { isFinalBossAppeared = false; }
};

