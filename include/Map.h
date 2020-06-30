#ifndef __MAP_H__
#define __MAP_H__

#include "common.h"
#include "MapElement.h"

typedef vector<vector<MapElement>> MapField;

class Map
{
public:
  MapField field;
  int numColumns;
  int numRows;

  Map();

};

#endif