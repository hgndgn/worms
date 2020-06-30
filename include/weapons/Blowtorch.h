#ifndef __BLOWTORCH_H__
#define __BLOWTORCH_H__

#include "../common.h"
#include "../Game.h"
#include "../Utilities.h"

class Blowtorch : public Weapon
{
public:
  Blowtorch(Game &_game) : Weapon(_game)
  {
    game = _game;
    name = "blowtorch";
    ammunition = 0;
    fireDirections = FireDirection::ALL();
    damage = 35;
  };

  void fire(FireDirection direction)
  {
    _fire(direction);
    if (ammunition > 0)
    {
      ammunition -= 1; // ammunition = ammunition - 1;
    }
  }

private:
  int maxRange = 5;

  void _fire(FireDirection direction)
  {
    Position current = game.selectedWorm->position;
    MapElement curCell = game.map.field[current.y][current.x];

    bool hit = false;
    int i = 0;

    while (!hit && i <= maxRange)
    {
      i++;
      curCell.xPos = curCell.xPos + direction.xChange;
      curCell.yPos = curCell.yPos + direction.yChange;
      curCell.value = game.map.field[curCell.yPos][curCell.xPos].value;

      if (curCell.value.compare(AIR) == 0)
      {
        continue;
      }
      else if (curCell.value.compare(EARTH) == 0)
      {
        applyGravity(game, curCell.xPos, curCell.yPos);
      }
      else
      {
        giveDamageAt(game, curCell.xPos, curCell.yPos);
      }
      hit = true;
    }
  };
};

#endif