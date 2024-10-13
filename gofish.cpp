#include "gofish.h"
#include "cards.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>


GoFish::GoFish(std::vector<Player*> myPlayers) : Game(myPlayers) {

    // Shuffle the cards, and deal each player a hand of 7
    numberOfPlayers=myPlayers.size();
    deck.shuffle();
    for(auto player: myPlayers){
        player->hand = deck.deal(cardsPerPlayer);
        (player->hand).orderByValue();
        player->enterGame();
        // Discard any initial sets
        for(auto const value : Cards::AllValues){
            discardSets(player,value);
        }
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
            battle(player); // choose an opponent, and take their cards or go fish. Update opponent. Discard sets and add points. Update player.
        }
    }
}

void GoFish::battle(Player* myPlayer){
    std::cout << myPlayer->name << "'s turn (" << myPlayer->showPoints() << " points): " << std::endl;
    myPlayer->showHand();
    std::cout << std::endl;

    std::string input_name;
    char input_value_string[20];
    std::cin >> input_name >> input_value_string;
    
    // Catch value typos:

    bool found = false;
    
    // Loop over the rank_txt array
    for (int i = 0; i < 13; ++i) {
        if (std::strcmp(input_value_string, Cards::rank_txt[i]) == 0) {
            found = true;
            break;
        }
    }

    if(!found){
        std::cout << "That is not a valid card type." << std::endl;
        std::cout << std::endl;
        return battle(myPlayer);
    }

    Cards::Value input_value = Cards::convertValue(input_value_string);

    // Make sure that player has the requested card type:

    found = false;

    for(auto const card : (myPlayer->hand).getHand()){
        if(card->value == input_value){
            found = true;
            break;
        }
    }

    if(!found){
        std::cout << "You cannot request that card type." << std::endl;
        std::cout << std::endl;
        return battle(myPlayer);
    }

    bool playerExists = false;
    bool playerHasValue = false;
    bool drewRequestedValue = false;

    for(auto player : players){
        if(player->name == input_name){
            playerExists = true;
            for(auto const card : (player->hand).getHand()){
                if(card->value == input_value){
                    std::cout << "Yeah boi" << std::endl << std::endl;
                    playerHasValue = true;
                    Cards::Give(player->hand,myPlayer->hand,input_value);
                    discardSets(myPlayer,input_value);
                    updatePlayerStatus(myPlayer);

                    // Update opponent
                    updatePlayerStatus(player);

                    break;
                }
            }
            if(!playerHasValue){
                std::cout << "Go fish, bitch!" << std::endl << std::endl;
                if(deck.getNumberOfCards() > 0){  // Can only draw a card if the deck is not empty
                    Cards::Hand newHand = deck.deal(1);
                    if(newHand.top()->value == input_value){
                        drewRequestedValue = true;
                    }
                    myPlayer->hand = myPlayer->hand + newHand;
                    discardSets(myPlayer,newHand.top()->value);
                    updatePlayerStatus(myPlayer);
                }
            }
            break;
        }
    }

    // Implement check for typos.
    if(!playerExists){
        std::cout << "That player is not in the game!" << std::endl;
        std::cout << std::endl;
        battle(myPlayer);
    }

    // Reorder cards
    (myPlayer->hand).orderByValue();

    // If the player won the battle or they drew the desired card from the deck, then they get to play again.
    if((playerHasValue||drewRequestedValue)&&myPlayer->playing()){
        battle(myPlayer);
    }
}

void GoFish::discardSets(Player* myPlayer, Cards::Value myValue){

    int valueCount = 0;
    for(auto const card : (myPlayer->hand).getHand()){

        if(card->value == myValue){
            valueCount++;
        }
        if(valueCount == 4){
            (myPlayer->hand).discard(pile,myValue,Cards::Spades);
            (myPlayer->hand).discard(pile,myValue,Cards::Diamonds);
            (myPlayer->hand).discard(pile,myValue,Cards::Clubs);
            (myPlayer->hand).discard(pile,myValue,Cards::Hearts);
            myPlayer->addPoints(1);
            break;
        }

    }
    
}

void GoFish::updatePlayerStatus(Player* myPlayer){
    if((myPlayer->hand).getNumberOfCards() == 0){
        if(deck.getNumberOfCards()>0){
            (myPlayer->hand).add(deck);
        }
        else{
            myPlayer->leaveGame();
        }
    }
}

void GoFish::declareWinner(){

    std::vector<Player*> winners;
    int maxPoints = 0;

    for(auto const player : players){
        int points = player->showPoints();
        std::cout << player->name << ": " << points << " points" << std::endl;
        if(points > maxPoints){
            maxPoints = points;

            winners.clear();
            winners.push_back(player);
        }
        else if(points == maxPoints){

            winners.push_back(player);
        }
    }


    std::cout << std::endl;
    for(auto const winner : winners){
        std::cout << winner->name << " wins!" << std::endl;
    }
}

bool GoFish::endCondition() {
    return pile.getNumberOfCards() == Cards::Deck::length + 1;
}