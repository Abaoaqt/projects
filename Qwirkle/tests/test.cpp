#include <iostream>
#include "LinkedList.h"

#define  EXIT_SUCCESS      0

using std::cout;
using std::endl;
using std::string;

// int main(void)
// {
//   LinkedList* list = new LinkedList();

//   delete list;

//   Tile* tile = new Tile('A',1);

//   if(tile->getColour() == 'A' && tile->getShape() ==1)
//      std::cout<<"Create Tile: Success"<<std::endl;
//   else
//      std::cout<<"Create Tile: Failure"<<std::endl;

//   delete tile;

//   list = new LinkedList();

//   tile = new Tile('A',1);

//   list->addFront(tile);

//   Tile* tileTemp = list->get(1);

//   if(tileTemp->getColour() == 'A' && tileTemp->getShape() ==1)
//      std::cout<<"Add 1 Node: Success"<<std::endl;
//   else
//      std::cout<<"Add 1 Node: Failure"<<std::endl;

//   tile = new Tile('B',2);
//   list->addFront(tile);
//   tile = new Tile('C',3);
//   list->addFront(tile);

//   tileTemp = list->get(1);

//   if(tileTemp->getColour() == 'C' && tileTemp->getShape() ==3)
//      std::cout<<"Add 2 Nodes and get Front: Success"<<std::endl;
//   else
//      std::cout<<"Add 2 Nodes and get Front: Failure"<<std::endl;

//   tile = new Tile('D',4);
//   list->addBack(tile);

//   tileTemp = list->get(4);

//   if(tileTemp->getColour() == 'D' && tileTemp->getShape() ==4)
//      std::cout<<"Add Back and get Back: Success"<<std::endl;
//   else
//      std::cout<<"Add Back and get Back: Failure"<<std::endl;

//   tileTemp = list->remove(3);

//   if(tileTemp->getColour() == 'A' && tileTemp->getShape() ==1)
//      std::cout<<"Remove Node 3 and display: Success"<<std::endl;
//   else
//      std::cout<<"Remove Node 3 and display: Failure"<<std::endl;

//   delete tileTemp;

//   tileTemp = list->get(3);

//   if(tileTemp->getColour() == 'D' && tileTemp->getShape() ==4)
//      std::cout<<"Display new Node 3: Success"<<std::endl;
//   else
//      std::cout<<"Display new Node 3: Failure"<<std::endl;

//   if(list->size()==3)
//      std::cout<<"Show List Size 3: Success"<<std::endl;
//   else
//      std::cout<<"Show List Size 3: Failure"<<std::endl;

//   list->removeFront();

//   if(list->size()==2)
//      std::cout<<"Remove Front and Show List Size 2: Success"<<std::endl;
//   else
//      std::cout<<"Remove Front and Show List Size 2: Failure"<<std::endl;

//   tileTemp = list->get(1);

//   if(tileTemp->getColour() == 'B' && tileTemp->getShape() ==2)
//      std::cout<<"Get front node: Success"<<std::endl;
//   else
//      std::cout<<"Get front node: Failure"<<std::endl;

//   tile = new Tile('E',5);
//   list->addBack(tile);
//   tile = new Tile('G',6);
//   list->addBack(tile);

//   tileTemp = list->get(4);

//   if(tileTemp->getColour() == 'G' && tileTemp->getShape() ==6)
//      std::cout<<"Add 2 Back Nodes and get Back Node: Success"<<std::endl;
//   else
//      std::cout<<"Add 2 Back Nodes and get Back Node: Failure"<<std::endl;

//   tileTemp = list->get(3);

//   if(tileTemp->getColour() == 'E' && tileTemp->getShape() ==5)
//      std::cout<<"Get 2nd Last Node: Success"<<std::endl;
//   else
//      std::cout<<"Get 2nd Last Node: Failure"<<std::endl;

//   list->removeBack();

//   if(list->size()==3)
//      std::cout<<"Remove Back node and show Size 3: Success"<<std::endl;
//   else
//      std::cout<<"Remove Back node and show Size 3: Failure"<<std::endl;

//   tileTemp = list->get(3);

//   if(tileTemp->getColour() == 'E' && tileTemp->getShape() ==5)
//      std::cout<<"Get New Back Node: Success"<<std::endl;
//   else
//      std::cout<<"Get New Back Node: Failure"<<std::endl;

//   delete list;
//   delete tileTemp;

//   return EXIT_SUCCESS;
// }
