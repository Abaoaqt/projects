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
    
    return EXIT_SUCCESS;
}

