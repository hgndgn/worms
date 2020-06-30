#ifndef __CONFIG_READER_H__
#define __CONFIG_READER_H__

#include "common.h"
#include "Random.h"
#include "MapElement.h"
#include "Game.h"

class ConfigReader
{
private:
  Game &game;
  Map readMapConfig(string filename);

public:
  void configure(string filename);

  ConfigReader(Game &);
};

#endif