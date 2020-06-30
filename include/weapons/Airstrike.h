#ifndef __AIRSTRIKE_H__
#define __AIRSTRIKE_H__

#include "../common.h"
#include "../Game.h"
#include "../Utilities.h"

class Airstrike : public Weapon
{
public:
  Airstrike(Game &_game) : Weapon(_game)
  {
    game = _game;
    name = "airstrike";
    ammunition = 0;
    fireDirections = {"b"};
    damage = 35;
  };

  void fire(FireDirection _)
  {
    // do nothing
  }

  void fire(const int &column)
  {
    if (column < 0 || column >= game.map.numColumns)
    {
      printf("[WARNING] Given column was not in map range!\n");
      return;
    }

    if (ammunition > 0)
    {
      ammunition -= 1; // ammunition = ammunition - 1;
    }

    for (int i = 0; i < game.map.numRows; i++)
    {
      MapElement curCell = game.map.field[i][column];

      if (curCell.value.compare(AIR) == 0)
      {
        continue;
      }
      else if (curCell.value.compare(WATER) == 0)
      {
        return;
      }
      else if (curCell.value.compare(EARTH) == 0)
      {
        applyGravity(game, curCell.xPos, curCell.yPos + 1);
        return;
      }
      else
      {
        giveDamageAt(game, curCell.xPos, curCell.yPos);
        return;
      }
    }
  }
};

#endif