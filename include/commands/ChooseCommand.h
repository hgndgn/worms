#ifndef __CHOOSE_COMMAND_H__
#define __CHOOSE_COMMAND_H__

#include "ICommand.h"
#include "../Game.h"

class ChooseCommand : public ICommand
{
public:
  Game &game;
  const string &weaponName;

  ChooseCommand(Game &_g, const string &weaponName);

  virtual ~ChooseCommand();

  virtual bool execute();
};

#endif