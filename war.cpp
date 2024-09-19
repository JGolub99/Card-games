#include "war.h"
#include "cards.h"
#include <cmath>
#include <vector>
#include <iostream>

War::War(std::vector<Player*> myPlayers) : Game(myPlayers) {

    // Shuffle the cards, and deal each player a hand of equal size

    numberOfPlayers=myPlayers.size();
    deck.shuffle();
    int cardsPerPlayer = std::floor((Cards::Deck::length + 1)/numberOfPlayers);
    for(auto player: myPlayers){
        player->hand = deck.deal(cardsPerPlayer);
        player->enterGame();
    }

};

void War::play() {
    while(!endCondition()){
        playround();
        updatePlayerStatus();
    }
};

// This function returns the player who has the higher first card in their hand
Player* War::battle(Player* player1, Player* player2){
    // If the cards have the same value:
    if((player1->hand).top()->value == (player2->hand).top()->value){
        // If a draw is not possible
        if(player1->hand.getNumberOfCards() == 1 && player2->hand.getNumberOfCards() == 1){
            if((player1->hand).top()->suit > (player2->hand).top()->suit){
                player2->leaveGame();
                return player1;                 
            }
            else{
                player1->leaveGame();
                return player2;      
            }
        }
        else if(player1->hand.getNumberOfCards() == 1){
            player1->leaveGame();
            return player2;
        }
        else if(player2->hand.getNumberOfCards() == 1){
            player2->leaveGame();
            return player1;   
        }
        else{
            return nullptr; // Reflects a draw
        }
    }

    else if((player1->hand).top()->value == Cards::Ace){
        player2->leaveGame();
        return player1;
    }
    else if((player2->hand).top()->value == Cards::Ace){
        player1->leaveGame();
        return player2;
    }
    else if((player1->hand).top()->value > (player2->hand).top()->value){
        player2->leaveGame();
        return player1;
    }
    else{
        player1->leaveGame();
        return player2;
    }
}

void War::playround() {
    // First, get a list of players in the round
    std::vector<Player*> playersInRound;
    for(auto const player : players){
        if(player->playing()){
            std::cout << player->name << ": ";
            (player->hand).top()->show();
            std::cout << (player->hand).getNumberOfCards() << " cards" << std::endl;
            playersInRound.push_back(player);
        }
    }

    std::cin.get();
    
    Player* winner = playersInRound[0];
    Player* tempWinner;
    std::vector<Player*> subPlayers(playersInRound.begin() + 1, playersInRound.end()); 
    bool draw = false;

    // Then, battle each player against each other, and determine the winner or if it is a draw

    for(auto player : subPlayers){
        tempWinner = battle(winner,player);
        if(!tempWinner){
            draw = true;
        }
        else if(tempWinner!=winner){ // New challenger wins the battle
            draw = false;
            winner = tempWinner;
        }
    }

    // If it is a draw, add top card from each player to pile and play another round between the winners.

    if(draw){
        std::cout << "Draw!" << std::endl;
        std::cout << std::endl;
        for(auto player : playersInRound){
            (player->hand).discard(pile);
        }
        playround();
    }

    // If it is not a draw, transfer all top cards to winners pile (to the bottom)

    else{
        std::cout << winner->name << " wins the round!" << std::endl;
        std::cout << std::endl;
        for(auto player : playersInRound){
            if(!(player==winner)){
                Cards::Give(player->hand,winner->hand);
            }
        }
        // Now add any cards that might be in pile from previous round(s)
        Cards::Hand extraCards = pile.dealAll();
        winner->hand = winner->hand + extraCards;

        // Finally, move winning card from winner to the back of their hand
        (winner->hand).topToBottom();
        // FINISH THIS
    }
}

void War::updatePlayerStatus() {
    numberOfPlayers = 0;
    for(auto const player : players){
        if((player->hand).getNumberOfCards() == 0){
            player->leaveGame();
        }
        else{
            player->enterGame();
            numberOfPlayers++;
        }
    }
}

bool War::endCondition() {return numberOfPlayers<2;};