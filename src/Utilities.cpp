#include "../include/Utilities.h"

void applyGravity(Game &game, const int &xPos, const int &yPos)
{
  int bottom = yPos; // the position, where an element can fall

  for (int i = yPos - 1; i >= 0; i--)
  {
    MapElement cur = game.map.field[i][xPos];

    if (cur.value.compare(AIR) != 0)
    {
      int tmpX = cur.xPos;
      int tmpY = cur.yPos;

      if (cur.isWorm())
      {
        Worm *w = getWormAtPosition(game, tmpX, tmpY);
        bool wormRemoved = false;

        if (w != NULL)
        {
          if (game.map.field[bottom + 1][xPos].value.compare(WATER) == 0)
          {
            printf("\u0FBE\t %s (%d) drowned.\n", w->name.c_str(), w->id);
            removeWorm(game, w->id);
            return;
          }

          // move position of worm to bottom
          for (int j = i; j < bottom; j++)
          {
            cur.yPos++;
            w->position.y++;
            if (game.map.field[w->position.y + 1][xPos].isCase())
            {
              openCase(game, xPos, yPos);
              // changeWormPosition(game, w[0], xPos, yPos);
            }
            else if (game.gameInitialized)
            {
              w->health -= FALL_DAMAGE;
              printf("%s (%d) took %dhp fall damage\n", w->name.c_str(), w->id, FALL_DAMAGE);
            }
          }

          if (w->health <= 0)
          {
            printf("\u0FBE\t%s (%d) fell into his death.\n", w->name.c_str(), w->id);
            removeWorm(game, w->id);
            wormRemoved = true;
          }
        }

        // dont change starting row if worm is removed
        if (wormRemoved)
        {
          i++;
        }
        else
        {
          bottom--;
        }
      }
      else
      {
        // int tmpBottom = cur.isCase() ? bottom - 1 : bottom;
        int tmpBottom = bottom;
        for (int j = i; j < tmpBottom; j++)
        {
          cur.yPos++;
        }
        bottom--;
      }

      game.map.field[tmpY][tmpX].value = AIR;
      game.map.field[cur.yPos][xPos] = cur;

      // if case falls upon a worm
      if (cur.isCase())
      {
        // check under worm
        if (game.map.field[cur.yPos + 1][cur.xPos].value.compare(WATER) == 0)
        {
          game.map.field[cur.yPos][cur.xPos].value = AIR;
          return;
        }
        if (game.map.field[cur.yPos + 1][cur.xPos].isWorm())
        {
          openCase(game, cur.xPos, cur.yPos);
        }
      }
    }
  }
}

void applyGravityAtColumn(Game &game, const int &col)
{
  for (int row = game.map.numRows - 1; row >= 0; row--)
  {
    MapElement &m = game.map.field[row][col];
    if (m.value.compare(AIR) == 0 || m.isCase())
    {
      applyGravity(game, col, row);
    }
  }
}

void changeWormPosition(Game &game, Worm &w, const int &xPos, const int &yPos)
{
  if (game.map.field[yPos][xPos].isCase())
  {
    openCase(game, xPos, yPos);
    for (int y = yPos - 1; y >= 0; y--)
    {
      MapElement &m = game.map.field[y][xPos];
      if (m.value.compare(AIR) == 0)
      {
        break;
      }
      if (m.isCase())
      {
        openCase(game, xPos, y);
      }
    }
  }

  game.map.field[w.position.y][w.position.x].value = AIR;
  w.position.x = xPos;
  w.position.y = yPos;
  game.map.field[yPos][xPos].value = w.icon;

  MapElement underWorm = game.map.field[yPos + 1][xPos];

  if (underWorm.value.compare(WATER) == 0)
  {
    Worm *w = getWormAtPosition(game, xPos, yPos);
    if (w != NULL)
    {
      printf("\u0FBE\t %s (%d) drowned.\n", w->name.c_str(), w->id);
      removeWorm(game, w->id);
      return;
    }
  }

  if (underWorm.isCase())
  {
    openCase(game, xPos, yPos + 1);
    game.map.field[w.position.y][w.position.x].value = AIR;
    w.position.x = xPos;
    w.position.y = yPos + 1;
    game.map.field[yPos + 1][xPos].value = w.icon;
  }

  applyGravityAtColumn(game, xPos);
};

void checkIfGameEnds(Game &game)
{
  if (game.allPlayers.size() == 1)
  {
    game.printMap();
    game.printPlayersInfo();
    printf("\n\u2705 Player %s won the game !\n\n", game.allPlayers[0]->name.c_str());
    game.gameRunning = false;
    exit(0);
  }
}

vector<MapElement> getDirectNeighbours(Game &game, MapElement &curCell)
{
  vector<MapElement> neighbours = {};

  // top
  if (curCell.yPos > 0)
  {
    neighbours.push_back(game.map.field[curCell.yPos - 1][curCell.xPos]);
  }
  // right
  if (curCell.xPos < game.map.numColumns - 1)
  {
    neighbours.push_back(game.map.field[curCell.yPos][curCell.xPos + 1]);
  }
  // left
  if (curCell.xPos > 0)
  {
    neighbours.push_back(game.map.field[curCell.yPos][curCell.xPos - 1]);
  }
  // bottom
  if (curCell.yPos < game.map.numRows - 1)
  {
    neighbours.push_back(game.map.field[curCell.yPos + 1][curCell.xPos]);
  }

  return neighbours;
}

vector<MapElement> getAllNeighbours(Game &game, MapElement &curCell)
{
  vector<MapElement> neighbours = getDirectNeighbours(game, curCell);

  // top right
  if (curCell.yPos > 0 && curCell.xPos < game.map.numColumns - 1)
  {
    neighbours.push_back(game.map.field[curCell.yPos - 1][curCell.xPos + 1]);
  }
  // bottom right
  if (curCell.yPos < game.map.numRows - 1 && curCell.xPos < game.map.numColumns - 1)
  {
    neighbours.push_back(game.map.field[curCell.yPos + 1][curCell.xPos + 1]);
  }
  // bottom left
  if (curCell.yPos < game.map.numRows - 1 && curCell.xPos > 0)
  {
    neighbours.push_back(game.map.field[curCell.yPos + 1][curCell.xPos - 1]);
  }
  // top left
  if (curCell.yPos > 0 && curCell.xPos > 0)
  {
    neighbours.push_back(game.map.field[curCell.yPos - 1][curCell.xPos - 1]);
  }

  return neighbours;
}

Weapon *getWeapon(vector<Weapon *> &weapons, const WeaponPosition &weapon)
{
  return weapons.at(weapon);
}

Worm *getWormAtPosition(Game &game, const int &x, const int &y)
{
  if (y >= game.map.numRows || y < 0)
  {
    // printf("No worm found at position x: %d y: %d\n", x, y);
    return NULL;
  }
  if (y >= game.map.numColumns || x < 0)
  {
    // printf("No worm found at position x: %d y: %d\n", x, y);
    return NULL;
  }

  for (int p = 0; p < game.numPlayers; p++)
  {
    for (size_t w = 0; w < game.allPlayers[p]->worms.size(); w++)
    {
      Worm *worm = &(game.allPlayers[p]->worms[w]);
      if (worm->position.x == x && worm->position.y == y)
      {
        return worm;
      }
    }
  }

  // printf("No worm found at position x: %d y: %d\n", x, y);
  return NULL;
}

bool giveDamageAt(Game &game, const int &x, const int &y)
{
  MapElement &m = game.map.field[y][x];
  if (m.isCase()) {
    m.value = AIR;
  }
  if (m.value.compare(EARTH) == 0)
  {
    printf("Shot hit EARTH at position (%d, %d)\n", x, y);
    applyGravity(game, x, y + 1);
    return true;
  }

  for (auto &p : game.allPlayers)
  {
    int index = 0;

    for (auto &w : p->worms)
    {
      if (w.position.x == x && w.position.y == y)
      {
        w.health -= game.selectedWeapon->damage;
        printf("Shot hit %s (%d) at position (%d, %d) => %dhp\n", w.name.c_str(), w.id, w.position.y, w.position.x, w.health);

        if (w.health <= 0)
        {
          game.map.field[w.position.y][w.position.x].value = AIR;
          printf("\u0FBE\t Worm '%s' died\n", w.name.c_str());
          p->worms.erase(p->worms.begin() + index);

          if (p->worms.size() == 0)
          {
            removePlayer(game, p->name);
          }
          applyGravity(game, w.position.x, w.position.y + 1);
          return true;
        }
        index++;
      }
    }
  }

  return false;
}

void removePlayer(Game &game, const string &name)
{
  for (size_t idx = 0; idx < game.allPlayers.size(); idx++)
  {
    Player &p = game.allPlayers[idx][0];
    if (p.name == name)
    {
      printf("\n\u274C Player %s GAME OVER\n", p.name.c_str());
      game.allPlayers.erase(game.allPlayers.begin() + idx);
      checkIfGameEnds(game);
      break;
    }
  }
}

void removeWorm(Game &game, const int &wormId)
{
  int index = 0;
  for (auto &p : game.allPlayers)
  {
    for (const auto &w : p->worms)
    {
      if (w.id == wormId)
      {
        game.map.field[w.position.y][w.position.x].value = AIR;
        printf("\u0FBE\t %s (%d) died\n", w.name.c_str(), w.id);
        p->worms.erase(p->worms.begin() + index);

        if (p->worms.size() == 0)
        {
          removePlayer(game, p->name);
        }
        return;
      }
      index++;
    }
  }
}

/*
  This function splits a string by a given delimiter and returns a string vector.
  ex:
    string: "MAP=some/path/to/Map"
    delimiter: '='
    result: [ "MAP", "some/path/to/Map" ]

  @param str String to split
  @param delimiter Delimiter character for splitting

  @return A pair of strings
*/
vector<string> splitString(string str, string delimiter)
{
  vector<string> result = {};
  const string token = str.substr(0, str.find(delimiter));
  auto start = 0U;
  auto end = str.find(delimiter);

  string word;

  while (end != string::npos)
  {
    word = str.substr(start, end - start);
    start = end + delimiter.length();
    end = str.find(delimiter, start);
    result.push_back(word);
  }

  word = str.substr(start, end);
  if (!word.empty())
  {
    result.push_back(word);
  }
  return result;
}

string getRandomWeaponName()
{
  const vector<string> weapons = {"melee", "bazooka", "blowtorch", "airstrike", "teleporter"};
  se::Random *r = new se::Random();
  return weapons.at(r->getRandomInt(0, weapons.size() - 1));
}

void openCase(Game &game, const int &caseXPos, const int &caseYPos)
{
  const string randomWeapon = getRandomWeaponName();
  for (auto &w : game.selectedWorm->weapons)
  {
    if (w->name.compare(randomWeapon) == 0)
    {
      w->ammunition += 1;
      printf("%s (%d) picked up 1 of '%s'\n", game.selectedWorm->name.c_str(), game.selectedWorm->id, w->name.c_str());
      game.map.field[caseYPos][caseXPos].value = AIR;
      return;
    }
  }
}