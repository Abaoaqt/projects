#include "Player.h"

Player::Player(std::string name) {
    this->name = name;
    this->score = 0;
    LinkedList hand;
}
// for loading data from a saved game
Player::Player(std::string name, int score, LinkedList* hand){
	this->name = name;
	this->score = score;
	this->hand = *hand;
}

Player::~Player() {
    hand.clear();
}

std::string Player::getName() {
    return name;
}

int Player::getScore() {
    return score;
}

LinkedList* Player::getHand() {
    return &hand;
}

void Player::setScore(int score) {
    this->score = score;
}

void Player::setName(std::string name) {
    this->name = name;
}

void Player::printList() 
{   
    Node* node = getHand()->getHead();
    while (node != NULL) 
    { 
        std::cout << node->tile->getColour() << node->tile->getShape() << " ";
        node = node->next; 
    } 
} 


