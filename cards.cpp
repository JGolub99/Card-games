#include "cards.h"
#include <iostream>
#include <memory>
#include <random> 
#include <algorithm> 

// #define DEBUG

// CARD

// Implement the constructors:
Cards::Card::Card(Suit mysuit, Value myvalue) : suit(mysuit), value(myvalue) {
    #ifdef DEBUG
    std::cout << "Constructed" << std::endl;
    #endif
}

Cards::Card::Card(Value myvalue, Suit mysuit) : suit(mysuit), value(myvalue) {
    #ifdef DEBUG
    std::cout << "Constructed" << std::endl;
    #endif
}

Cards::Card::~Card() {
    #ifdef DEBUG
    std::cout << "Destructed" << std::endl;
    #endif
}


// Implement the show card function:
void Cards::Card::show(){

    std::cout << rank_txt[value-1] << " of " << suit_txt[suit-1] << std::endl;
}


// DECK

// Implement the constructor:

Cards::Deck::Deck(bool shuffled) {
    for(const auto my_suit : AllSuits){
        for(const auto my_value : AllValues){
            Card* pCard = new Card(my_value,my_suit);
            cards.push_back(pCard);
        }
    }
    if(shuffled){
        this->shuffle();
    }
}

Cards::Deck::~Deck() {
    for (auto p : cards){
        delete p;
    }
}

// Implement the show functions:

void Cards::Deck::top(int number){
    for(int i = 0; i < number; i++){
        cards[i]->show();
    }
}

void Cards::Deck::bottom(int number){
    int j = 0;
    for(int i = length; j<number; i--){
        cards[i]->show();
        j++;
    }
}

// Implement the shuffle function:

void Cards::Deck::shuffle(){
    std::random_device rd; 
    std::mt19937 g(rd()); 

    std::shuffle(cards.begin(), cards.end(), g); 
}