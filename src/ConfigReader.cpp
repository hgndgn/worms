#include <time.h>

#include "../include/ConfigReader.h"
#include "../include/Map.h"
#include "../include/MapElement.h"
#include "../include/Position.h"
#include "../include/Random.h"
#include "../include/Utilities.h"

int wormIdCounter = 1;

ConfigReader::ConfigReader(Game &s) : game(s){};

/*
  Checks, if a substring exists in a string.
  ex:
    str: "abcdef"
    substr: "bc"
    result: 1

    str: "abcdef"
    substr: "ca"
    result: 0

  @param str The string to check 
  @param substr The substring to check in str
  
  @return 1 if substr exists in str otherwise 0
 */
bool hasSubstring(string str, string substr)
{
  return str.find(substr) != std::string::npos;
}

/*
  Reads the map from a file and returns a two dimensional character vector.

  @param mapPath The path of the file, where the map is defined

  @return Two dimensional character vector, consisting the map elements
*/
Map ConfigReader::readMapConfig(string mapPath)
{
  ifstream mapConfigFile(mapPath);
  Map map;

  // if the map file opened successfully
  if (mapConfigFile.is_open())
  {
    string line;
    int x = 0;
    int y = 0;

    // Read map file line by line. Store in each iteration
    // the content of current line into "line" variable
    while (getline(mapConfigFile, line))
    {
      x = line.size();
      y++;
    }

    // set the vector size
    map.numColumns = x;
    map.numRows = y;
    map.field.resize(y);
    // set cursor to the begin of the file,
    // because the while loop above brought the cursor to the end of the file
    mapConfigFile.clear();
    mapConfigFile.seekg(0, ios::beg);

    int i = 0;

    // Read file line by line
    while (getline(mapConfigFile, line))
    {
      /*
        The line is a string, therefore iterate over it
        Put each character into the i'th line of the vector

        ex:
          line: "ABC"
          iteration 1: 
            line[k] = 'A'
            map.field[i].push_back('A')
            => map.field[i] = ['A']
          iteration 2: 
            line[k] = 'B'
            map.field[i].push_back('B')
            => map.field[i] = ['A', 'B']
          iteration 3:
            line[k] = 'C'
            map.field[i].push_back('C')
            => map.field[i] = ['A', 'B', 'C']
      */
      for (size_t k = 0; k < line.size(); k++)
      {
        // Create a map element object with the character value line[k] (k'th element of line i) and the position above
        string s(1, line[k]);
        map.field[i].push_back(*(make_unique<MapElement>(s, k, i).get()));
      }
      i++; // go to next line
    }
  }

  return map;
}

void initPlayerWorms(Game &game, Player &player, se::Random &r)
{
  vector<Worm> worms = {};
  for (int j = 0; j < game.numWorms; j++)
  {
    int xPos;
    int yPos;

    bool validPositionFound = false;

    while (!validPositionFound)
    {
      xPos = r.getRandomInt(game.groundStart, game.groundEnd);
      yPos = r.getRandomInt(0, game.map.numRows - 1);
      MapElement &me = game.map.field[yPos][xPos];
      MapElement &bottomEl = game.map.field[yPos + 1][xPos];

      if (me.value.compare(AIR) == 0 && !bottomEl.isWorm())
      {
        validPositionFound = true;
      }
    }

    string wormName = r.getWormName();

    Worm w(wormIdCounter++, wormName, player.wormIcon, player.name);
    w.icon = player.wormIcon;
    w.health = INITIAL_HP;
    w.position = Position(xPos, yPos);
    w.initWeapons(game);

    MapElement me(w.icon);
    me.xPos = xPos;
    me.yPos = yPos;
    game.map.field[yPos][xPos] = me;
    player.worms.push_back(w);
    applyGravityAtColumn(game, xPos);
    printf("Spawning %s (%d) at (%d, %d)\n", w.name.c_str(), w.id, w.position.x, w.position.y);
  }
}

void ConfigReader::configure(string filePath)
{
  ifstream configFile(filePath);

  // if the config file opened successfully
  if (configFile.is_open())
  {
    string line;
    se::Random *r = NULL;

    while (getline(configFile, line))
    {
      // if the line start with '[' or '#' or ' ', then ignore this line and continue to next line
      const char lineStart = line[0];
      if (lineStart == '[' || lineStart == '#' || line.empty())
        continue;

      // split the string by '=' delimiter
      // return value is a pair ex: Pair("NUM_PLAYERS", "2")
      vector<string> splitted = splitString(line, "=");

      if (splitted[0] == "MAP")
      {
        game.map = readMapConfig(splitted[1]);
        game.initMap();

        int x = game.map.field[game.map.numRows - 1].size() - 1;
        int y = game.map.numRows - 1;

        for (int i = 0; i <= x; i++)
        {
          if (game.map.field[y - 1][i].value.compare(EARTH) == 0)
          {
            game.groundStart = i;
            break;
          }
        }

        for (int i = x; i > game.groundStart; i--)
        {
          if (game.map.field[y - 1][i].value.compare(EARTH) == 0)
          {
            game.groundEnd = i;
            break;
          }
        }
      }

      if (splitted[0] == "WORM_NAMES")
      {
        const string wormNamesPath = splitted[1];
        r = new se::Random(wormNamesPath);
      }

      if (splitted[0] == "PROMT")
      {
        game.cmdPrompt = splitted[1];
      }
    }

    for (auto &p : game.allPlayers)
    {
      initPlayerWorms(game, p[0], r[0]);
    }

    game.gameInitialized = true;
    game.printPlayersInfo();
    game.printMap();

    configFile.close(); //close the file object.
  }
}