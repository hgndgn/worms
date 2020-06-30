#ifndef __MAP_ELEMENT_H__
#define __MAP_ELEMENT_H__

#include "common.h"
#include "Position.h"
#include "constants.h"

class MapElement
{
public:
  string value;
  int xPos;
  int yPos;

  MapElement(string);
  MapElement(string, int, int);

  bool isWorm()
  {
    return this->value.compare(AIR) != 0 && this->value.compare(EARTH) != 0 && this->value.compare(WATER) != 0 && this->value.compare(CASE) != 0;
  }
  bool isCase()
  {
    return this->value.compare(CASE) == 0;
  }
};

#endif