#include "Weapon.h"

Weapon::Weapon(Game &s) : game(s){};

void Weapon::printInfo()
{
  if (ammunition == 0)
  {
    return;
  }
  printf("  %s (ammunition: %d)", name.c_str(), ammunition);
  if (game.selectedWeapon->name.compare(name) == 0)
  {
    printf("  *\n");
  }
  else
  {
    printf("\n");
  }
};