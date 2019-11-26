#include <iostream>
#include "Board.h"
#include "LinkedList.h"
#include "AI.h"

#define  EXIT_SUCCESS      0

using std::cout;
using std::endl;
using std::string;

int main(void)
{
	
    Board* board = new Board(5,5, true);
        
    Player* player = new Player("test");
    LinkedList* hand = new LinkedList();
    Tile* test = new Tile(RED,CIRCLE);
    Tile* test2 = new Tile(BLUE,CIRCLE);
    Tile* test7 = new Tile(RED,STAR_4);

    board->putTile(player,test,2,2);
    board->printBoard();
    std::cout<<std::endl;

    hand->addFront(test2);
    hand->addFront(test7);

    struct Move move = marvinMove(board, hand);

    board->putTile(player, move.tile, move.xCoord, move.yCoord);
    
    board->printBoard();
    // board->printTiles();
    return EXIT_SUCCESS;
}

