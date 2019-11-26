
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"
#include "TileCodes.h"

class Node {
public:

   Node(Tile* tile, Node* next);
   Node(Node& other);
   ~Node();

   Tile*    tile;
   Node*    next;
};

#endif // ASSIGN2_NODE_H
