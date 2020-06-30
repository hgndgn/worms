#ifndef __WORM_H__
#define __WORM_H__

#include "common.h"
#include "Position.h"
#include "Weapon.h"
#include "Game.h"


class Weapon;
class Game;

class Worm
{
public:
  int id;
  string name;
  string icon;
  string playerId;
  int health;
  Position position;
  vector<Weapon *> weapons;

  Worm();
  Worm(int id, string name, string icon, string playerId);

  void initWeapons(Game &game);

  string getPositionString()
  {
    return this->position.x + "/" + this->position.y;
  }

  void printInfo()
  {
    printf("  - Worm %s:\n", this->name.c_str());
    printf("      Position(x/y): %d/%d\n", this->position.x, this->position.y);
    printf("      Health: %d\n", this->health);
  }
};

#endif