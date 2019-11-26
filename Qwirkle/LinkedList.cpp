#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {

   head = nullptr;
   tail = nullptr;
   listSize = 0;

}

LinkedList::~LinkedList() {

   tail = nullptr;
   clear();
}

int LinkedList::size()
{
   return listSize;
}

void LinkedList::clear()
{
   //confirms that there are nodes in the list
   if (listSize!=0)
   {
      //otherwise sets the parameters to clear the list
      int count = 1;
      Node* counter = head;

      //iterates through the list
      while(count<=listSize)
      {
         //stores the address of the next node
         counter=head->next;
   
         //deletes the node
         delete head;

         //moves onto the next
         head = counter;
         count++;
      }
      listSize=0;
   }
}

//gets the data from the nth (i) node
//If i is not within range, null will be returned
//This also captures an empty list (since listSize = 0)
Tile* LinkedList::get(int i)
{
  Tile* tile;
  //confirms that the request is within range
  if (i<=0 || i> listSize)
    tile=nullptr;
  else
  {
    //sets the search variables
    bool found = false;
    int count = 1;
    Node* counter = head;

    //iterates through the list
    while(!found)
    {
       //if the node number is equal to the request
       if(count == i)
       {
         //returns the data stored in the node
         tile=counter->tile;
         found = true;
       }
       else
       {
         //otherwise moves to the next node
         count++;
         counter=counter->next;
       }
    }
  }
  return tile;
}

Tile* LinkedList::getTile(char  colour, int shape)
{
  Tile* tile = nullptr;
  //confirms that the request is within range
  if (listSize == 0)
    tile=nullptr;
  else
  {
    //sets the search variables
    bool found = false;
    int count = 1;
    Node* counter = head;

    //iterates through the list
    while(!found && count<=listSize)
    {
       //
       if(counter->tile->getColour() == colour && counter->tile->getShape() == shape)
       {
         //returns the data stored in the node
         tile=counter->tile;
         found = true;
       }
       else
       {
         //otherwise moves to the next node
         count++;
         counter=counter->next;
       }
    }
  }
  return tile;
}

//removes a tile from the list with the value tileRqst and passes to the implementing function
//THIS FUNCTION DOES NOT DELETE THE NODE
//If i is not within range, null will be returned
//This also captures an empty list (since listSize = 0)
Tile* LinkedList::remove(int i)
{
  Tile* tile = nullptr;
  
  if(i<=0 || i>listSize)
  {
     tile=nullptr;
  }
  else
  {
     //sets the search variables
     bool found = false;

     //Stores the location of the current node
     Node* counter = head;
     int count=1;

     //Stores the location of the previous node
     Node* previous=nullptr;

     //iterates through the list
     while(!found)
     {
        //if the tile in this node is equal to the request
        if(count == i)
        {
           //returns the tile stored in the node
           tile=counter->tile;

            if(tile == get(1)) { 
               removeFront();
               break;
            }

           //sets the pointer in the previous node to the next
           previous->next=counter->next;
           found = true;
           listSize--;
        }
        else
        {
           //otherwise moves to the next node
           //and sets the current node as the previous
           previous=counter;
           counter=counter->next;
           count++;
        }
     }
  }
  return tile;
}

void LinkedList::addFront(Tile* tile)
{

   //create a new node and the node points to the head
   Node* node = new Node(tile,head);

   //The head now points to this node.
   head = node;

   //if the tail points to null, then this will be the first node
   //so the tail will point to this node
   if(tail == nullptr)
     tail = node;

   //the size of the list is increased by one
   listSize++;

}

void LinkedList::addBack(Tile* tile)
{
   //create a new node with the data and nullptr
   Node* node = new Node(tile,nullptr);

   //checks to see if there are any nodes in the list and if not
   //adds this node as the head and as the tail
   if(listSize == 0)
   {
     head = node;
     tail = node;
     listSize++;
   }
   else
   {
     //otherwise points the tail to the new node
     tail->next = node;

     //and makes the new node the tail
     tail = node;
     listSize++;
   }
}

//removes the node at the front. Nothing happens if the list is empty
void LinkedList::removeFront()
{

   //confirms that the list is not empty
   if (listSize>0)   
   {

      //creates a temporary pointer
      Node* node = head;

      //shifts the head to the next in line
      head = head->next;

      //deletes the previous head
      delete node;

      //decreases the size of the list by one.
      listSize--;

   }
}

//removes the node at the back of the list
//nothing happens if the list is empty
void LinkedList::removeBack()
{
   if (listSize>0)
   {
      //creates a temporary pointer
      Node* node = head;

      //iterates through the list until it finds the node before the tail
      while(node->next != tail)
         node = node->next;
  
      //deletes the tail
      delete tail;

      //sets the previous node as the new tail
      tail = node;

      //decreases the size of the list by one
      listSize--;
   }
}

void LinkedList::removeTile(char colour, int shape)
{
   //sets the search variables
   bool found = false;

  if(listSize == 0) 
  {
     found = true;
  }
  else
  {
     //Stores the location of the current node
     Node* counter = head;
     //Stores the location of the previous node
     Node* previous = nullptr;

     //iterates through the list
     while(!found)
     {
        //if the tile in this node is equal to the request
       if(counter->tile->getColour() == colour && counter->tile->getShape() == shape)
       {
           //clears the tile that has been removed
           counter->tile = nullptr;

           if(head == counter) 
           {
              removeFront();
              found=true;

           } else if (tail == counter) {

              removeBack();
              found = true;

           } else {

              //sets the pointer in the previous node to the next
              previous->next=counter->next;
              found = true;
              delete counter;
              listSize--;
           }
        }
        else
        {
           //otherwise moves to the next node
           //and sets the current node as the previous
           previous=counter;
           counter=counter->next;
        }
     }
  }
}


Node* LinkedList::getHead() {
   return head;
}
