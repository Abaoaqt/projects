struct Move {
   int xCoord;
   int yCoord;
   int position;
   Tile* tile;
   int score;
};

Move marvinMove(Board* board, LinkedList* hand, bool difficulty);
int getRandomNumber(int length);
