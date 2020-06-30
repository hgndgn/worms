#include "Worm.h"
#include "constants.h"
#include "weapons/Airstrike.h"
#include "weapons/Bazooka.h"
#include "weapons/Blowtorch.h"
#include "weapons/Melee.h"
#include "weapons/Pistol.h"
#include "weapons/Teleporter.h"

Worm::Worm(){};
Worm::Worm(int _id, string _name, string _icon, string _playerId) : id(_id), name(_name), icon(_icon), playerId(_playerId)
{
  weapons.resize(MAX_WEAPONS);
};

void Worm::initWeapons(Game &game)
{
  weapons.at(WeaponPosition::PISTOL) = new Pistol(game);
  weapons.at(WeaponPosition::MELEE) = new Melee(game);
  weapons.at(WeaponPosition::BAZOOKA) = new Bazooka(game);
  weapons.at(WeaponPosition::BLOWTORCH) = new Blowtorch(game);
  weapons.at(WeaponPosition::AIRSTRIKE) = new Airstrike(game);
  weapons.at(WeaponPosition::TELEPORTER) = new Teleporter(game);
}