#pragma once
#include "game.h"


class GoFish : public Game {
public:
    GoFish(std::vector<Player*>);
    void play();

private:
   bool endCondition();

   static const int cardsPerPlayer = 7;
};