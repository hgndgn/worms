#ifndef __FIRE_DIRECTION_H__
#define __FIRE_DIRECTION_H__

#include "common.h"

class FireDirection
{

public:
  string direction;
  int xChange;
  int yChange;

  FireDirection(string _direction, int _xChange, int _yChange);

  FireDirection();

  static vector<string> ALL()
  {
    return {"t", "r", "b", "l", "tr", "br", "bl", "tl"};
  }

  static FireDirection IDLE()
  {
    FireDirection fd("-", 0, 0);
    return fd;
  }

  static FireDirection TOP()
  {
    FireDirection fd("t", 0, -1);
    return fd;
  };
  static FireDirection RIGHT()
  {
    FireDirection fd("r", 1, 0);
    return fd;
  }
  static FireDirection BOTTOM()
  {
    FireDirection fd("b", 0, 1);
    return fd;
  }
  static FireDirection LEFT()
  {
    FireDirection fd("l", -1, 0);
    return fd;
  }
  static FireDirection TOP_RIGHT()
  {
    FireDirection fd("tr", 1, -1);
    return fd;
  }
  static FireDirection BOTTOM_RIGHT()
  {
    FireDirection fd("br", 1, 1);
    return fd;
  }
  static FireDirection BOTTOM_LEFT()
  {
    FireDirection fd("bl", -1, 1);
    return fd;
  }
  static FireDirection TOP_LEFT()
  {
    FireDirection fd("tl", -1, -1);
    return fd;
  }

};

#endif