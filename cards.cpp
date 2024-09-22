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
void Cards::Card::show() const {

    std::cout << rank_txt[value-1] << " of " << suit_txt[suit-1] << std::endl;
}


// DECK

// Implement the constructor:

Cards::Deck::Deck(bool shuffled, bool empty) {
    if(!empty){
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

int Cards::Deck::getNumberOfCards() const {
    return numberOfCards;
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

void Cards::Deck::add(Card* myCard){
    if(numberOfCards==length){
        throw std::runtime_error("Deck is full.");
    }
    cards.push_back(myCard);
    numberOfCards++;
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

Cards::Hand Cards::Deck::dealAll(){
    return deal(numberOfCards);
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


void Cards::Hand::discard(Deck& myDeck, bool random){
    if(!random){
        myDeck.add(cards[0]);
        cards.erase(cards.begin());
    }
    else{
        int index;
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,numberOfCards-1);
        index = dist6(rng);
        myDeck.add(cards[index]);
        auto it = std::find(cards.begin(), cards.end(), cards[index]);
        cards.erase(it);
    }
    numberOfCards--;
}

void Cards::Hand::discard(Deck& myDeck, Value myValue, Suit mySuit){
    for(const auto cardP : cards){
        if((*cardP).value == myValue && (*cardP).suit == mySuit){
            myDeck.add(cardP);
            auto it = std::find(cards.begin(), cards.end(), cardP);
            cards.erase(it);
            numberOfCards--;
            return;
        }
    }
}

void Cards::Hand::discardAll(Deck& myDeck){
    int count = numberOfCards;
    for(int i=0; i<count; i++){
        this->discard(myDeck);
    }
}

void Cards::Hand::topToBottom(){
    Card* frontCard = cards.front();
    cards.erase(cards.begin());
    cards.push_back(frontCard);
}

void Cards::Hand::show() const {
    for(auto card : cards){
        card->show();
    }
}

Cards::Card* Cards::Hand::top() const {
    return this->cards[0];
}

int Cards::Hand::getNumberOfCards() const {
    return numberOfCards;
}

// Implement Give functionality

void Cards::Give(Hand& hand1, Hand& hand2, Cards::Value myValue, Cards::Suit mySuit){
    for(const auto cardP : hand1.cards){
        if((*cardP).value == myValue && (*cardP).suit == mySuit){
            hand2.add(cardP);
            auto it = std::find(hand1.cards.begin(), hand1.cards.end(), cardP);
            hand1.cards.erase(it);
            hand1.numberOfCards--;
            return;
        }
    }

    std::cout << "Card not found!" << std::endl;
}

void Cards::Give(Hand& hand1, Hand& hand2){
    if(hand1.numberOfCards == 0){
        throw std::runtime_error("Hand is empty.");
    }
    hand2.add(hand1.cards[0]);
    hand1.cards.erase(hand1.cards.begin());
    hand1.numberOfCards--;
}

void Cards::GiveRandom(Hand& hand1, Hand& hand2){
    if(hand1.numberOfCards == 0){
        throw std::runtime_error("Hand is empty.");
    }
    int index;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,hand1.numberOfCards-1);
    index = dist6(rng);
    hand2.add(hand1.cards[index]);
    auto it = std::find(hand1.cards.begin(), hand1.cards.end(), hand1.cards[index]);
    hand1.cards.erase(it);
    hand1.numberOfCards--;
}

// Implement functionality for combining hands

Cards::Hand Cards::operator+(Cards::Hand& hand1, Cards::Hand& hand2){
    Cards::Hand newHand;
    int numCards1 = hand1.numberOfCards;
    int numCards2 = hand2.numberOfCards;

    for(int i = 0; i<numCards1; i++){
        Cards::Give(hand1,newHand);
    }
    for(int j = 0; j<numCards2; j++){
        Cards::Give(hand2,newHand);
    }  
    return newHand;
}