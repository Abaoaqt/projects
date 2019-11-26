#include "Board.h"
#include <iostream>
#include <fstream>

using std::endl;
using std::cout;
using std::to_string;
using std::vector;

#define BOARD_SIZE  	26
#define MAXLEN 			6

//defining for giving the colour on the output
#define blue "\033[0;34m"
#define red "\033[0;31m"
#define yellow "\033[0;33m"
#define green "\033[0;32m"
#define purple "\033[0;35m"
#define orange "\033[38;5;214m"
#define reset "\033[m"

Board::Board(){
    //construct an empty 2d board
    for(int i = 0; i<=26; i++){
        for(int j = 0; j <26; j ++){
          gameBoard[j][i] = nullptr;
        }
    }
}

Board::Board(int x, int y, bool state){
	this->xEnd = x;
	this->yEnd = y;
	this->initialMove = state; //should be set to false when loading a game
	
    //construct an empty 2d board
    this->gameBoard.resize(this->yEnd);
    
    for(int y = 0; y < this->yEnd; y++){
    	this->gameBoard[y].resize(this->xEnd);
    	
    	for(int x = 0; x < this->xEnd; x++){
    		this->gameBoard[y][x] = nullptr;
		}
	}
}

Board::~Board(){
    
}

bool Board::putTile(Player* player, Tile* tile, int x, int y){
	bool outcome = false;
	this->tile = tile; //why 

	if (this->moveValidation(tile, x, y)){
		this->tile = tile;

    	this->gameBoard[y][x] = tile;
		this->expandBoard(x,y);
		
		player->setScore(player->getScore() + this->getScore(this->countHorizontal(x,y), this->countVertical(x,y)));
		outcome = true;
	
	}
	else{
		cout << "invalid move made" << endl;
	}
	
	return outcome;

}

void Board::printTiles(){
	for(int i = 0; i < BOARD_SIZE ;i ++){
		for (int j = 0 ; j < BOARD_SIZE; j ++){
			std::cout<<"gameBoard["<<i<<"]["<<j<<"] = "<<gameBoard[i][j]<<std::endl;
		}
	}
}

void Board::printBoard(){
	//printing the numbers for the top section
	cout <<"  ";
	for(int i = 0; i < this->xEnd; i++){
		cout << " " << i << " ";
	}
	cout << endl;
	
	//printing '-' to the board
	cout <<"  ";
	for(int i = 0; i <= 3*this->xEnd; i++){
		cout << "-";
	}
	cout << endl;
	
	//printing the rest of the board
	for(int i = 0; i < this->yEnd; i++){
		cout<< char(i+65) << " |";
		for(int j = 0; j < this->xEnd; j++){
			//condition where there's no tile on that location
			if(this->gameBoard[i][j] == nullptr){
				cout << "  |";
			}
			//condition where there's a tile on that location and printing it out using colour 
			// using cout<<'colour'<<...<<'reset'; set the colour and reset it at the end of cout to return the colour back to normal
			else{
				cout << gameBoard[i][j]->getColour()<<gameBoard[i][j]->getShape();				
				cout<< "|";				
			}
		}
		cout<< endl;
	}
}

bool Board::moveValidation(Tile* tile, int x, int y){
	bool valid = false;
	if (y < 0 || y > this->yEnd || x < 0  || x > this->xEnd){
		valid = false;
	}
	else{
		// first move should always be legal
		if(this->initialMove){
			valid = true;
			this->initialMove = false;
		}
		else{
			// is the space empty?
			if(this->gameBoard[y][x] == nullptr){
				valid = true;
				int hCount = 1;
				int vCount = 1;
				// for all directions:
				// while there is a piece adjacent in the direction and its placement is still valid 
				// get the current adjacent piece
				// if it shares only one attribute with the placed piece, it remains valid
				// if there are no shared attributes or both attributes are shared, then the tile cannot be placed
				// case is invalid

				// if hCount or vCount are greater than the max length for a line, then it is not valid either

				// rows above case:
				int yu = y-1;
				while(yu > 0 && this->gameBoard[yu][x] != nullptr && valid){
					if((this->gameBoard[yu][x]->getColour() == tile->getColour() && this->gameBoard[yu][x]->getShape() == tile->getShape()) ||
					(this->gameBoard[yu][x]->getColour() != tile->getColour() && this->gameBoard[yu][x]->getShape() != tile->getShape()) ){
						valid = false;
					}
					yu--;
					vCount++;
				}
				
				// rows below case: 
				int yd = y+1;
				while(yd < this->yEnd && this->gameBoard[yd][x] != nullptr && valid){
					if((this->gameBoard[yd][x]->getColour() == tile->getColour() && this->gameBoard[yd][x]->getShape() == tile->getShape()) ||
					(this->gameBoard[yd][x]->getColour() != tile->getColour() && this->gameBoard[yd][x]->getShape() != tile->getShape()) ){
						valid = false;
					}
					yd++;
					vCount++;
				}
				
				//columns to the right case:
				int xr = x+1;
				while(xr < this->xEnd && this->gameBoard[y][xr] != nullptr && valid){
					if((this->gameBoard[y][xr]->getColour() == tile->getColour() && this->gameBoard[y][xr]->getShape() == tile->getShape()) ||
					(this->gameBoard[y][xr]->getColour() != tile->getColour() && this->gameBoard[y][xr]->getShape() != tile->getShape()) ){
						valid = false;
					}
					xr++;
					hCount++;
				}

				//columns to the left case:
				int xl = x-1;
				while(xl > 0 && this->gameBoard[y][xl] != nullptr && valid){
					if((this->gameBoard[y][xl]->getColour() == tile->getColour() && this->gameBoard[y][xl]->getShape() == tile->getShape()) ||
					(this->gameBoard[y][xl]->getColour() != tile->getColour() && this->gameBoard[y][xl]->getShape() != tile->getShape()) ){
						valid = false;
					}
					xl--;
					hCount++;
				}

				if((hCount > MAXLEN || vCount > MAXLEN) || (hCount == 1 && vCount == 1)){
					valid = false;
				}
			}
		}
	}
	return valid;
}

void Board::expandBoard(int x, int y){
	// adding a column to the left
	if(x == 0){
		this->xEnd++;
		for(int y = 0; y < this->yEnd; y++){
			this->gameBoard[y].insert(this->gameBoard[y].begin(), nullptr);
		}	
	}
	// adding a column to the right
	else if(x == this->xEnd-1){
		this->xEnd++;
		for(int y = 0; y < this->yEnd; y++){
			this->gameBoard[y].push_back(nullptr);
		}
	}
	
	// adding a row at the bottom
	if(y == this->yEnd-1){
		this->yEnd++;
		// create a new row to insert in
		vector<Tile*> insert;
		insert.resize(this->xEnd);
		for(int i = 0; i < this->xEnd; i++){
			insert[i] = nullptr;
		}
		this->gameBoard.push_back(insert);
	}
	
	// adding a row at the top
	else if(y == 0){
		this->yEnd++;
		vector<Tile*> insert;
		insert.resize(this->xEnd);
		for(int i = 0; i < this->xEnd; i++){
			insert[i] = nullptr;
		}
		this->gameBoard.insert(this->gameBoard.begin(), insert);
		
	}
}

int Board::countHorizontal(int x, int y){
	int count = 0 ;
	for(int i = x+1; i < this->xEnd;i++){
		if(gameBoard[y][i]!= nullptr){
			count ++ ;
		}
		else{i = this->xEnd;}
	}
	for(int o = x-1; o >=0 ; o--){
		if(gameBoard[y][o]!= nullptr){
			count ++ ;
		}
		else{o=0;}
	}
	return count;
}

int Board::countVertical(int x, int y){
	int count = 0 ;
	for(int i = y+1; i < this->yEnd;i++){
		if(gameBoard[i][x]!= nullptr){
			count ++ ;
		}
		else{i = this->yEnd;}
	}
	for(int o = y-1; o >=0 ; o--){
		if(gameBoard[o][x]!= nullptr){
			count ++ ;
		}
		else{o=0;}
	}
	return count;
}

//works as long as one tile is placed at a time
int Board::getScore(int countHorizontal , int countVertical){
	int score = 1;
	if(countHorizontal>0){
		if(countHorizontal==5){
			score += 11;
		}
		else{
			score += countHorizontal;
		}
	}
	if(countVertical>0){
		if(countVertical==5){
			score += 11;
		}
		else{
			score += countVertical;
		}
	}
	if(countHorizontal == 5 && countVertical == 5){
		score = 24;
	}
	return score;
}

void Board::setTile(Tile* tile, int x, int y){
	this->gameBoard[y][x] = tile;
}

void Board::saveBoard(std::ofstream& outFile){

	outFile <<"  ";
	for(int i = 0; i < this->xEnd; i++){
		outFile << " " << i << " ";
	}
	outFile << endl;
	
	outFile <<"  ";
	for(int i = 0; i <= 3*this->xEnd; i++){
		outFile << "-";
	}
	outFile << endl;
	
	for(int i = 0; i < this->yEnd; i++){
		outFile<< char(i+65) << " |";
		for(int j = 0; j < this->xEnd; j++){
			if(this->gameBoard[i][j] == nullptr){
				outFile << "  |";
			}
			else{
				outFile << this->gameBoard[i][j]->getColour() << this->gameBoard[i][j]->getShape() << "|";
			}
		}
		outFile << endl;
	}
}

int Board::getXEnd() {
	return xEnd;
}

int Board::getYEnd(){
	return yEnd;
}

void Board::setXEnd(int x){
	this->xEnd = x;
}

void Board::setYEnd(int y){
	this->yEnd = y;
}

void Board::resize(int x, int y){
	this->setXEnd(x);
	this->setYEnd(y);

	this->gameBoard.resize(this->yEnd);
    
    for(int y = 0; y < this->yEnd; y++){
    	this->gameBoard[y].resize(this->xEnd);
    }
}

void Board::setState(){
	this->initialMove = false;
}
