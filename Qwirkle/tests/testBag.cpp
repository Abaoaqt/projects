#include <iostream>
#include "LinkedList.h"
#include "bag.h"

#define  EXIT_SUCCESS      0

using std::cout;
using std::endl;
using std::string;

int main(void)
{

  //tests that a tile can be created and the tileCodes are valid
  Tile* tile = new Tile('R',1);

  if(tile->getColour() == RED && tile->getShape() ==CIRCLE)
     std::cout<<"Create Tile: Success"<<std::endl;
  else
     std::cout<<"Create Tile: Failure"<<std::endl;

  delete tile;

  LinkedList* bag = new LinkedList();

  //tests that the program does not fail when attempt to remove a tile from the empty bag
  bag->removeFront();

  bag = fillBag();
  
  //tests to see that the size of the bag is 72 (that is contains 72 pieces)
  if(bag->size() == 72)
     std::cout<<"Bag Size 72: Success"<<std::endl;
  else
     std::cout<<"Bag Size 72: Failure"<<std::endl;

  //tests that the first tile in the bag is a purple clover
  tile = bag->get(1);

  if(tile->getColour() == PURPLE && tile->getShape() == CLOVER)
     std::cout<<"Get First Tile Purple Clover: Success"<<std::endl;
  else
     std::cout<<"Get First Tile Purple Clover: Failure"<<std::endl;

  //tests that the last tile in the bag is a red circle
  tile = bag->get(bag->size());

  if(tile->getColour() == RED && tile->getShape() ==CIRCLE)
     std::cout<<"Get Last Tile Red Circle: Success"<<std::endl;
  else
     std::cout<<"Get Last Tile Red Circle: Failure"<<std::endl;

  //tests that random numbers are generated
  std::cout<<getRandomNumber(bag)<<std::endl;
  std::cout<<getRandomNumber(bag)<<std::endl;
  std::cout<<getRandomNumber(bag)<<std::endl;
  std::cout<<getRandomNumber(bag)<<std::endl;
  std::cout<<getRandomNumber(bag)<<std::endl;
  std::cout<<getRandomNumber(bag)<<std::endl;
  std::cout<<getRandomNumber(bag)<<std::endl;
  std::cout<<getRandomNumber(bag)<<std::endl;

  //tests that random tiles are removed from the bag
  tile = getRandomTile(bag);
  std::cout<<tile->getColour()<<" "<<tile->getShape()<<" bag size "<<bag->size()<<endl;
  tile = getRandomTile(bag);
  std::cout<<tile->getColour()<<" "<<tile->getShape()<<" bag size "<<bag->size()<<endl;
  tile = getRandomTile(bag);
  std::cout<<tile->getColour()<<" "<<tile->getShape()<<" bag size "<<bag->size()<<endl;
  tile = getRandomTile(bag);
  std::cout<<tile->getColour()<<" "<<tile->getShape()<<" bag size "<<bag->size()<<endl;

  saveBag(bag);

  return EXIT_SUCCESS;
}
