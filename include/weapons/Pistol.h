#ifndef __PISTOL_H__
#define __PISTOL_H__

#include "../common.h"
#include "../Game.h"
#include "../Utilities.h"

class Pistol : public Weapon
{
public:
  Pistol(Game &_game) : Weapon(_game)
  {
    game = _game;
    name = "pistol";
    ammunition = -1;
    fireDirections = FireDirection::ALL();
    damage = 25;
  };

  void fire(FireDirection direction)
  {
    Position pos = game.selectedWorm->position;
    _fire(direction, pos.x, pos.y);
  }

private:
  void _fire(FireDirection direction, int xPos, int yPos)
  {
    MapElement curCell = game.map.field[yPos][xPos];

    bool hit = false;

    while (!hit)
    {
      curCell.xPos = curCell.xPos + direction.xChange;
      curCell.yPos = curCell.yPos + direction.yChange;

      if (curCell.yPos < 0)
      {
        return;
      }

      curCell.value = game.map.field[curCell.yPos][curCell.xPos].value;

      if (curCell.value.compare(AIR) != 0)
      {
        hit = true;
        giveDamageAt(game, curCell.xPos, curCell.yPos);
      }
    }
  };
};

#endif