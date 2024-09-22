#include "gofish.h"
#include "cards.h"
#include <vector>

GoFish::GoFish(std::vector<Player*> myPlayers) : Game(myPlayers) {

    // Shuffle the cards, and deal each player a hand of 7
    numberOfPlayers=myPlayers.size();
    deck.shuffle();
    for(auto player: myPlayers){
        player->hand = deck.deal(cardsPerPlayer);
        player->enterGame();
    }
}

void GoFish::play() {}

bool GoFish::endCondition(){return numberOfPlayers<2;}