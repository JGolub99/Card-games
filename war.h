#pragma once
#include "game.h"

class War : Game {
public:
    War(std::vector<Player*>);
    void play();

private:
    bool endCondition();
};