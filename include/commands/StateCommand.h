#ifndef __STATE_COMMAND_H__
#define __STATE_COMMAND_H__

#include "ICommand.h"
#include "../Game.h"

class StateCommand : public ICommand
{
public:
  Game &game;
  StateCommand(Game &_g) : game(_g){};

  virtual ~StateCommand(){};

  virtual bool execute()
  {
    printf("__________________ STATE __________________\n");
    printf("Current player: %s\n", game.currentPlayer->name.c_str());
    printf("Current worm: %s\n", game.selectedWorm->name.c_str());
    printf("Weapons of current worm: \n");
    for (auto &w : game.selectedWorm->weapons)
    {
      w->printInfo();
    }

    for (auto &p : game.allPlayers)
    {
      printf("Worms of Player %s: '%s'\n", p->name.c_str(), p->wormIcon.c_str());
      for (auto &w : p->worms)
      {
        w.printInfo();
      }
    }

    return true;
  };
};

#endif