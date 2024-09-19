#pragma once
#include <vector>
#include <string>
#include "cards.h"


class Player{
public:

    Player(std::string,int startingPoints=0);
    void addPoints(int);
    void deductPoints(int);
    void leaveGame();
    void enterGame();
    bool playing() const;
    void showHand() const;

    std::string name;
    Cards::Hand hand;

private:
    int points = 0;
    bool inGame = false;

};


class Game{
public:
    Cards::Deck deck;
    std::vector<Player*> players;

    Game(std::vector<Player*>);
    virtual void play() = 0;

protected:
    int numberOfPlayers = 0;

    void addPlayer(Player*);
    virtual bool endCondition() = 0;
};