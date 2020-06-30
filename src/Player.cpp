#include "Player.h"

Player::Player(Game &_s, const string &_name, const string &_wormIcon) : game(_s), name(_name), wormIcon(_wormIcon) {}

int Player::numWorms()
{
  return worms.size();
}

void Player::selectWorm(const string &name)
{
  for (auto &w : worms)
  {
    if (w.name.compare(name) == 0)
    {
      game.selectedWorm = &w;
      return;
    }
  }

  printf("[ERROR] Worm not found!\n");
}
