#include <iostream>
#include <fstream>
#include "../include/ConfigReader.h"
#include "../include/Game.h"

/*
    - Initialize number of worms
    - Read and configure map
 */
void initGame(Game &game)
{
  cout << "How many worms ?\n";
  cin >> game.numWorms;

  if (game.numWorms < 1)
  {
    printf("No worms, no game :(\n");
    exit(0);
  }
  if (game.numWorms > 3)
  {
    printf("Too many worms. Maximum worms: 3\n");
    exit(0);
  }

  for (int i = 0; i < game.numPlayers; i++)
  {
    printf("Type in player %d worm icon: ", i + 1);
    string name = to_string(i + 1);
    string wormIcon;
    cin >> wormIcon;
    if (wormIcon.size() == 0)
    {
      printf("Worm icon can not be empty!\n");
      --i;
      continue;
    }
    game.allPlayers.push_back(new Player(game, name, wormIcon.substr(0, 1)));
  }

  ConfigReader(game).configure(CONFIG_PATH);

  game.selectedWorm = &game.allPlayers[0]->worms[0];
  game.selectedWeapon = game.selectedWorm->weapons[0];
  game.currentPlayer = game.allPlayers[0];

  printf("Player 1 turn\n");
}