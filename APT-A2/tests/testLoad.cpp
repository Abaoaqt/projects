#include <iostream>
#include "LinkedList.h"
#include "bag.h"

#define  EXIT_SUCCESS      0

using std::cout;
using std::endl;
using std::string;

int main(void)
{

  LinkedList* list = loadBag();
  Tile* tileTemp;

  //tests that the remove tile function works
  tileTemp = list->remove(3);

  if(tileTemp->getColour() == 'Y' && tileTemp->getShape() ==1)
     std::cout<<"Remove Node 3 and display: Success"<<std::endl;
  else
     std::cout<<"Remove Node 3 and display: Failure"<<std::endl;

  delete tileTemp;

  //tests that the remove tile function works
  tileTemp = list->remove(3);

  if(tileTemp->getColour() == 'G' && tileTemp->getShape() ==1)
     std::cout<<"Remove Node 3 and display: Success"<<std::endl;
  else
     std::cout<<"Remove Node 3 and display: Failure"<<std::endl;

  delete tileTemp;

  //tests that the remove tile function works
  tileTemp = list->remove(3);

  if(tileTemp->getColour() == 'B' && tileTemp->getShape() ==1)
     std::cout<<"Remove Node 3 and display: Success"<<std::endl;
  else
     std::cout<<"Remove Node 3 and display: Failure"<<std::endl;

  delete tileTemp;

  return EXIT_SUCCESS;
}
