#ifndef __ACTION_COMMAND_H__
#define __ACTION_COMMAND_H__

#include "ICommand.h"
#include "../Game.h"

class ActionCommand : public ICommand
{
public:
  Game &game;
  string direction = "";
  int col = -1;
  int row = -1;

  ActionCommand(Game &_g);
  ActionCommand(Game &_g, const int &col);
  ActionCommand(Game &_g, const int &col, const int &row);
  ActionCommand(Game &_g, const string &paramString);

  virtual ~ActionCommand();

  virtual bool execute();
};

#endif