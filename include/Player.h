#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "common.h"
#include "Game.h"
#include "Worm.h"

class Game;
class Worm;

class Player
{
public:
  Game &game;
  string name;
  vector<Worm> worms;
  string wormIcon;

  int numWorms();
  void selectWorm(const string &name);

  Player(Game &_s, const string &_name, const string &_wormIcon);

  bool operator==(const Player &p) const
  {
    return (this->name == p.name);
  }
};

#endif