#ifndef __POSITION_H__
#define __POSITION_H__

#include "common.h"

class Position
{
public:
  int x;
  int y;

  Position();
  Position(int x, int y);

  bool operator == (const Position &position) const
  {
    return (this->x == position.x && this->y == position.y);
  }
};

#endif