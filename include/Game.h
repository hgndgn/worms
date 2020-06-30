#ifndef __GAME_H__
#define __GAME_H__

#include "common.h"
#include "Map.h"
#include "Player.h"
#include "Weapon.h"
#include "Worm.h"

class Weapon;
class Player;

class Game
{
public:
  Player *currentPlayer;
  Worm *selectedWorm;
  Weapon *selectedWeapon;
  vector<Player *> allPlayers;
  vector<string> allWeapons;
  Map map;
  string cmdPrompt;
  int numWorms;
  int groundStart;
  int groundEnd;
  int numPlayers = 2;
  bool gameRunning = true;
  bool gameInitialized = false;

  Game();

  void printMap()
  {
    if (map.numRows == 0)
      return;

    const int x = map.numColumns;
    const int y = map.numRows;

    printf("\n\u279C  CURRENT MAP:\n");

    printf("*");

    for (int k = 0; k <= x; k++)
    {
      if (k % 2 == 0)
        cout << k % 10;
      else
        cout << ' ';
    }
    printf("\n");

    for (int i = 0; i < y; i++)
    {
      cout << i % 10;
      for (int k = 0; k <= x; k++)
      {
        cout << map.field[i][k].value;
      }
      cout << i % 10;

      printf("\n");
    }

    printf("*");

    for (int k = 0; k < x; k++)
    {
      if (k % 2 == 0)
        cout << k % 10;
      else
        cout << ' ';
    }
    printf("*\n");
  }

  void initMap()
  {
    const int x = map.field[0].size();
    const int y = map.field.size();

    for (int i = 0; i < y; i++)
    {
      for (int k = 0; k < x; k++)
      {
        const string value = map.field[i][k].value;

        if (value == MAP_AIR)
        {
          map.field[i][k].value = AIR;
        }
        if (value == MAP_EARTH)
        {
          map.field[i][k].value = EARTH;
        }
        if (value == MAP_WATER)
        {
          map.field[i][k].value = WATER;
        }
        if (value == MAP_CASE)
        {
          map.field[i][k].value = CASE;
        }
      }
    }
  }

  void printPlayersInfo();
};

#endif