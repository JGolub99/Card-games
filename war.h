#pragma once
#include "game.h"
#include "cards.h"

class War : public Game
{
public:
    War(std::vector<Player*>);
    void play();

private:
    bool endCondition();
    void playround();
    void updatePlayerStatus();
    Player* battle(Player*, Player*);
    Cards::Deck pile = Cards::Deck(false,true);
};