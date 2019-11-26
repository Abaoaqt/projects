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
    Tile* test3 = new Tile(GREEN,CIRCLE);  // SQUARE
    Tile* test4 = new Tile(YELLOW,CIRCLE); // STAR_4
    Tile* test5 = new Tile(YELLOW,STAR_4); 
	Tile* test6 = new Tile(GREEN, STAR_4);

    board->putTile(player,test,2,2);
    board->printBoard();
    std::cout<<std::endl;

    hand->addFront(test2);
    hand->addFront(test3);
    hand->addFront(test4);
	hand->addFront(test5);
    hand->addFront(test6);

    struct Move move = marvinMove(board, hand);

    board->putTile(player, move.tile, move.xCoord, move.yCoord);
    board->printBoard();
    std::cout<<std::endl;

    move = marvinMove(board, hand);

    board->putTile(player, move.tile, move.xCoord, move.yCoord);
    board->printBoard();
    std::cout<<std::endl;

    move = marvinMove(board, hand);

    board->putTile(player, move.tile, move.xCoord, move.yCoord);
    board->printBoard();
    std::cout<<std::endl;

    move = marvinMove(board, hand);

    board->putTile(player, move.tile, move.xCoord, move.yCoord);
    board->printBoard();
    std::cout<<std::endl;

    move = marvinMove(board, hand);

    board->putTile(player, move.tile, move.xCoord, move.yCoord);
    board->printBoard();
    std::cout<<std::endl;
    // board->printTiles();
    return EXIT_SUCCESS;
}

