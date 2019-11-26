#include "LinkedList.h"
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>

#define MAX_DUPLICATES     3

LinkedList* fillBag()
{

    LinkedList* bag = new LinkedList();
    Tile* tile = nullptr;

    for (int i=0;i<MAX_DUPLICATES; i++)
    {
        for (int i=1;i<7;i++)
        {
            tile = new Tile(RED, i);
            bag->addFront(tile);
            tile = new Tile(ORANGE, i);
            bag->addFront(tile);
            tile = new Tile(YELLOW, i);
            bag->addFront(tile);
            tile = new Tile(GREEN, i);
            bag->addFront(tile);
            tile = new Tile(BLUE, i);
            bag->addFront(tile);
            tile = new Tile(PURPLE, i);
            bag->addFront(tile);

        }
    }

    return bag;
}

void printBag(LinkedList* bag)
{
   for (int i=1;i<bag->size();i++)
   {
      std::cout<<bag->get(i)->getColour()<<bag->get(i)->getShape()<<std::endl;
   }
}


//generates a random number between 1 and the number of tiles in the bag
int getRandomNumber(LinkedList* bag)
{

  //default value for an empty bag
  int value = -1;

  //the minimum is 1
  int min = 1;

  //the maximum is the number of pieces in the bag
  int max = bag->size();

  //confirms that there are tiles in the bag
  if(max>0)
  {
     std::random_device engine;
     std::uniform_int_distribution<int> uniform_dist(min,max);
     value = uniform_dist(engine);
  }
  return 1;  

}

//returns a random tile from the bag, as long as the bag is not empty
Tile* getRandomTile(LinkedList* bag)
{

  //sets the value of a tile to nill and gets a random number
  Tile* tile = nullptr;
  int piece = getRandomNumber(bag);

  //confirms that there are tiles in the bag (is not -1)
  //and gets the appropriate tile from the bag
  if(piece>0) {
    tile = bag->get(piece);
    bag->removeTile(tile->getColour(), tile->getShape());
     //tile = bag->remove(piece);
  }
  
  return tile;
}

//replaces the tile into the bag, namely the position is
//placed at the end
void replaceTile(Tile* tile, LinkedList* bag)
{
  bag->addBack(tile);
}

LinkedList* loadBag()
{
   LinkedList* bag = new LinkedList();
   Tile* tile;
   std::string filename = "bag.txt";
   
   std::ifstream inFile;
   inFile.open(filename);

   if(inFile.good())
   {
       while(!inFile.eof())
       {
           std::string line;
           std::getline(inFile, line);
           if (line.length() == 3)
           {
              int shape = 0;
              std::string shp = line.substr (2,1);
              std::istringstream (shp) >> shape;
              tile = new Tile(line[0],shape);
              bag->addFront(tile);
           }
       }
   }

   inFile.close();

   return bag;
} 
