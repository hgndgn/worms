#ifndef __BAZOOKA_H__
#define __BAZOOKA_H__

#include "../common.h"
#include "../constants.h"
#include "../FireDirection.h"
#include "../Game.h"
#include "../Utilities.h"

void getDirectNeighbours(MapField &m, MapElement curCell, vector<MapElement &> neighbours);

class Bazooka : public Weapon
{
public:
  Bazooka(Game &_game) : Weapon(_game)
  {
    game = _game;
    name = "bazooka";
    ammunition = 0;
    fireDirections = FireDirection::ALL();
    damage = 40;
  };

  void fire(FireDirection direction)
  {
    if (ammunition > 0)
    {
      ammunition -= 1; // ammunition = ammunition - 1;
    }

    Position current = game.selectedWorm->position;
    MapElement curCell = game.map.field[current.y][current.x];

    bool hit = false;

    while (!hit)
    {
      curCell.xPos += direction.xChange;
      curCell.yPos += direction.yChange;
      curCell.value = game.map.field[curCell.yPos][curCell.xPos].value;

      if (curCell.value.compare(AIR) == 0)
      {
        continue;
      }

      hit = true;
      if (curCell.isCase())
      {
        printf("Shot destroyed case at position (%d, %d)\n", curCell.xPos, curCell.yPos);
        game.map.field[curCell.yPos][curCell.xPos].value = AIR;
      }

      vector<MapElement> neighbours = getDirectNeighbours(game, curCell);

      // iterate over all neighbours
      for (auto &neighbour : neighbours)
      {
        if (neighbour.value.compare(AIR) != 0)
        {
          // if bottom neighbour
          if (neighbour.yPos == curCell.yPos + 1)
          {
            giveDamageAt(game, curCell.xPos, curCell.yPos);
          }

          giveDamageAt(game, neighbour.xPos, neighbour.yPos);
        }
      }
    }
  }
};

#endif