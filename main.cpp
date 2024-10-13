#include "war.h"
#include "gofish.h"
#include <iostream>

/*

"Deal a hand, draw a card"

*/

#define BREAK std::cout << "Break" << std::endl;

int main(){

    Player player1("Jacob");
    Player player2("Lia");
    Player player3("Sam");
    Player player4("Iz");
    std::vector<Player*> players{&player1,&player2,&player3,&player4};
    GoFish myGame(players);
    myGame.play();
    return 0;
}