#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "common.h"
#include "Game.h"
#include "FireDirection.h"

class Game;

class Weapon
{
public:
  Game &game;
  string name;
  vector<string> fireDirections;
  int ammunition;
  int damage;

  Weapon(Game &s);

  virtual void fire(FireDirection fd = FireDirection::IDLE()) = 0;
  void printInfo();
  
  static bool hasWeapon(vector<Weapon *> weapons, const string &name)
  {
    for (auto &w : weapons)
    {
      if (w->name.compare(name) == 0)
      {
        return true;
      }
    }
    return false;
  }
};

#endif