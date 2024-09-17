#include "game.h"
#include <string>

Player::Player(std::string myName, int startingPoints){
    name = myName;
    points = startingPoints;
}

void Player::addPoints(int number){
    points+=points;
}

void Player::deductPoints(int number){
    points-=number;
}

void Player::enterGame(){
    inGame = true;
}

void Player::leaveGame(){
    inGame = false;
}

void Player::showHand() const {
    hand.show();
}

Game::Game(std::vector<Player*> myPlayers){
    for(const auto player: myPlayers){;
        this->addPlayer(player);
    }
}

void Game::addPlayer(Player* myPlayer){
    players.push_back(myPlayer);
    numberOfPlayers++;
}
