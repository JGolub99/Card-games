#pragma once
#include <vector>

namespace Cards{

enum Suit{Spades=1, Diamonds, Clubs, Hearts};

enum Value{Ace=1,Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King};

static const Suit AllSuits[] = { Spades, Diamonds, Clubs, Hearts };
static const Value AllValues[] = {Ace,Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King};

static const char* rank_txt[] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" } ;
static const char* suit_txt[] = {"Spades", "Diamonds", "Clubs", "Hearts"} ;

class Card {

public:
    const Suit suit;
    const Value value;
    void show() const;

private:

    friend class Deck;
    friend class Hand;

    Card(Suit, Value);
    Card(Value, Suit);
    ~Card();

};

class Deck; //Forward declaration

class Hand {
public:

    void add(Deck&, bool random = false); // Add a card to the hand from the top of the deck or randomly
    void add(Deck&, Value, Suit); // Add a specific card from the deck (if it is in the deck)
    void discard(Deck&, bool random = false);
    void discard(Deck&, Value, Suit);
    void discardAll(Deck&);

    void show();
    
private:
    friend class Deck;
    friend void Give(Hand&, Hand&, Value, Suit);
    friend void Give(Hand&, Hand&);
    friend void GiveRandom(Hand&, Hand&);
    friend Hand operator+(Cards::Hand&, Cards::Hand&);

    void add(Card*);
    
    std::vector<Card*> cards;
    int numberOfCards = 0;
};

class Deck {
public:
    Deck(bool shuffled = false, bool empty = false);
    ~Deck();
    void shuffle();
    void show(bool reverse = false);
    void top(int);
    void bottom(int);
    Hand deal(int); // Deal a hand of specified size
    Hand deal(Suit); // Deal a hand of one suit
    Hand deal(Value); // Deal a hand of one value
    Hand deal(Value,Suit); // Deal a hand of just one card

private:

    friend class Hand;

    std::vector<Card*> cards;
    int numberOfCards = 0;
    static const int length = 51;

    Card* draw(bool random = false); // Draw a card from the top of the deck, or one at random
    Card* draw(Value,Suit); //For drawing a specific card
    
    void add(Card*); // For adding a card pointer to the deck 
};

void Give(Hand&, Hand&, Value, Suit);
void Give(Hand&, Hand&); // Top card
void GiveRandom(Hand&, Hand&);

Hand operator+(Hand&, Hand&);
}