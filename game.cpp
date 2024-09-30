#include "game.h"
#include <string>
#include <algorithm>
#include <stdexcept>

Player::Player(std::string myName, int startingPoints){
    name = myName;
    points = startingPoints;
}

void Player::addPoints(int number){
    points+=number;
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

bool Player::playing() const {
    return inGame;
}

void Player::showHand() const {
    hand.show();
}

int Player::showPoints() const {
    return points;
}

Game::Game(std::vector<Player*> myPlayers){
    for(const auto player: myPlayers){
        int cnt = std::count(players.begin(), players.end(), player); 
        if(cnt==0){
            this->addPlayer(player);
        }
        else{
            throw std::runtime_error("Player cannot be registered in a game twice.");
        }
    }
}

void Game::addPlayer(Player* myPlayer){
    players.push_back(myPlayer);
    numberOfPlayers++;
}
