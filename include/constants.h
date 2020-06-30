#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <string>
#include <unordered_map>
#include "FireDirection.h"

const string CONFIG_PATH = "./assets/config";

const string MAP_AIR = "A";
const string MAP_EARTH = "E";
const string MAP_WATER = "W";
const string MAP_CASE = "#";
const string AIR = " ";
const string EARTH = "\u23F9";
const string WATER = "-";
const string CASE = "\u25C9";

const int MAX_WEAPONS = 6;
const int INITIAL_HP = 100;
const int FALL_DAMAGE = 10;

enum WeaponPosition
{
  PISTOL = 0,
  MELEE = 1,
  BAZOOKA = 2,
  BLOWTORCH = 3,
  AIRSTRIKE = 4,
  TELEPORTER = 5
};

extern unordered_map<string, FireDirection> DIRECTIONS;

#endif