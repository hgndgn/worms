#ifndef __ICOMMAND_H
#define __ICOMMAND_H

#include "../common.h"

/**
    see https://en.wikipedia.org/wiki/Command_pattern#C++
 **/
class ICommand
{
public:
  string name;

  virtual ~ICommand() = default;

  /*
    @return true if command successfully executed, false otherwise
  */
  virtual bool execute() = 0;
};

#endif