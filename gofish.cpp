#include "gofish.h"
#include "cards.h"
#include <iostream>
#include <vector>

#define DEBUG

GoFish::GoFish(std::vector<Player*> myPlayers) : Game(myPlayers) {

    // Shuffle the cards, and deal each player a hand of 7
    numberOfPlayers=myPlayers.size();
    deck.shuffle();
    for(auto player: myPlayers){
        player->hand = deck.deal(cardsPerPlayer);
        player->enterGame();
    }
}

void GoFish::play() {
    while(!endCondition()){
        #ifdef DEBUG
        std::cout << "Playing" << std::endl;
        std::cin.get();
        #endif
        playround();
    }
    declareWinner();
}

void GoFish::playround() {
    for(auto player : players){
        if(player->playing()){
            std::cout << player->name << ": " << std::endl;
            player->showHand();
            std::cout << std::endl;
            battle(player); // choose an opponent, and take their cards or go fish. Update opponent.
            discardSets(player); // discard any sets to the pile, and add points
            updatePlayerStatus(player); // if player is out of cards and deck is empty, leave game
        }
    }
}

void GoFish::battle(Player* myPlayer){

}

void GoFish::discardSets(Player* myPlayer){

}

void GoFish::updatePlayerStatus(Player* myPlayer){

}

void GoFish::declareWinner(){

}

bool GoFish::endCondition() {
    return pile.getNumberOfCards() == Cards::Deck::length;
}