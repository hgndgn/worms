#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include "Game.h"
#include "MapElement.h"
#include "Worm.h"
#include "Random.h"

void applyGravity(Game &game, const int &xPos, const int &yPos);
void applyGravityAtColumn(Game &game, const int &col);
void changeWormPosition(Game &game, Worm &w, const int &xPos, const int &yPos);
void checkIfGameEnds(Game &game);
vector<MapElement> getAllNeighbours(Game &game, MapElement &curCell);
vector<MapElement> getDirectNeighbours(Game &game, MapElement &curCell);
Weapon *getWeapon(vector<Weapon *> &weapons, const WeaponPosition &weapon);
Worm *getWormAtPosition(Game &game, const int &x, const int &y);
bool giveDamageAt(Game &game, const int &x, const int &y);
void removeWorm(Game &game, const int &wormId);
void removePlayer(Game &game, const string &name);
vector<string> splitString(string str, string delimiter);
string getRandomWeaponName();
void openCase(Game &game, const int &caseXPos, const int &caseYPos);

#endif