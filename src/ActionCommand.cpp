#include "../include/commands/ActionCommand.h"
#include "../include/weapons/Airstrike.h"
#include "../include/weapons/Teleporter.h"

ActionCommand::ActionCommand(Game &_g) : game(_g){};
ActionCommand::ActionCommand(Game &_g, const int &_col) : game(_g), col(_col){};
ActionCommand::ActionCommand(Game &_g, const int &_col, const int &_row) : game(_g), col(_col), row(_row){};
ActionCommand::ActionCommand(Game &_g, const string &_direction) : game(_g), direction(_direction){};
ActionCommand::~ActionCommand(){};

bool ActionCommand::execute()
{
  // use melee
  if (col == -1 && row == -1 && direction.empty())
  {
    if (game.selectedWeapon->name.compare("melee") != 0)
    {
      printf("[ERROR] Given parameters are wrong for selected weapon!\n");
      return false;
    }
    game.selectedWeapon = getWeapon(game.selectedWorm->weapons, WeaponPosition::MELEE);
    if (game.selectedWeapon->ammunition <= 0)
    {
      printf("[ERROR] No ammunition for Melee!\n");
      return false;
    }
    game.selectedWeapon->fire();
  }
  // use teleporter
  else if (col != -1 && row != -1)
  {
    if (game.selectedWeapon->name.compare("teleporter") != 0)
    {
      printf("[ERROR] Given parameters are wrong for selected weapon!\n");
      return false;
    }
    Teleporter t = ((Teleporter *)game.selectedWeapon)[0];
    t.use(game.selectedWorm[0], col, row);
  }
  // use airstrike
  else if (col != -1 && row == -1 && !direction.empty())
  {
    if (game.selectedWeapon->name.compare("airstrike") != 0)
    {
      printf("[ERROR] Given parameters are wrong for selected weapon!\n");
      return false;
    }
    Airstrike &a = ((Airstrike *)game.selectedWeapon)[0];
    if (a.ammunition <= 0)
    {
      printf("[ERROR] No ammunition for Airstrike!\n");
      return false;
    }
    a.fire(col);
  }
  else if (col == -1 && row == -1 && !direction.empty())
  {
    // use pistol / bazooka / blowtorch
    const string curWeapon = game.selectedWeapon->name;
    const bool isPistol = curWeapon.compare("pistol") == 0;
    const bool isBazooka = curWeapon.compare("bazooka") == 0;
    const bool isBlowtorch = curWeapon.compare("blowtorch") == 0;

    if (!isPistol && !isBazooka && !isBlowtorch)
    {
      printf("[ERROR] Given parameters are wrong for selected weapon!\n");
      return false;
    }

    // check if given direction is available in selected weapons directions
    if (find(game.selectedWeapon->fireDirections.begin(), game.selectedWeapon->fireDirections.end(), direction) != game.selectedWeapon->fireDirections.end())
    {
      if (DIRECTIONS.find(direction) == DIRECTIONS.end())
      {
        printf("[ERROR] Direction not available for current weapon!\n");
        return false;
      }
      game.selectedWeapon->fire(DIRECTIONS[direction]);
    }
    else
    {
      printf("[ERROR] Not valid direction!\n");
      return false;
    }
  }

  return true;
};
