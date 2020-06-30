#ifndef __HELP_COMMAND_H__
#define __HELP_COMMAND_H__

#include "ICommand.h"
#include "../Game.h"

class HelpCommand : public ICommand
{
public:
  virtual ~HelpCommand(){};

  virtual bool execute()
  {
    printf("Available Commands:\n");
    printf("move [left/right] [0..3]\n");
    printf("    Move your worm.\n");
    printf("choose [weapon]\n");
    printf("    Select your weapon.\n");
    printf("action [t/r/b/l/tr/br/bl/tl]\n");
    printf("    Shoots current weapon.\n");
    printf("    Activates blowtorch.\n");
    printf("action\n");
    printf("    Activates melee attack.\n");
    printf("action [row] [col]\n");
    printf("    Teleports to coordinate.\n");
    printf("action [col]\n");
    printf("    Airstrike.\n");
    printf("action idle\n");
    printf("    Do nothing.\n");
    printf("quit\n");
    printf("    End the game.\n");
    printf("help\n");
    printf("    Display this help.\n");
    printf("state\n");
    printf("    Print the current game state.\n");
    return true;
  };
};

#endif