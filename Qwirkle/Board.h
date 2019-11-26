#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H


#include <string>
#include <fstream>
#include <vector>
#include "Tile.h"
#include "TileCodes.h"
#include "Player.h"

using std::to_string;
using std::vector;
using std::string;

class Board{
public:
    Board();
    Board(int x, int y, bool state);
    
    ~Board();
    void printBoard();
    bool putTile(Player* player, Tile* tile, int x, int y);
    void printTiles();
    void setTile(Tile* tile, int x, int y);
    void saveBoard(std::ofstream& outFile);

    bool moveValidation(Tile* tile, int x, int y);
    void expandBoard(int x, int y);
    int countHorizontal(int x, int y);
    int countVertical(int x, int y);
    int getScore(int countHorizontal, int countVertical);
    int getXEnd();
    int getYEnd();
    void setXEnd(int x);
    void setYEnd(int y);
    void resize(int x, int y);
    void setState();

   
private:
    //std::string gameBoard[26][26];
	std::vector<std::vector<Tile*> > gameBoard;
    
    bool initialMove;
    int xEnd;
    int yEnd;
    Tile* tile;
};

#endif // ASSIGN2_BOARD_H
