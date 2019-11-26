
#include "Board.h"
#include "LinkedList.h"
#include <vector>
#include <iostream>
#include "AI.h"

#define BOARD_SIZE      26

Move marvinMove(Board* board, LinkedList* hand)
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
                 move.xCoord = i;
                 move.yCoord = j;
                 move.tile = hand->get(h);
                 move.score = 0;
                 moves.push_back(move);
             }

   }

   return moves[5];

}
