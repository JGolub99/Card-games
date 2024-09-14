#include "cards.h"
#include <iostream>
#include <random> 
#include <algorithm> 
#include <stdexcept>

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
            numberOfCards+=1;
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

void Cards::Deck::show(bool reverse){
    if(reverse){
        for (int i = numberOfCards - 1; i >= 0; --i) {
            cards[i]->show();
        }
    }
    else{
        for(const auto card : cards){
            card->show();
        }
    }
}

void Cards::Deck::top(int number){
    if(number>numberOfCards){
        this->show();
    }
    else{
        for(int i = 0; i < number; i++){
            cards[i]->show();
        }
    }
}

void Cards::Deck::bottom(int number){

    if(number>numberOfCards){
        this->show(true);
    }
    else{
        int j = 0;
        for(int i = length; j<number; i--){
            cards[i]->show();
            j++;
        }
    }
}

// Implement the shuffle function:

void Cards::Deck::shuffle(){
    std::random_device rd; 
    std::mt19937 g(rd()); 

    std::shuffle(cards.begin(), cards.end(), g); 
}


Cards::Card* Cards::Deck::draw(bool random){
    int index = 0;
    if(random){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,numberOfCards-1);
        index = dist6(rng);
    }
    Card* pCar = cards[index];
    cards.erase(cards.begin()+index);
    numberOfCards--;
    return pCar;
}

Cards::Card* Cards::Deck::draw(Value myValue, Suit mySuit){
    for (const auto cardP : cards){
        if((*cardP).suit == mySuit && (*cardP).value == myValue){
            // erase card from deck

            auto it = std::find(cards.begin(), cards.end(), cardP);
            cards.erase(it);

            numberOfCards--;
            return cardP;
        }
    }
    throw std::runtime_error("Requested card is not in the deck.");
}


Cards::Hand Cards::Deck::deal(int mynumber){
    Cards::Hand hand;
    for(int i=0;i<mynumber;i++){
        Card* drawnCard = this->draw();
        hand.add(drawnCard);
    }
    return hand;
}

Cards::Hand Cards::Deck::deal(Suit mySuit){
    Cards::Hand hand;
    for(const auto myValue : AllValues){
        Card* drawnCard = this->draw(myValue,mySuit);
        hand.add(drawnCard);
    }
    return hand;
}

Cards::Hand Cards::Deck::deal(Value myValue){
    Cards::Hand hand;
    for(const auto mySuit : AllSuits){
        Card* drawnCard = this->draw(myValue,mySuit);
        hand.add(drawnCard);
    }
    return hand;
}

Cards::Hand Cards::Deck::deal(Value myValue, Suit mySuit){
    Cards::Hand hand;
    Card* drawnCard = this->draw(myValue,mySuit);
    hand.add(drawnCard);
    return hand;
}

// HAND


void Cards::Hand::add(Card* card){
    cards.push_back(card);
    numberOfCards+=1;
}

void Cards::Hand::add(Deck& myDeck, bool random){
    Card* drawnCard = myDeck.draw(random);
    cards.push_back(drawnCard);
    numberOfCards+=1;
}

void Cards::Hand::add(Deck& myDeck, Value myValue, Suit mySuit){
    Card* drawnCard = myDeck.draw(myValue, mySuit);
    cards.push_back(drawnCard);
    numberOfCards+=1;
}

void Cards::Hand::show(){
    for(auto card : cards){
        card->show();
    }
}