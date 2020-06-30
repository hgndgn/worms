#ifndef __MOVE_COMMAND_H__
#define __MOVE_COMMAND_H__

#include "ICommand.h"
#include "../FireDirection.h"
#include "../Game.h"
#include "../Utilities.h"
#include "../Worm.h"

class MoveCommand : public ICommand
{
public:
  Game &game;
  Worm &worm;
  const FireDirection &fd;
  const int &steps;

  MoveCommand(Game &_g, Worm &_w, const FireDirection &_fd, const int &_s);

  virtual ~MoveCommand();

  virtual bool execute();
};

#endif