#ifndef __MELEE_H__
#define __MELEE_H__

#include "../Game.h"
#include "../Utilities.h"

class Melee : public Weapon
{
public:
  Melee(Game &_game) : Weapon(_game)
  {
    game = _game;
    name = "melee";
    ammunition = 0;
    fireDirections = FireDirection::ALL();
    damage = 50;
  };

  void fire(FireDirection direction = FireDirection::IDLE())
  {
    if (ammunition > 0)
    {
      ammunition -= 1; // ammunition = ammunition - 1;
    }

    const Position p = game.selectedWorm->position;
    vector<MapElement> neighbours = getAllNeighbours(game, game.map.field[p.y][p.x]);

    for (auto &n : neighbours)
    {
      if (n.isWorm())
      {
        giveDamageAt(game, n.xPos, n.yPos);
      }
    }
  }
};

#endif