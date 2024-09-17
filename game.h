#pragma once
#include <vector>
#include <string>
#include "cards.h"


class Player{
public:
    std::string name;
    Cards::Hand hand;

    Player(std::string,int startingPoints=0);
    void addPoints(int);
    void deductPoints(int);
    void leaveGame();
    void enterGame();
    void showHand() const;

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