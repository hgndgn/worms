#include "MapElement.h"

MapElement::MapElement(string _value) : value(_value) {}
MapElement::MapElement(string _value, int _xPos, int _yPos) : value(_value), xPos(_xPos), yPos(_yPos) {}