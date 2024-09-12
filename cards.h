#pragma once
#include <vector>
#include <memory>

namespace Cards{

enum Suit{Spades=1, Diamonds, Clubs, Hearts};

enum Value{Ace=1,Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King};

static const Suit AllSuits[] = { Spades, Diamonds, Clubs, Hearts };
static const Value AllValues[] = {Ace,Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King};

static const char* rank_txt[] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" } ;
static const char* suit_txt[] = {"Spades", "Diamonds", "Clubs", "Hearts"} ;

class Card {

private:

    friend class Deck;

    Card(Suit, Value);
    Card(Value, Suit);
    ~Card();
    void show();

    Suit suit;
    Value value;

};

class Deck {
public:
    Deck(bool shuffled = false);
    ~Deck();
    void shuffle();
    void top(int);
    void bottom(int);

private:
    std::vector<Card*> cards;
    static const int length = 51;
};
}