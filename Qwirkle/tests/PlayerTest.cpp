#include <iostream>
#include "Player.h"

#define  EXIT_SUCCESS      0

using std::cout;
using std::endl;
using std::string;

int main(void)
{
    Player* ben = new Player("Ben");
    std::cout << "Player name is " << ben->getName() << std::endl;
    ben->setScore(20);
    std::cout << "Player score is " << ben->getScore() << std::endl;
    ben->setName("Tom");
    std::cout << "Player name is " << ben->getName() << std::endl;

    Tile* tile1 = new Tile('A',1);
    Tile* tile2 = new Tile('B',2);
    Tile* tile3 = new Tile('C',3);

    ben->getHand().addBack(tile1);
    ben->getHand().addBack(tile2);
    ben->getHand().addBack(tile3);

    // std::cout << ben->getHand().get(1)->getColour() << ben->getHand().get(1)->getShape() << std::endl;
    // std::cout << ben->getHand().get(2)->getColour() << ben->getHand().get(2)->getShape() << std::endl;
    // std::cout << ben->getHand().get(3)->getColour() << ben->getHand().get(3)->getShape() << std::endl;

    ben->getHand().addFront(new Tile('D', 4));
    std::cout << ben->getHand().get(1)->getColour() << ben->getHand().get(1)->getShape() << std::endl;

    ben->printTiles();
    
}