#include <iostream>
#include "Board.h"

#define  EXIT_SUCCESS      0

using std::cout;
using std::endl;
using std::string;

int main(void)
{
	
    Board* board = new Board(5,5, true);

    
    board->printBoard();
    Player* player = new Player("test");
    Tile* test = new Tile(RED,CIRCLE);
    Tile* test2 = new Tile(BLUE,CIRCLE);
    Tile* test3 = new Tile(GREEN,CIRCLE);  // SQUARE
    Tile* test4 = new Tile(YELLOW,CIRCLE); // STAR_4
    Tile* test5 = new Tile(YELLOW,STAR_4); 
  	Tile* test6 = new Tile(GREEN, STAR_4);
    
    board->putTile(player,test,2,2);

    board->putTile(player,test2,2,3);
    board->putTile(player,test3,2,4);
    board->putTile(player,test4,2,5);
    board->putTile(player,test5,3,5);
    board->putTile(player,test6,3,6);

    cout << "player score: " << player->getScore() << endl;
    board->putTile(player,test2,2,3);
    cout << "player score: " << player->getScore() << endl;
    board->putTile(player,test3,2,4);
    cout << "player score: " << player->getScore() << endl;
    board->putTile(player,test4,2,5);
    cout << "player score: " << player->getScore() << endl;
    board->putTile(player,test5,3,5);
	cout << "player score: " << player->getScore() << endl;
    board->putTile(player,test6,3,6);
    cout << "player score: " << player->getScore() << endl;
    
    board->printBoard();
    // board->printTiles();
    return EXIT_SUCCESS;
}

// compiling command
// g++ -Wall -Werror -std=c++14 -O -o test BoardTest.cpp Board.cpp Tile.cpp LinkedList.cpp Node.cpp
