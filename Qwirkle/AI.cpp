
#include "Board.h"
#include "LinkedList.h"
#include <random>
#include <vector>
#include <iostream>
#include "AI.h"

#define BOARD_SIZE      26

Move marvinMove(Board* board, LinkedList* hand, bool difficulty)
{
   //creates a collection of potential moves
   vector<Move> moves;
   
   //checks all of the tiles in the hand
   for (int h=1;h<=hand->size(); h++)
   {
       //iterates across the board
       for (int i=0;i<5; i++)
          for (int j=0;j<5; j++)
             
             //if the move is valid, then the move is added
             //to a list of possible movies
             if (board->moveValidation(hand->get(h),i,j))
             {
                 struct Move move;
                 move.position = h;
                 move.xCoord = i;
                 move.yCoord = j;
                 move.tile = hand->get(h);
                 if(difficulty)
                    move.score = board->getScore(board->countHorizontal(i,j), board->countVertical(i,j));
                 else
                    move.score = 0;
                 moves.push_back(move);
             }
   }

   struct Move selectedMove = moves[0];
   int potentialScore = 0;

   if(difficulty)
	   for (int i=0;i<moves.size();i++)
	   {
          if(moves[i].score>potentialScore)
          {
              potentialScore = moves[i].score;
              selectedMove = moves[i];
          }
	   }
   else
   {
       selectedMove = moves[getRandomNumber(moves.size())];
   }

   // Tile* usedTile = hand->remove(selectedMove.position);

   return selectedMove;
}

//gets a random number based on the number of available movoes
int getRandomNumber(int length)
{

  //the minimum is 1
  int min = 0;

  //the maximum is the number potential moves
  int max = length;

  std::random_device engine;
  std::uniform_int_distribution<int> uniform_dist(min,max);
  int value = uniform_dist(engine);
 
  return value; 
}
