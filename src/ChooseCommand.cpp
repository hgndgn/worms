#include "../include/commands/ChooseCommand.h"

ChooseCommand::ChooseCommand(Game &_g, const string &_weaponName) : game(_g), weaponName(_weaponName){};
ChooseCommand::~ChooseCommand(){};

bool ChooseCommand::execute()
{
  for (auto &w : game.selectedWorm->weapons)
  {
    if (w->name.compare(weaponName) == 0)
    {
      if (w->ammunition == 0) {
        printf("[ERROR] You don't have '%s'\n", w->name.c_str());
        return false;
      }
      game.selectedWeapon = w;
      printf("Chose weapon '%s' => ammunition: %d\n", w->name.c_str(), w->ammunition);
      return true;
    }
  }
  printf("[ERROR] Weapon '%s' not exists!\n", weaponName.c_str());
  return false;
};
