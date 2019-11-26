
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();
   int size();
   void clear();
   Tile* get(int i);
   Tile* getTile(char colour, int shape);
   Tile* remove(int i);
   void removeTile(char colour, int shape);

   void addFront(Tile* tile);
   void addBack(Tile* tile);
   void removeFront();
   void removeBack();
   Node* getHead();

private:
   Node* head;
   Node* tail;
   int listSize;
};

#endif // ASSIGN2_LINKEDLIST_H
