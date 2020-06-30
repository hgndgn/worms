#include "../include/commands/MoveCommand.h"

MoveCommand::MoveCommand(Game &_g, Worm &_w, const FireDirection &_fd, const int &_s) : game(_g), worm(_w), fd(_fd), steps(_s){};
MoveCommand::~MoveCommand(){};

void applyGravityToPreviousColumn(Game &game, const string &direction, const int &col)
{
  if (direction.compare("r") == 0)
  {
    applyGravityAtColumn(game, col - 1);
  }
  else
  {
    applyGravityAtColumn(game, col + 1);
  }
}

bool MoveCommand::execute()
{
  // const int xPos = worm.position.x;

  for (int i = 0; i < steps; i++)
  {
    int nextX = worm.position.x + fd.xChange;
    int nextY = worm.position.y + fd.yChange;

    if (nextX < 0 || nextX > game.map.numColumns - 1)
    {
      printf("[WARNING] can't move further\n");
      return true;
    }

    MapElement next = game.map.field[nextY][nextX];

    // move one step to left/right
    if (next.value.compare(AIR) == 0 || next.value.compare(CASE) == 0)
    {
      int numWormsBeforeMove = game.currentPlayer->numWorms();
      changeWormPosition(game, worm, nextX, nextY);
      applyGravityToPreviousColumn(game, fd.direction, worm.position.x);
      if (game.currentPlayer->numWorms() < numWormsBeforeMove)
      {
        return true;
      }

      continue;
    }

    // can't move further
    if (nextY == 0)
    {
      printf("[WARNING] can't move further\n");
      return true;
    }

    // climb up to left/right element
    MapElement &m = game.map.field[nextY - 1][nextX];
    if (m.value.compare(AIR) == 0 || m.isCase())
    {
      int numWormsBeforeMove = game.currentPlayer->numWorms();
      changeWormPosition(game, worm, nextX, nextY - 1);
      applyGravityToPreviousColumn(game, fd.direction, worm.position.x);
      if (game.currentPlayer->numWorms() < numWormsBeforeMove)
      {
        return true;
      }

      continue;
    }

    printf("[WARNING] can't move further\n");
    return true;
  }

  return true;
};