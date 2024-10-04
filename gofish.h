#pragma once
#include "game.h"


class GoFish : public Game {
public:
    GoFish(std::vector<Player*>);
    void play();

private:
    void playround();
    void battle(Player*);
    void discardSets(Player*,Cards::Value);
    void updatePlayerStatus(Player*);
    void declareWinner();
    bool endCondition();

    Cards::Deck pile = Cards::Deck(false,true);

    static const int cardsPerPlayer = 7;
};