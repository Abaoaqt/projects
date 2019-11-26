#include "Tile.h"

Tile::Tile(Colour colour, Shape shape)
{
   this->colour = colour;
   this->shape = shape;
}


Colour Tile::getColour()
{
   return colour;
}


Shape Tile::getShape()
{
   return shape;
}

