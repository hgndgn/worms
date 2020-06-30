#ifndef __MAP_COMMAND_H__
#define __MAP_COMMAND_H__

#include "ICommand.h"
#include "../Game.h"

class MapCommand : public ICommand
{
public:
  Game &game;
  const string name = "map";

  MapCommand(Game &_g) : game(_g){};

  virtual ~MapCommand(){};

  virtual bool execute()
  {
    game.printMap();
    return true;
  };
};

#endif