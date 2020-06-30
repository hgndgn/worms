#include "Game.h"

Game::Game(){}

void Game::printPlayersInfo()
  {
    printf("\n\u279C  INFORMATION OF PLAYERS:\n");
    for (Player *&p : allPlayers)
    {
      printf("  Player %s: '%s'\n", p->name.c_str(), p->wormIcon.c_str());
      for (auto &w : p->worms)
      {
        w.printInfo();
      }
      printf("\n");
    }
  }