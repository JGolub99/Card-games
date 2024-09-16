#include "cards.h"
#include "game.h"
#include "war.h"
#include <iostream>

/*

"Deal a hand, draw a card"

*/

#define BREAK std::cout << "Break" << std::endl;

int main(){

    Player player1("Jacob");
    Player player2("Lia");
    std::vector<Player*> players{&player1,&player2};
    War myGame(players);
    return 0;
}