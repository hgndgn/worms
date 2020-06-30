#ifndef __QUITE_COMMAND_H__
#define __QUITE_COMMAND_H__

#include "ICommand.h"
#include "../Game.h"

class QuitCommand : public ICommand
{
public:
  virtual ~QuitCommand(){};

  virtual bool execute()
  {
    printf("\n\u279C  Quitting game\n");
    exit(0);
  };
};

#endif