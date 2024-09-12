#include "cards.h"
#include <iostream>




int main(){

    Cards::Deck myDeck(false);
    Cards::Hand myHand = myDeck.deal(5);
    myHand.add(myDeck);
    myHand.show();
    myDeck.shuffle();
    myDeck.top(5);
    return 0;
}