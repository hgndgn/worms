#ifndef __TELEPORTER_H__
#define __TELEPORTER_H__

#include "../common.h"
#include "../Game.h"
#include "../Utilities.h"
#include "../MapElement.h"

class Teleporter : public Weapon
{
private:
  bool isInvalidPosition(int xPos, int yPos)
  {
    return xPos < 0 || xPos >= game.map.numColumns || yPos < 0 || yPos >= game.map.numRows;
  }

public:
  Teleporter(Game &_game) : Weapon(_game)
  {
    game = _game;
    name = "teleporter";
    ammunition = 0;
  }

  void fire(FireDirection fd)
  {
    // just do nothing
  }

  void use(Worm &w, int xPos, int yPos)
  {
    const int &oldX = w.position.x;

    if (ammunition > 0)
    {
      ammunition -= 1; // ammunition = ammunition - 1;
    }

    if (isInvalidPosition(xPos, yPos))
    {
      printf("%s (%d) fell out of the map.\n", game.selectedWorm->name.c_str(), game.selectedWorm->id);
      removeWorm(game, game.selectedWorm->id);
      return;
    }

    MapElement &m = game.map.field[yPos][xPos];
    if (m.value.compare(AIR) == 0 || m.isCase())
    {
      changeWormPosition(game, w, xPos, yPos);
      applyGravityAtColumn(game, oldX);
      return;
    }

    bool validPosition = false;

    while (!validPosition)
    {
      int tmpX;
      int tmpY;
      printf("Teleport x: ");
      cin >> tmpX;
      printf("Teleport y: ");
      cin >> tmpY;

      if (isInvalidPosition(tmpX, tmpY))
      {
        printf("%s (%d) fell out of the map.\n", game.selectedWorm->name.c_str(), game.selectedWorm->id);
        removeWorm(game, game.selectedWorm->id);
        validPosition = true;
        return;
      }

      MapElement &m = game.map.field[tmpY][tmpX];
      if (m.value.compare(AIR) == 0 || m.isCase())
      {
        changeWormPosition(game, w, tmpX, tmpY);
        applyGravityAtColumn(game, oldX);
        validPosition = true;
        return;
      }

      printf("Position not free!\n");
    }
  }
};

#endif