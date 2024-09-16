#include "war.h"

War::War(std::vector<Player*> myPlayers) : Game(myPlayers) {};

void War::play() {};

bool War::endCondition() {return true;};