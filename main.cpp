#include "cards.h"
#include <iostream>

/*

"Deal a hand, draw a card"

*/

#define BREAK std::cout << "Break" << std::endl;

int main(){

    Cards::Deck myDeck(false);
    Cards::Hand myHand1 = myDeck.deal(4);
    Cards::Hand myHand2 = myDeck.deal(5);
    myHand1.show();
    myHand2.show();
    BREAK;
    Cards::Hand myHand3 = myHand1 + myHand2;
    myHand3.show();
    BREAK;
    myHand1.add(myDeck);
    myHand1.show();
    myHand2.show();
    BREAK;
    myDeck.show();
    return 0;
}