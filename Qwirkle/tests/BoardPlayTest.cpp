#include <iostream>
#include "Board.h"
#include "LinkedList.h"

#define  EXIT_SUCCESS      0

using std::cout;
using std::endl;
using std::string;

int main(void)
{
	
    Board* board = new Board(5,5, true);
        
    Player* player = new Player("test");
    Tile* test = new Tile(RED,CIRCLE);
    Tile* test2 = new Tile(BLUE,CIRCLE);
    Tile* test3 = new Tile(GREEN,CIRCLE);  // SQUARE
    Tile* test4 = new Tile(YELLOW,CIRCLE); // STAR_4
    Tile* test5 = new Tile(YELLOW,STAR_4); 
	Tile* test6 = new Tile(GREEN, STAR_4);
    Tile* test7 = new Tile(RED,STAR_4);
    Tile* test8 = new Tile(YELLOW,CIRCLE);
    
    board->putTile(player,test,2,2);
    board->printBoard();
    std::cout<<std::endl;
    board->putTile(player,test2,2,3);
    board->printBoard();
    std::cout<<std::endl;
    board->putTile(player,test3,2,4);
    board->printBoard();
    std::cout<<std::endl;
    board->putTile(player,test4,2,5);
    board->printBoard();
    std::cout<<std::endl;
    board->putTile(player,test5,3,5);
    board->printBoard();
    std::cout<<std::endl;
    board->putTile(player,test6,3,6);
    board->printBoard();
    std::cout<<std::endl;
    board->putTile(player,test7,1,2);
    board->printBoard();
    std::cout<<std::endl;
    board->putTile(player,test8,0,2);
    board->putTile(player,test8,1,2);
    board->putTile(player,test8,0,0);
    
    board->printBoard();
    // board->printTiles();
    return EXIT_SUCCESS;
}

