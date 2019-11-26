#include <iostream>
#include <string>
#include "LinkedList.h"

class Player{

public: 

    Player(std::string name);
    Player(std::string name, int score, LinkedList* hand);
    Player(Player& other);
    ~Player();
    std::string getName();
    int getScore();
    void setScore(int score);
    void setName(std::string name);
    LinkedList* getHand();
    void printTiles();
    void printList();

private:

    LinkedList hand;
    std::string name;
    int score;

};

